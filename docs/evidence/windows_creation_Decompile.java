//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
public class windows_creation_Decompile extends GhidraScript {
 public void run() throws Exception {
  DecompInterface d=new DecompInterface(); d.openProgram(currentProgram);
  String[][] targets={{"004105c0","get_camp"},{"004107f0","draw_campselgfx"},{"004108a0","SelectCampaign"},{"00410d40","game_course"},{"00460450","NaytaMittakaava"},{"00460b60","kartta_main"},{"00460ad0","rndworld_screen"},{"004e6e90","endgame"},{"004cfaf0","LIST_ButtonSpotEntry"},{"004d1120","LIST_Go"},{"0040f210","crtplr_info"}};
  try(PrintWriter o=new PrintWriter(Files.newBufferedWriter(Path.of(getScriptArgs()[0]),StandardCharsets.UTF_8))){
   o.println("/* Read-only PE static decompilation. Addresses are VAs; subtract 0x400000. */");
   for(String[] t:targets){Function f=getFunctionAt(toAddr(t[0]));o.println("\n/* "+t[1]+" VA="+t[0]+" */");if(f==null){o.println("/* No defined function; no program modification. */");continue;}DecompileResults r=d.decompileFunction(f,120,monitor);o.println(r.getDecompiledFunction()==null?r.getErrorMessage():r.getDecompiledFunction().getC());o.flush();}
  }finally{d.dispose();}
 }
}
