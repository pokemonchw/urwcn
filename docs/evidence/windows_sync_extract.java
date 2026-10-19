//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.*;
public class windows_sync_extract extends GhidraScript {
 public void run() throws Exception {
  DecompInterface dc=new DecompInterface();dc.toggleCCode(true);dc.openProgram(currentProgram);
  TreeMap<Long,Function> fs=new TreeMap<>();
  long[] literals={0x58f6b8L,0x58f628L,0x5a6d44L,0x5a6d58L,0x5a6e68L,0x594fd4L,0x5954d8L,0x5954a8L,0x594fa0L,0x58f6d4L};
  for(long value:literals) for(Reference r:getReferencesTo(toAddr(value))) {
   Function f=getFunctionContaining(r.getFromAddress());if(f!=null)fs.put(f.getEntryPoint().getOffset(),f);
  }
  for(int a=1;a<getScriptArgs().length;++a) for(String s:getScriptArgs()[a].split(",")) {
   Function f=getFunctionAt(toAddr(s));if(f!=null)fs.put(f.getEntryPoint().getOffset(),f);
  }
  try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(Path.of(getScriptArgs()[0]),StandardCharsets.UTF_8))){
   for(Function f:fs.values()) {
    out.println("\n/* "+f.getName()+" VA "+f.getEntryPoint()+" */");
    DecompileResults r=dc.decompileFunction(f,90,monitor);
    out.println(r.getDecompiledFunction()==null?r.getErrorMessage():r.getDecompiledFunction().getC());out.flush();
   }
  }finally{dc.dispose();}
 }
}
