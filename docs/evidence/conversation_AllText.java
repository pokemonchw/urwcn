//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.util.cparser.C.CParserUtils;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.pcode.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.*;

public class conversation_AllText extends GhidraScript {
    String textAt(long va) throws Exception {
        if (va < 0x58c000L || va >= 0x5e2000L) return "";
        ByteArrayOutputStream bytes = new ByteArrayOutputStream();
        for (int i=0; i<4096; ++i) {
            byte b=getByte(toAddr(va+i));
            if (b==0) return bytes.toString("ISO-8859-1").replace("\r","\\r").replace("\n","\\n").replace("\t","\\t");
            bytes.write(b);
        }
        return "";
    }
    public void run() throws Exception {
        String[][] signatures={
            {"005339b0","void __fastcall NpcSpeech(char *text);"},
            {"00534350","void __fastcall PlayerSpeech(char *text);"},
            {"00534c70","int __fastcall ChatOption(int unused, char *label, char *command);"},
            {"00534d90","void __fastcall ChatEmote(int mode, char *text);"},
            {"00561480","char * __fastcall ChatResource(char *key);"},
            {"00561b00","char * __fastcall MessageResource(char *key);"},
            {"004ad4f0","char * __fastcall NpcDisplayName(int actor, unsigned int flags);"},
            {"004cf790","void __fastcall CreateMenu(unsigned int color, char *title, int x, int y, int width, int height, int kind);"},
            {"004cf990","void __fastcall AddMenuRow(int action, char *label);"},
            {"00516270","void __fastcall Panel(int x, int y, int width, int height, char *title, unsigned int style, unsigned int flags);"}
        };
        for(String[] signature:signatures)
            new ApplyFunctionSignatureCmd(toAddr(signature[0]),CParserUtils.parseSignature(null,currentProgram,signature[1],false),SourceType.USER_DEFINED).applyTo(currentProgram);
        long[] sinks={0x5339b0,0x534350,0x534c70,0x534d90};
        TreeMap<Long,Function> functions=new TreeMap<>();
        Path directory=Path.of(getScriptArgs()[0]);
        try(PrintWriter refs=new PrintWriter(Files.newBufferedWriter(directory.resolve("incoming.tsv"),StandardCharsets.UTF_8))) {
            refs.println("target_va\tsite_va\ttype\tcaller_va");
            for(long sink:sinks) {
                functions.put(sink,getFunctionAt(toAddr(sink)));
                for(Reference ref:getReferencesTo(toAddr(sink))) {
                    Function caller=getFunctionContaining(ref.getFromAddress());
                    refs.println(String.format("%08x\t%s\t%s\t%s",sink,ref.getFromAddress(),ref.getReferenceType(),caller==null?"":caller.getEntryPoint()));
                    if(caller!=null) functions.put(caller.getEntryPoint().getOffset(),caller);
                }
            }
        }
        FunctionIterator all=currentProgram.getFunctionManager().getFunctions(toAddr(0x5337f0),true);
        while(all.hasNext()) {Function f=all.next();if(f.getEntryPoint().getOffset()>=0x5471c0) break;functions.put(f.getEntryPoint().getOffset(),f);}
        for(long helper:new long[]{0x561480,0x561330,0x5601c0,0x4846c0,0x5344d0}) functions.put(helper,getFunctionAt(toAddr(helper)));
        DecompInterface dc=new DecompInterface();dc.toggleCCode(true);dc.openProgram(currentProgram);
        try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(directory.resolve("all-text-ghidra.c"),StandardCharsets.UTF_8));
            PrintWriter calls=new PrintWriter(Files.newBufferedWriter(directory.resolve("calls.tsv"),StandardCharsets.UTF_8));
            PrintWriter strings=new PrintWriter(Files.newBufferedWriter(directory.resolve("string-refs.tsv"),StandardCharsets.UTF_8))) {
            calls.println("caller_va\tsite_va\ttarget_va\tinputs");strings.println("caller_va\tsite_va\tstring_va\ttext");int index=0;
            for(Function f:functions.values()) {
                DecompileResults result=dc.decompileFunction(f,180,monitor);
                out.println("\n/* Function "+f.getEntryPoint()+" */");out.println(result.getDecompiledFunction().getC());out.flush();
                Iterator<PcodeOpAST> ops=result.getHighFunction().getPcodeOps();
                while(ops.hasNext()) {
                    PcodeOpAST op=ops.next();if(op.getOpcode()!=PcodeOp.CALL) continue;
                    StringBuilder inputs=new StringBuilder();
                    for(int i=1;i<op.getNumInputs();++i) {Varnode v=op.getInput(i);inputs.append(i).append(':').append(v);if(v.isConstant()) inputs.append("=").append(textAt(v.getOffset()));inputs.append(" | ");}
                    calls.println(f.getEntryPoint()+"\t"+op.getSeqnum().getTarget()+"\t"+String.format("%08x",op.getInput(0).getOffset())+"\t"+inputs);
                }
                InstructionIterator instructions=currentProgram.getListing().getInstructions(f.getBody(),true);
                while(instructions.hasNext()) {Instruction ins=instructions.next();for(Reference ref:ins.getReferencesFrom()) {String text=textAt(ref.getToAddress().getOffset());if(!text.isEmpty()) strings.println(f.getEntryPoint()+"\t"+ins.getAddress()+"\t"+ref.getToAddress()+"\t"+text);}}
                calls.flush();strings.flush();println("Extracted "+(++index)+"/"+functions.size()+" "+f.getEntryPoint());
            }
        } finally {dc.dispose();}
    }
}
