//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import java.io.*;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
public class conversation_Helpers extends GhidraScript {
 public void run() throws Exception {
  DecompInterface dc=new DecompInterface();dc.toggleCCode(true);dc.openProgram(currentProgram);
  try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(Path.of(getScriptArgs()[0]),StandardCharsets.UTF_8))) {
   for(long va:new long[]{0x55eff0,0x55f400,0x5627a0,0x562930,0x55dfc0,0x55e000,0x452640,0x451770,0x4199b0,0x419610,0x538ea0,0x562be0,0x561b00}) {
    var f=getFunctionContaining(toAddr(va));var result=dc.decompileFunction(f,180,monitor);
    out.println("\n/* Function "+f.getEntryPoint()+" */\n"+result.getDecompiledFunction().getC());out.flush();println("Extracted "+f.getEntryPoint());
   }
  } finally {dc.dispose();}
 }
}
