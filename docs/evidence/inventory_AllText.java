//@category Static source extraction
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.util.cparser.C.CParserUtils;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.SourceType;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Map;
import java.util.TreeMap;

public class inventory_AllText extends GhidraScript {
    public void run() throws Exception {
        String[] args = getScriptArgs();
        new ApplyFunctionSignatureCmd(toAddr("00455060"), CParserUtils.parseSignature(null, currentProgram,
            "int __fastcall Inventory(int mode, int selected, int x, int y, char *title, char *verb, unsigned int flags, unsigned int mask, int maximum);", false), SourceType.USER_DEFINED).applyTo(currentProgram);
        new ApplyFunctionSignatureCmd(toAddr("004581f0"), CParserUtils.parseSignature(null, currentProgram,
            "int __fastcall SelectInventory(char *title, char *verb, unsigned int flags, unsigned int mask, int maximum);", false), SourceType.USER_DEFINED).applyTo(currentProgram);
        Map<String, Function> functions = new TreeMap<>();
        try (PrintWriter refs = new PrintWriter(Files.newBufferedWriter(Path.of(args[1]), StandardCharsets.UTF_8))) {
            refs.println("target\tsite\tkind\tcaller");
            for (String root : new String[]{"00454160", "00455060", "004581f0"}) {
                Function f = getFunctionAt(toAddr(root));
                functions.put(f.getEntryPoint().toString(), f);
                for (Reference r : getReferencesTo(f.getEntryPoint())) {
                    Function caller = getFunctionContaining(r.getFromAddress());
                    refs.println(root + "\t" + r.getFromAddress() + "\t" + r.getReferenceType() + "\t" + (caller == null ? "" : caller.getEntryPoint()));
                    if (caller != null) functions.put(caller.getEntryPoint().toString(), caller);
                }
            }
        }
        for (String helper : new String[]{"004491f0", "0044b0b0", "0044b2f0", "0044bb90", "00453130", "004fbb10", "004fbd80", "005136f0"}) {
            Function f = getFunctionAt(toAddr(helper));
            functions.put(f.getEntryPoint().toString(), f);
        }
        DecompInterface dc = new DecompInterface();
        dc.toggleCCode(true);
        dc.openProgram(currentProgram);
        try (PrintWriter out = new PrintWriter(Files.newBufferedWriter(Path.of(args[0]), StandardCharsets.UTF_8))) {
            out.println("/* Offline Windows PE extraction. Image base " + currentProgram.getImageBase() + ". */");
            for (Function f : functions.values()) {
                out.println("\n/* Function " + f.getEntryPoint() + " */");
                // The first complete extraction timed out on this large debug
                // dispatcher. Its five inventory CALL windows are extracted
                // separately from the PE disassembly and listed in the TSV.
                if (f.getEntryPoint().equals(toAddr("0056fe30"))) {
                    out.println("/* Inventory inputs: 57BDD0, 57BE4F, 57BE8E, 57BF73, 57C7AB. See call-windows.asm. */");
                    continue;
                }
                DecompileResults r = dc.decompileFunction(f, 180, monitor);
                out.println(r.getDecompiledFunction() == null ? "/* " + r.getErrorMessage() + " */" : r.getDecompiledFunction().getC());
                out.flush();
                println("Extracted " + f.getEntryPoint());
            }
        } finally {
            dc.dispose();
        }
    }
}
