//@category Static source extraction
import ghidra.app.script.GhidraScript;import ghidra.program.model.listing.*;import ghidra.program.model.symbol.*;import java.io.*;import java.nio.charset.StandardCharsets;import java.nio.file.*;
public class settlement_DataRefs extends GhidraScript {
 public void run()throws Exception {String[]args=getScriptArgs();try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(Path.of(args[0]),StandardCharsets.UTF_8))){out.println("target\tfrom\tcaller\ttype\tinstruction");for(int i=1;i<args.length;i++)for(Reference r:getReferencesTo(toAddr(args[i]))){Function f=getFunctionContaining(r.getFromAddress());out.println(args[i]+"\t"+r.getFromAddress()+"\t"+(f==null?"":f.getEntryPoint())+"\t"+r.getReferenceType()+"\t"+getInstructionAt(r.getFromAddress()));}}}
}
