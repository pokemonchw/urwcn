//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.util.cparser.C.CParserUtils;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.*;

public class confirmation_AllText extends GhidraScript {
    public void run() throws Exception {
        String[][] signatures={
            {"004fb8a0","unsigned char __fastcall ConfirmYesNo(char *text);"},
            {"004fbb10","unsigned char __fastcall ConfirmYesEscape(char *text);"},
            {"004cf790","void __fastcall CreateMenu(unsigned int color, char *title, int x, int y, int width, int height, int kind);"},
            {"004cf990","void __fastcall AddMenuRow(int action, char *label);"},
            {"004cfaf0","void __fastcall AddButton(int action, int x, int y, char *label);"},
            {"004cffb0","void DrawMenu(void);"},
            {"004d0650","void __fastcall SelectMenuRow(int row, int mode);"},
            {"004d1120","int WaitMenu(void);"},
            {"00514680","void __fastcall DrawButton(int x, int y, char *label);"},
            {"00516270","void __fastcall Panel(int x, int y, int width, int height, char *title, unsigned int style, unsigned int flags);"},
            {"0050e5a0","void __fastcall ShowText(int x, int y, char *text, int spacing, unsigned int flags);"}
        };
        for(String[] signature:signatures)
            new ApplyFunctionSignatureCmd(toAddr(signature[0]),CParserUtils.parseSignature(null,currentProgram,signature[1],false),SourceType.USER_DEFINED).applyTo(currentProgram);
        Path directory=Path.of(getScriptArgs()[0]);
        TreeMap<Long,Function> functions=new TreeMap<>();
        try(PrintWriter refs=new PrintWriter(Files.newBufferedWriter(directory.resolve("incoming.tsv"),StandardCharsets.UTF_8))) {
            refs.println("target_va\tsite_va\ttype\tcaller_va");
            for(long sink:new long[]{0x4fb8a0,0x4fbb10}) {
                functions.put(sink,getFunctionAt(toAddr(sink)));
                for(Reference ref:getReferencesTo(toAddr(sink))) {
                    Function caller=getFunctionContaining(ref.getFromAddress());
                    refs.println(String.format("%08x\t%s\t%s\t%s",sink,ref.getFromAddress(),ref.getReferenceType(),caller==null?"":caller.getEntryPoint()));
                    if(caller!=null) functions.put(caller.getEntryPoint().getOffset(),caller);
                }
            }
        }
        functions.put(0x508730L,getFunctionAt(toAddr(0x508730)));
        for(long target:new long[]{0x4cfaf0,0x4cffb0,0x4d0650,0x4d1120,0x514680})
            functions.put(target,getFunctionAt(toAddr(target)));
        DecompInterface dc=new DecompInterface();dc.toggleCCode(true);dc.openProgram(currentProgram);
        try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(directory.resolve("all-text-ghidra.c"),StandardCharsets.UTF_8));
            PrintWriter refs=new PrintWriter(Files.newBufferedWriter(directory.resolve("source-references.tsv"),StandardCharsets.UTF_8))) {
            refs.println("function_va\tsite_va\ttarget_va\ttext");
            for(Function function:functions.values()) {
                // Full 56FE30 decompilation timed out in this extraction.
                // Its 66 query branches are extracted as native instruction
                // windows and source references, independently of C output.
                if(function.getEntryPoint().getOffset()!=0x56fe30) {
                    DecompileResults result=dc.decompileFunction(function,180,monitor);
                    out.println("\n/* "+function.getEntryPoint()+" */\n"+result.getDecompiledFunction().getC());out.flush();
                }
                for(Instruction instruction:currentProgram.getListing().getInstructions(function.getBody(),true))
                    for(Reference ref:instruction.getReferencesFrom()) {
                        long va=ref.getToAddress().getOffset();
                        if(va<0x58c000 || va>=0x5e2000) continue;
                        ByteArrayOutputStream bytes=new ByteArrayOutputStream();
                        for(int i=0;i<4096;++i) {byte b=getByte(toAddr(va+i));if(b==0) break;bytes.write(b);}
                        String value=bytes.toString("ISO-8859-1").replace("\r","\\r").replace("\n","\\n").replace("\t","\\t");
                        refs.println(function.getEntryPoint()+"\t"+instruction.getAddress()+"\t"+ref.getToAddress()+"\t"+value);
                    }
                println("Extracted "+function.getEntryPoint());
            }
        } finally {dc.dispose();}
    }
}
