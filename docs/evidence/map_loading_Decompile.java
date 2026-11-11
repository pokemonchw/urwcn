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

public class map_loading_Decompile extends GhidraScript {
    public void run() throws Exception {
        String[][] signatures={
            {"0050e5a0","void __fastcall ShowText(int x, int y, char *text, unsigned int color, unsigned int outline);"},
            {"004fa7b0","void __fastcall MapLoadingProgress(int progress);"}
        };
        for(String[] signature:signatures)
            new ApplyFunctionSignatureCmd(toAddr(signature[0]),
                CParserUtils.parseSignature(null,currentProgram,signature[1],false),
                SourceType.USER_DEFINED).applyTo(currentProgram);
        DecompInterface dc=new DecompInterface();dc.toggleCCode(true);dc.openProgram(currentProgram);
        try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(
                Path.of(getScriptArgs()[0]),StandardCharsets.UTF_8))) {
            for(String target:new String[]{"004fa7b0","0050e5a0"}) {
                out.println("\n/* "+target+" */");
                out.println(dc.decompileFunction(getFunctionAt(toAddr(target)),180,monitor)
                    .getDecompiledFunction().getC());out.flush();
                println("Extracted "+target);
            }
            out.println("\n/* Map loading progress callers */");
            for(var reference:getReferencesTo(toAddr("004fa7b0")))
                out.println(reference.getFromAddress()+" "+reference.getReferenceType()+" "+
                    getFunctionContaining(reference.getFromAddress()));
        } finally {dc.dispose();}
    }
}
