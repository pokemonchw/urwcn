import ghidra.app.decompiler.DecompInterface;
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.util.cparser.C.CParserUtils;
import ghidra.program.model.symbol.SourceType;
import java.io.PrintWriter;
public class GameTaskDecompile extends GhidraScript {
 public void run() throws Exception {
  String[][] signatures={
   {"00562300","void __fastcall Words(int reset, char *text);"},
   {"0050e5a0","void __fastcall ShowText(int x, int y, char *text, unsigned int color, unsigned int outline);"},
   {"0050eb40","void __fastcall Paragraph(int x, int y, int width, int height, unsigned int color, unsigned int outline);"},
   {"004cf790","void __fastcall CreateMenu(unsigned int color, char *title, int x, int y, int width, int height, int kind);"},
   {"004cf990","void __fastcall AddMenuRow(int action, char *label);"},
   {"00516270","void __fastcall Panel(int x, int y, int width, int height, char *title, unsigned int style, unsigned int flags);"}
  };
  for(String[] s:signatures) new ApplyFunctionSignatureCmd(toAddr(s[0]),CParserUtils.parseSignature(null,currentProgram,s[1],false),SourceType.USER_DEFINED).applyTo(currentProgram);
  DecompInterface dc=new DecompInterface();dc.openProgram(currentProgram);
  String[] args=getScriptArgs();
  try(PrintWriter out=new PrintWriter(args[0],"UTF-8")) {
   for(int i=1;i<args.length;i++) {
    var f=getFunctionContaining(toAddr(args[i]));out.println("\n/* "+f+" */");
    out.println(dc.decompileFunction(f,180,monitor).getDecompiledFunction().getC());out.flush();
    for(var r:getReferencesTo(f.getEntryPoint())) out.println("/* caller "+r.getFromAddress()+" "+getFunctionContaining(r.getFromAddress())+" */");
   }
  } finally {dc.dispose();}
 }
}
