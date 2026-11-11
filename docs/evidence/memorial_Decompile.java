//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.util.cparser.C.CParserUtils;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;

// Read-only extraction of the complete memorial/death producers and consumers.
public class memorial_Decompile extends GhidraScript {
 public void run() throws Exception {
  String[][] signatures={
   {"004010d0","int __cdecl sprintf(char *destination, const char *format, ...);"},
   {"004dd400","void __fastcall Memorial(int unused, int y, char *record, int detail);"},
   {"004de990","void __fastcall Ancestors(int mode);"},
   {"0050e5a0","void __fastcall ShowText(int x, int y, char *text, unsigned int color, unsigned int outline);"},
   {"0050eb40","int __fastcall Paragraph(int x, int y, int width, int height, unsigned int color, unsigned int outline);"},
   {"00562300","void __fastcall AppendWords(int reset, char *text);"},
   {"005157b0","void __fastcall Heading(int x, int y, int width, char *text, int style);"}
  };
  for(String[] signature:signatures)
   new ApplyFunctionSignatureCmd(toAddr(signature[0]),CParserUtils.parseSignature(null,currentProgram,signature[1],false),SourceType.USER_DEFINED).applyTo(currentProgram);
  DecompInterface dc=new DecompInterface();dc.toggleCCode(true);dc.openProgram(currentProgram);
  Path directory=Path.of(getScriptArgs()[0]);
  try(PrintWriter refs=new PrintWriter(Files.newBufferedWriter(directory.resolve("references.tsv"),StandardCharsets.UTF_8))) {
   refs.println("target_va\tsite_va\ttype\tcaller_va");
   for(int i=1;i<getScriptArgs().length;++i) {
    var address=toAddr(getScriptArgs()[i]);Function f=getFunctionContaining(address);
    var result=dc.decompileFunction(f,180,monitor);
    Files.writeString(directory.resolve(f.getEntryPoint()+".c"),result.getDecompiledFunction().getC(),StandardCharsets.UTF_8);
    for(var ref:getReferencesTo(f.getEntryPoint())) {
     var caller=getFunctionContaining(ref.getFromAddress());
     refs.println(f.getEntryPoint()+"\t"+ref.getFromAddress()+"\t"+ref.getReferenceType()+"\t"+(caller==null?"":caller.getEntryPoint()));
    }
    refs.flush();println("Extracted "+f.getEntryPoint());
   }
  } finally {dc.dispose();}
 }
}
