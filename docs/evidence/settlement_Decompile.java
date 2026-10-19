//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
public class settlement_Decompile extends GhidraScript {
 public void run() throws Exception {
  DecompInterface dc=new DecompInterface(); dc.toggleCCode(true); dc.openProgram(currentProgram);
  String[] targets={"004f6510","004f5b00","00499f00"};
  try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(Path.of(getScriptArgs()[0]),StandardCharsets.UTF_8))){
   out.println("/* Read-only PE static extraction. Image base 0x400000. */");
   for(String target:targets){Function f=getFunctionContaining(toAddr(target)); if(f==null){out.println("NO FUNCTION "+target); continue;} out.println("\n/* function at "+f.getEntryPoint()+", requested "+target+" */"); DecompileResults r=dc.decompileFunction(f,120,monitor); if(r.getDecompiledFunction()!=null)out.println(r.getDecompiledFunction().getC()); else out.println(r.getErrorMessage()); out.println("/* References to "+f.getEntryPoint()+":"); for(Reference ref:getReferencesTo(f.getEntryPoint())){Function caller=getFunctionContaining(ref.getFromAddress());out.println(ref.getFromAddress()+" "+ref.getReferenceType()+" caller "+(caller==null?"none":caller.getEntryPoint()));} out.println("*/"); out.flush(); }
  }finally{dc.dispose();}
 }
}
