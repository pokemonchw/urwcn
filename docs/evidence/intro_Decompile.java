//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;

// Offline PE decompilation; does not execute the target or delivery artifacts.
public class intro_Decompile extends GhidraScript {
 public void run() throws Exception {
  DecompInterface dc=new DecompInterface(); dc.toggleCCode(true); dc.openProgram(currentProgram);
  String[][] targets={
   {"005254c0","intro_sequence"},{"00525370","first_winter_story"},
   {"00525240","story_line_fade"},{"00524710","intro_version_logo"},
   {"00512980","draw_image"},{"005127c0","draw_scaled_background"},
   {"0050e5a0","draw_text"},{"004d25e0","intro_input_poll"},
   {"0050d5b0","native_surface_fade"},{"0050b9f0","clear_native_frame"},
   {"0050b3c0","consume_drawing_records"},{"0050af90","upload_frame"},
   {"005800e0","startup_caller"},{"00524690","actual_version_source"},
   {"00512260","image_leaf"},{"0040e380","stdout_diagnostic"},
   {"0050ac30","fprintf_diagnostic"}
  };
  try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(Path.of(getScriptArgs()[0]), StandardCharsets.UTF_8))){
   out.println("/* Ghidra 12.1.4 PUBLIC static PE decompiler extraction. Image base 0x400000. */");
   for(String[] t:targets){
    Function f=getFunctionAt(toAddr(t[0]));
    if(f==null){disassemble(toAddr(t[0]));f=createFunction(toAddr(t[0]),t[1]);}
    DecompileResults result=dc.decompileFunction(f,120,monitor);
    out.println("\n/* "+t[1]+"; VA 0x"+t[0]+" */");
    if(result.getDecompiledFunction()==null) out.println("/* "+result.getErrorMessage()+" */");
    else out.println(result.getDecompiledFunction().getC());
    out.flush();println("Extracted "+t[1]+" at VA 0x"+t[0]);
   }
  }finally{dc.dispose();}
 }
}