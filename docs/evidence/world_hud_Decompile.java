//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
// Offline extraction of original PE instructions. Does not execute target code.
public class world_hud_Decompile extends GhidraScript {
 public void run() throws Exception {
  DecompInterface dc=new DecompInterface(); dc.toggleCCode(true); dc.openProgram(currentProgram);
  String[][] targets={{"00503640","world_calendar_hud"},{"0048e3d0","world_place_part"},{"0048e420","world_place_combined"},{"0048e4f0","world_place_context"},{"0049b040","world_region_description"},{"004a8f50","world_place_generator"},{"004a3e70","world_place_lexicon_init"},{"0049ad00","world_cultural_region"},{"0050e910","native_centered_wrap"},{"0048fe90","world_scale_label"}};
  try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(Path.of(getScriptArgs()[0]),StandardCharsets.UTF_8))){
   out.println("/* Read-only original PE decompilation. Preferred image base 0x400000. */");
   for(String[] t:targets){Function f=getFunctionContaining(toAddr(t[0]));if(f==null){disassemble(toAddr(t[0]));f=createFunction(toAddr(t[0]),t[1]);}DecompileResults r=dc.decompileFunction(f,120,monitor);out.println("\n/* "+t[1]+"; VA 0x"+f.getEntryPoint()+" */");if(r.getDecompiledFunction()==null)out.println("/* "+r.getErrorMessage()+" */");else out.println(r.getDecompiledFunction().getC());out.flush();println("Extracted "+t[1]+" at "+f.getEntryPoint());}
  }finally{dc.dispose();}
 }
}

