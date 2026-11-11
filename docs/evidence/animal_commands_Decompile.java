//@category Static source extraction
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.script.GhidraScript;
import ghidra.app.util.cparser.C.CParserUtils;
import ghidra.program.model.symbol.SourceType;
import java.io.PrintWriter;

public class animal_commands_Decompile extends GhidraScript {
    public void run() throws Exception {
        String[][] signatures = {
            {"00543340", "void __fastcall AnimalCommands(int actor, int mode);"},
            {"005431d0", "void __fastcall NameAnimal(int actor);"},
            {"004ad4f0", "char * __fastcall NpcDisplayName(int actor, unsigned int flags);"},
            {"004a9790", "int __fastcall AnimalCommandState(int actor);"},
            {"00419070", "int __fastcall ActorX(int actor);"},
            {"004190c0", "int __fastcall ActorY(int actor);"},
            {"005002b0", "int __fastcall CommandMenu(char *title);"},
            {"004f6510", "void __fastcall Message(char *text);"},
            {"00561b00", "char * __fastcall MessageResource(char *key);"},
            {"0050f5b0", "char * __fastcall GetText(unsigned int color, unsigned int capacity);"}
        };
        for (String[] signature : signatures)
            new ApplyFunctionSignatureCmd(toAddr(signature[0]),
                CParserUtils.parseSignature(null, currentProgram, signature[1], false),
                SourceType.USER_DEFINED).applyTo(currentProgram);
        String[] targets = {"00543340", "005431d0", "004ad4f0", "004a9790",
            "005002b0", "00546200", "00424650", "00533620",
            "00424600", "00423df0", "004258b0", "00424720", "0048c160"};
        DecompInterface dc = new DecompInterface();
        dc.openProgram(currentProgram);
        try (PrintWriter out = new PrintWriter(getScriptArgs()[0], "UTF-8")) {
            out.println("/* Offline Windows x86 3.89.1, VA, image base 00400000. */");
            for (String target : targets) {
                var function = getFunctionAt(toAddr(target));
                out.println("\n/* " + target + " */");
                out.println(dc.decompileFunction(function, 180, monitor).getDecompiledFunction().getC());
                for (var reference : getReferencesTo(function.getEntryPoint()))
                    out.println("/* reference " + reference.getFromAddress() + " " + reference.getReferenceType() + " */");
                out.flush();
            }
        } finally { dc.dispose(); }
    }
}
