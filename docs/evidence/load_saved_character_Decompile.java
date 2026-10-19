//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;

// Offline decompiler extraction only. Does not load or execute the target EXE.
public class load_saved_character_Decompile extends GhidraScript {
    public void run() throws Exception {
        DecompInterface decompiler = new DecompInterface();
        decompiler.toggleCCode(true);
        decompiler.openProgram(currentProgram);
        String[][] targets = {
            {"00524e90", "load_saved_character"},
            {"004cf790", "initialize_menu"},
            {"004cf990", "append_menu_row"},
            {"004cffb0", "draw_menu"},
            {"00515e70", "legacy_panel_title"},
            {"005157b0", "title_paragraph"},
            {"00525a90", "main_menu"}
        };
        try (PrintWriter output = new PrintWriter(Files.newBufferedWriter(
                Path.of(getScriptArgs()[0]), StandardCharsets.UTF_8))) {
            output.println("/* Ghidra 12.1.4 PUBLIC headless decompiler output, static PE analysis only. */");
            output.println("/* Preferred image base 0x400000; addresses below are VAs. */");
            for (String[] target : targets) {
                Function function = getFunctionAt(toAddr(target[0]));
                if (function == null) { disassemble(toAddr(target[0])); function = createFunction(toAddr(target[0]), target[1]); }
                DecompileResults result = decompiler.decompileFunction(function, 120, monitor);
                output.println("\n/* " + target[1] + "; VA 0x" + target[0] + " */");
                if (result.getDecompiledFunction() == null) output.println("/* " + result.getErrorMessage() + " */");
                else output.println(result.getDecompiledFunction().getC());
                output.flush();
            }
        } finally { decompiler.dispose(); }
    }
}
