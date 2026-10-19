//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;

// Offline PE decompiler extraction, adapted from setup_options_Decompile.
// It does not execute the target EXE or any delivery artifact.
public class startup_audio_Decompile extends GhidraScript {
    public void run() throws Exception {
        DecompInterface decompiler = new DecompInterface();
        decompiler.toggleCCode(true);
        decompiler.openProgram(currentProgram);
        String[][] targets = {
            {"0040ae30", "load_named_sample"},
            {"0040b100", "load_file_sample"},
            {"0040b3d0", "load_startup_samples"},
            {"0040c1c0", "load_and_play_intro"},
            {"00523df0", "startup_progress_display"},
            {"004d3c80", "wait_for_key"},
            {"004d3bf0", "wait_key_event"},
            {"004d1c00", "event_dispatch"},
            {"0050b720", "software_frame_present"},
            {"005800e0", "main_startup"},
            {"00523db0", "log_only"}
        };
        try (PrintWriter output = new PrintWriter(Files.newBufferedWriter(
                Path.of(getScriptArgs()[0]), StandardCharsets.UTF_8))) {
            output.println("/* Ghidra 12.1.4 PUBLIC headless decompiler output, static PE analysis only. */");
            output.println("/* Preferred image base 0x400000; addresses below are VAs. */");
            for (String[] target : targets) {
                Function function = getFunctionAt(toAddr(target[0]));
                if (function == null) {
                    disassemble(toAddr(target[0]));
                    function = createFunction(toAddr(target[0]), target[1]);
                }
                DecompileResults result = decompiler.decompileFunction(function, 120, monitor);
                output.println("\n/* " + target[1] + "; VA 0x" + target[0] + " */");
                if (result.getDecompiledFunction() == null)
                    output.println("/* " + result.getErrorMessage() + " */");
                else output.println(result.getDecompiledFunction().getC());
                output.flush();
                println("Extracted " + target[1] + " at VA 0x" + target[0]);
            }
        } finally { decompiler.dispose(); }
    }
}
