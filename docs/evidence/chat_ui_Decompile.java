//@category Static source extraction
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.util.cparser.C.CParserUtils;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

public class chat_ui_Decompile extends GhidraScript {
    public void run() throws Exception {
        String[][] signatures = {
            {"004ad4f0", "char * __fastcall NpcDisplayName(int actor, unsigned int flags);"},
            {"004cf790", "void __fastcall CreateMenu(unsigned int color, char *title, int x, int y, int width, int height, int kind);"},
            {"004cf990", "void __fastcall AddMenuRow(int action, char *label);"},
            {"00516270", "void __fastcall Panel(int x, int y, int width, int height, char *title, unsigned int style, unsigned int flags);"},
            {"004f8f80", "void __fastcall Heading(char *text);"}
        };
        for (String[] signature : signatures)
            new ApplyFunctionSignatureCmd(toAddr(signature[0]),
                CParserUtils.parseSignature(null, currentProgram, signature[1], false),
                SourceType.USER_DEFINED).applyTo(currentProgram);
        String[] targets = {"00534150", "00534200", "005342c0", "00546200",
            "004ad4f0", "004f8f80"};
        DecompInterface dc = new DecompInterface();
        dc.toggleCCode(true);
        dc.openProgram(currentProgram);
        try (PrintWriter out = new PrintWriter(Files.newBufferedWriter(
                Path.of(getScriptArgs()[0]), StandardCharsets.UTF_8))) {
            out.println("/* Offline Windows 3.89.1 PE. VA, image base 00400000. */");
            for (String target : targets) {
                Function function = getFunctionAt(toAddr(target));
                DecompileResults result = dc.decompileFunction(function, 180, monitor);
                out.println("\n/* " + target + " */");
                out.println(result.getDecompiledFunction().getC());
                out.flush();
            }
        } finally {
            dc.dispose();
        }
    }
}
