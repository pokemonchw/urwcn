//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;

// Offline decompiler extraction only. Does not load or execute the target EXE.
public class setup_options_Decompile extends GhidraScript {
    public void run() throws Exception {
        DecompInterface decompiler = new DecompInterface();
        decompiler.toggleCCode(true);
        decompiler.openProgram(currentProgram);
        String[][] targets = {
            {"00505700", "setup_options"},
            {"0050e5a0", "draw_text"},
            {"00516270", "panel_title"},
            {"00562300", "footer_append"},
            {"00505520", "write_ini_setting"},
            {"00523f00", "read_ini_text"},
            {"00524030", "read_ini_yes"},
            {"005157b0", "title_paragraph"},
            {"00514680", "key_and_label_text"},
            {"0040f210", "bottom_panel"}
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
