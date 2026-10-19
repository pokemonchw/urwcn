//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
public class creation_complete_Decompile extends GhidraScript {
 public void run() throws Exception {
  DecompInterface decompiler = new DecompInterface();
  decompiler.openProgram(currentProgram);
  String[][] targets = {{"00412f80", "character_creation"}, {"005127c0", "completion_native_background"}};
  try (PrintWriter output = new PrintWriter(Files.newBufferedWriter(Path.of(getScriptArgs()[0]), StandardCharsets.UTF_8))) {
   output.println("/* Read-only PE static decompilation. Addresses are VAs; subtract 0x400000. */");
   for (String[] target : targets) {
    Function function = getFunctionAt(toAddr(target[0]));
    output.println("\n/* " + target[1] + " VA=" + target[0] + " */");
    DecompileResults result = decompiler.decompileFunction(function, 120, monitor);
    output.println(result.getDecompiledFunction().getC());
    output.flush();
   }
  } finally { decompiler.dispose(); }
 }
}
