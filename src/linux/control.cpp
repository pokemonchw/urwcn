#include "control.h"
#include "hooks.h"
#include <SDL2/SDL.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <dlfcn.h>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstring>
#include <cstdlib>
#include <mutex>
#include <stdexcept>
#include <thread>

namespace uwcn::linux_host {
namespace {
int listener=-1,client=-1;
std::atomic<bool> listening{};
std::mutex socket_lock;
std::thread worker;
void serve() {
    while(listening) {
        const int incoming=accept4(listener,nullptr,nullptr,SOCK_CLOEXEC);
        if(incoming<0) break;
        {
            std::lock_guard lock(socket_lock);
            if(!listening) { close(incoming); break; }
            client=incoming;
        }
        ucred peer{}; socklen_t size=sizeof(peer);
        if(getsockopt(incoming,SOL_SOCKET,SO_PEERCRED,&peer,&size)==0 && peer.uid==geteuid()) {
            std::string command;
            char value;
            while(recv(incoming,&value,1,0)==1 && value!='\n') command+=value;
            std::string response;
            try { response=control_command(command); }
            catch(const std::exception& error) { response="Failed "+std::string(error.what()); }
            response+='\n';
            std::size_t sent=0;
            while(sent<response.size()) {
                const auto count=send(incoming,response.data()+sent,response.size()-sent,MSG_NOSIGNAL);
                if(count<=0) break;
                sent+=count;
            }
        }
        { std::lock_guard lock(socket_lock); close(incoming); client=-1; }
    }
}
}
void start_control() {
    listener=socket(AF_UNIX,SOCK_STREAM|SOCK_CLOEXEC,0);
    if(listener<0) throw std::runtime_error("Cannot create resident control socket");
    // Linux abstract namespace: no filesystem alias or stale socket file.
    const auto name="uwcn-"+std::to_string(geteuid())+"-"+std::to_string(getpid());
    sockaddr_un address{};
    address.sun_family=AF_UNIX;
    std::memcpy(address.sun_path+1,name.data(),name.size());
    const auto length=offsetof(sockaddr_un,sun_path)+1+name.size();
    if(bind(listener,reinterpret_cast<const sockaddr*>(&address),length)!=0 || listen(listener,8)!=0)
        throw std::runtime_error("Cannot bind resident control socket: "+name);
    listening=true;
    worker=std::thread(serve);
    std::atexit(stop_control);
}
void stop_control() {
    if(!listening.exchange(false)) return;
    end_control_requests();
    {
        std::lock_guard lock(socket_lock);
        shutdown(listener,SHUT_RDWR);
        if(client>=0) shutdown(client,SHUT_RDWR);
    }
    worker.join();
    close(listener); listener=-1;
}
}
namespace {
template<class T> T sdl(const char* name) { return reinterpret_cast<T>(dlsym(RTLD_NEXT,name)); }
void service() { uwcn::linux_host::service_control(); }
int wait_event(SDL_Event* event,int timeout) {
    static const auto wait=sdl<decltype(&SDL_WaitEventTimeout)>("SDL_WaitEventTimeout");
    static const auto clear=sdl<decltype(&SDL_ClearError)>("SDL_ClearError");
    static const auto error=sdl<decltype(&SDL_GetError)>("SDL_GetError");
    const auto start=std::chrono::steady_clock::now();
    for(;;) {
        service();
        const auto elapsed=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-start).count();
        const int remaining=timeout<0 ? 40 : std::max(0,timeout-static_cast<int>(elapsed));
        clear();
        const int result=wait(event,std::min(40,remaining));
        if(result || *error()) return result;
        if(timeout>=0 && std::chrono::steady_clock::now()-start>=std::chrono::milliseconds(timeout)) return 0;
        // Internal slices never become fake input or game-visible timeouts.
    }
}
}
extern "C" int SDL_PollEvent(SDL_Event* event) {
    static const auto original=sdl<decltype(&SDL_PollEvent)>("SDL_PollEvent");
    service(); return original(event);
}
extern "C" int SDL_WaitEvent(SDL_Event* event) { return wait_event(event,-1); }
extern "C" int SDL_WaitEventTimeout(SDL_Event* event,int timeout) { return wait_event(event,timeout); }
extern "C" int SDL_PeepEvents(SDL_Event* events,int count,SDL_eventaction action,Uint32 first,Uint32 last) {
    static const auto original=sdl<decltype(&SDL_PeepEvents)>("SDL_PeepEvents");
    service(); return original(events,count,action,first,last);
}
extern "C" void SDL_PumpEvents() {
    static const auto original=sdl<decltype(&SDL_PumpEvents)>("SDL_PumpEvents");
    service(); original();
}
extern "C" void SDL_Delay(Uint32 milliseconds) {
    static const auto original=sdl<decltype(&SDL_Delay)>("SDL_Delay");
    service();
    while(milliseconds>40) { original(40); milliseconds-=40; service(); }
    original(milliseconds);
}
extern "C" void SDL_RenderPresent(SDL_Renderer* renderer) {
    static const auto original=sdl<decltype(&SDL_RenderPresent)>("SDL_RenderPresent");
    service(); original(renderer);
}
