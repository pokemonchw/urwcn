//@category Static source extraction
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.app.util.cparser.C.CParserUtils;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

public class direction_dialog_Decompile extends GhidraScript {
    public void run() throws Exception {
        String[][] signatures = {
            {"004f7820", "unsigned char __fastcall ChooseDirection(unsigned char mode, char *title);"},
            {"004f8740", "unsigned char __fastcall ChooseTerrain(char *title, char *terrain);"},
            {"004f88c0", "unsigned char __fastcall ChooseEntity(char *title, int type, unsigned int *x, unsigned int *y, unsigned char mode);"},
            {"004f8bc0", "unsigned char __fastcall ChooseLocation(char *title);"},
            {"004d3db0", "char * __fastcall UppercaseDisplay(char *text);"},
            {"00514a20", "void CreatureCycleHint(void);"},
            {"00562300", "void __fastcall ParseWords(int reset, char *text);"}
        };
        for (String[] signature : signatures)
            new ApplyFunctionSignatureCmd(toAddr(signature[0]),
                CParserUtils.parseSignature(null, currentProgram, signature[1], false),
                SourceType.USER_DEFINED).applyTo(currentProgram);
        DecompInterface dc = new DecompInterface();
        dc.toggleCCode(true);
        dc.openProgram(currentProgram);
        try (PrintWriter out = new PrintWriter(Files.newBufferedWriter(
                Path.of(getScriptArgs()[0]), StandardCharsets.UTF_8))) {
            out.println("/* Offline Windows 3.89.1 PE. VA, image base 00400000. */");
            for (String[] signature : signatures) {
                Function f = getFunctionAt(toAddr(signature[0]));
                DecompileResults result = dc.decompileFunction(f, 180, monitor);
                out.println("\n/* " + signature[0] + " */");
                out.println(result.getDecompiledFunction().getC());
                out.flush();
            }
        } finally {
            dc.dispose();
        }
    }
}
