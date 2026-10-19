//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
public class hud_refresh_sideeffects extends GhidraScript {
 public void run() throws Exception {
  DecompInterface dc=new DecompInterface(); dc.toggleCCode(true); dc.openProgram(currentProgram);
  String[][] targets={{"004db1f0","fatigue_read"},{"004db060","carrying_read"},{"00451770","item_name_format"},{"004d4020","display_string_conversion"},{"0044b800","item_weight_format"}};
  try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(Path.of(getScriptArgs()[0]), StandardCharsets.UTF_8))){
   out.println("/* Read-only offline PE decompilation. Image base 0x400000. */");
   for(String[] t:targets){ Function f=getFunctionContaining(toAddr(t[0])); if(f==null){disassemble(toAddr(t[0]));f=createFunction(toAddr(t[0]),t[1]);} DecompileResults r=dc.decompileFunction(f,120,monitor); out.println("\n/* "+t[1]+"; VA 0x"+f.getEntryPoint()+" */"); if(r.getDecompiledFunction()==null)out.println("/* "+r.getErrorMessage()+" */");else out.println(r.getDecompiledFunction().getC()); out.flush();println("Extracted "+t[1]+" at "+f.getEntryPoint()); }
  } finally {dc.dispose();}
 }
}
