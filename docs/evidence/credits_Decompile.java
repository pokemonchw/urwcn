//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;

// Offline PE decompilation only. The target executable is never executed.
public class credits_Decompile extends GhidraScript {
 public void run() throws Exception {
  DecompInterface dc = new DecompInterface();
  dc.toggleCCode(true); dc.openProgram(currentProgram);
  String[][] targets = {
   {"005244f0", "thanks_and_credits"}, {"00525a90", "main_menu_dispatch"},
   {"00525920", "main_menu_rows"},
   {"00516270", "native_panel_title"}, {"0050eb40", "native_paragraph"},
   {"00562300", "native_paragraph_append"}, {"005620c0", "native_paragraph_reset"},
   {"0050e5a0", "native_text_draw"}, {"00514680", "native_button"},
   {"004d3c80", "native_key_wait"}, {"004d3bf0", "native_key_poll"},
   {"004d1c00", "native_event_consumer"}, {"0050b720", "native_software_repaint"}
  };
  try (PrintWriter out = new PrintWriter(Files.newBufferedWriter(Path.of(getScriptArgs()[0]), StandardCharsets.UTF_8))) {
   out.println("/* Ghidra 12.1.4 PUBLIC static PE decompilation; preferred image base 0x400000. */");
   for (String[] t : targets) {
    Function f = getFunctionAt(toAddr(t[0]));
    if (f == null) { disassemble(toAddr(t[0])); f = createFunction(toAddr(t[0]), t[1]); }
    DecompileResults r = dc.decompileFunction(f, 120, monitor);
    out.println("\n/* " + t[1] + "; VA 0x" + t[0] + " */");
    if (r.getDecompiledFunction() == null) out.println("/* " + r.getErrorMessage() + " */");
    else out.println(r.getDecompiledFunction().getC());
    out.flush(); println("Extracted " + t[1] + " at VA 0x" + t[0]);
   }
  } finally { dc.dispose(); }
 }
}
