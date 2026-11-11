//@category Static source extraction
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.util.cparser.C.CParserUtils;
import ghidra.program.model.symbol.SourceType;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

public class load_progress_Decompile extends GhidraScript {
    public void run() throws Exception {
        String[][] signatures={
            {"0050e5a0","void __fastcall ShowText(int x, int y, char *text, unsigned int color, unsigned int outline);"},
            {"00562300","void __fastcall ParseText(int reset, char *text);"},
            {"0050eb40","void __fastcall DrawParagraph(int x, int y, int width, int height, unsigned int color, unsigned int outline);"}
        };
        for(String[] signature:signatures)
            new ApplyFunctionSignatureCmd(toAddr(signature[0]),
                CParserUtils.parseSignature(null,currentProgram,signature[1],false),
                SourceType.USER_DEFINED).applyTo(currentProgram);
        DecompInterface dc=new DecompInterface();dc.toggleCCode(true);dc.openProgram(currentProgram);
        try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(
                Path.of(getScriptArgs()[0]),StandardCharsets.UTF_8))) {
            for(String target:new String[]{"0057e4c0","00562300","0050eb40"}) {
                out.println("\n/* "+target+" */");
                out.println(dc.decompileFunction(getFunctionAt(toAddr(target)),180,monitor)
                    .getDecompiledFunction().getC());out.flush();
                println("Extracted "+target);
            }
        } finally {dc.dispose();}
    }
}
