//@category Static source extraction
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.symbol.Reference;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
public class settlement_InlineBoundaries extends GhidraScript {
    public void run() throws Exception {
        String[] args=getScriptArgs();
        try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(Path.of(args[1]),StandardCharsets.UTF_8))) {
            out.println("owner\thook\tstart\tbytes\tdecoded_end\tinstructions\tinterior_flow_references");
            for(String line:Files.readAllLines(Path.of(args[0]),StandardCharsets.UTF_8)) {
                if(line.startsWith("owner\t"))continue;
                String[] row=line.split("\t");Address start=toAddr(row[2]);int length=Integer.parseInt(row[3]);
                Address end=start.add(length),cursor=start;StringBuilder instructions=new StringBuilder(),references=new StringBuilder();
                while(cursor.compareTo(end)<0) {
                    Instruction instruction=getInstructionAt(cursor);
                    if(instruction==null) {instructions.append(cursor).append(": no instruction; ");break;}
                    instructions.append(cursor).append(": ").append(instruction).append("; ");cursor=cursor.add(instruction.getLength());
                }
                for(int offset=1;offset<length;++offset) {
                    Address address=start.add(offset);
                    for(Reference ref:getReferencesTo(address)) {
                        if(ref.getReferenceType().isFlow()) references.append(ref.getFromAddress()).append("->").append(address).append(" ").append(ref.getReferenceType()).append("; ");
                    }
                }
                out.println(row[0]+"\t"+row[1]+"\t"+start+"\t"+length+"\t"+cursor+"\t"+instructions+"\t"+references);
            }
        }
    }
}
