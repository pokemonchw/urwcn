//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
public class hud_right_Decompile extends GhidraScript {
 public void run() throws Exception {
  DecompInterface dc=new DecompInterface(); dc.toggleCCode(true); dc.openProgram(currentProgram);
  String[][] targets={{"004f8e20","hud_penalty_field"},{"004f9030","hud_name"},{"004f90d0","hud_command"},{"004f9200","hud_wielded"},{"004f9600","hud_repeat"},{"004f9910","hud_condition"},{"004fa2a0","hud_frame"},{"004fa860","hud_direction"},{"004faa30","hud_portrait"},{"0055f450","warmth_description"},{"0055ff80","nutrition_description"},{"005157b0","native_title"},{"0050e260","native_target_text"},{"00511560","native_renderer_text"},{"004905ef","world_bottom"},{"0048f100","world_upper"},{"0048a310","world_date"},{"0048a600","world_season"},{"0055e910","world_moon"},{"0055f8e0","world_time"},{"0050e910","native_center_text"}};
  try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(Path.of(getScriptArgs()[0]), StandardCharsets.UTF_8))){
   out.println("/* Read-only offline PE decompilation. Image base 0x400000. */");
   for(String[] t:targets){ Function f=getFunctionContaining(toAddr(t[0])); if(f==null){disassemble(toAddr(t[0]));f=createFunction(toAddr(t[0]),t[1]);} DecompileResults r=dc.decompileFunction(f,120,monitor); out.println("\n/* "+t[1]+"; VA 0x"+f.getEntryPoint()+" */"); if(r.getDecompiledFunction()==null)out.println("/* "+r.getErrorMessage()+" */");else out.println(r.getDecompiledFunction().getC()); out.flush();println("Extracted "+t[1]+" at "+f.getEntryPoint()); }
  } finally {dc.dispose();}
 }
}
