#include "file_identity.h"
#include <unistd.h>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <vector>

int main(int argc,char** argv) {
    try {
        const auto root=std::filesystem::canonical("/proc/self/exe").parent_path();
        std::ifstream configuration(root/"package/linux-game-path.txt");
        std::string game;
        std::getline(configuration,game);
        int first_argument=1;
        if(argc>=3 && std::strcmp(argv[1],"--game")==0) { game=argv[2]; first_argument=3; }
        const auto executable=std::filesystem::canonical(game);
        if(uwcn::linux_host::file_sha256(executable)!=uwcn::linux_host::game_sha256)
            throw std::runtime_error("Game identity differs from the Linux 3.89 Steam profile: "+executable.string());
        const std::string package=(root/"package").string();
        const std::string font=(root/"package/fonts/SourceHanSans.ttc").string();
        std::string preload=(root/"package/uwcn_loader.dll").string();
        if(const char* existing=std::getenv("LD_PRELOAD"); existing && *existing) preload+=' '+std::string(existing);
        std::string libraries=(root/"package/lib").string();
        if(const char* existing=std::getenv("LD_LIBRARY_PATH"); existing && *existing) libraries+=':'+std::string(existing);
        if(setenv("UWCN_PACKAGE",package.c_str(),1)!=0 || setenv("UWCN_FONT",font.c_str(),1)!=0 ||
           setenv("LD_PRELOAD",preload.c_str(),1)!=0 || setenv("LD_LIBRARY_PATH",libraries.c_str(),1)!=0)
            throw std::runtime_error(std::strerror(errno));
        std::filesystem::current_path(executable.parent_path());
        std::string command=executable.string();
        std::vector<char*> arguments{command.data()};
        for(int i=first_argument;i<argc;++i) arguments.push_back(argv[i]);
        arguments.push_back(nullptr);
        execv(command.c_str(),arguments.data());
        throw std::runtime_error("execv: "+std::string(std::strerror(errno)));
    } catch(const std::exception& error) {
        std::fprintf(stderr,"URWCN: %s\n",error.what());
        return 1;
    }
}
