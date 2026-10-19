//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;

// Offline PE decompilation only; never executes the game or delivery artifacts.
public class character_profile_Decompile extends GhidraScript {
 public void run() throws Exception {
  DecompInterface dc=new DecompInterface(); dc.toggleCCode(true); dc.openProgram(currentProgram);
  String[][] targets={
   {"0040f210","profile_footer"},
   {"0040f300","profile_sex"},
   {"0040f4f0","profile_culture"},
   {"00411870","profile_name"},
   {"00412ed0","profile_heading"},
   {"00412ca0","profile_stages"},
   {"0050f5b0","native_name_input"},
   {"00562300","native_paragraph_append"},
   {"004cf790","native_menu_init"},
   {"004cffb0","native_menu_draw"}
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
