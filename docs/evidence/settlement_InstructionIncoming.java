//@category Static source extraction
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
public class settlement_InstructionIncoming extends GhidraScript {
 public void run() throws Exception {
  String[] args=getScriptArgs();
  try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(Path.of(args[0]),StandardCharsets.UTF_8))) {
   for(int i=1;i<args.length;i++) {
    String[] item=args[i].split(":");Address first=toAddr(item[0]);int length=Integer.parseInt(item[1]);
    out.println("RANGE\t"+first+"\t"+length);
    for(int offset=0;offset<length;offset++) {
     Address at=first.add(offset);Instruction instruction=getInstructionAt(at);
     if(instruction!=null)out.println("INSTRUCTION\t"+at+"\t"+instruction.getLength()+"\t"+instruction);
     for(Reference reference:getReferencesTo(at))
      out.println("INCOMING\t"+at+"\t"+reference.getFromAddress()+"\t"+reference.getReferenceType());
    }
   }
  }
 }
}
