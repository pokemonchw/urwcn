//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.util.cparser.C.CParserUtils;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.pcode.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.*;

// Offline extraction only. Function signatures are applied in the read-only
// Ghidra program, never to the PE or the game process.
public class conversation_Operands extends GhidraScript {
 String expression(Varnode value,Set<Varnode> path,int depth) {
  if(value.isConstant()) return String.format("0x%x",value.getOffset());
  if(value.isAddress()) return value.getAddress().toString();
  if(depth==8 || path.contains(value) || value.getDef()==null) return value.toString();
  Set<Varnode> next=new HashSet<>(path);next.add(value);
  PcodeOp op=value.getDef();StringBuilder result=new StringBuilder(op.getMnemonic()).append('(');
  for(int i=0;i<op.getNumInputs();++i) {
   if(i>0) result.append(',');result.append(expression(op.getInput(i),next,depth+1));
  }
  return result.append(')').toString();
 }
 public void run() throws Exception {
  String[][] signatures={
   {"005339b0","void __fastcall NpcSpeech(char *text);"},
   {"00534350","void __fastcall PlayerSpeech(char *text);"},
   {"00534c70","int __fastcall ChatOption(int unused, char *label, char *command);"},
   {"00534d90","void __fastcall ChatEmote(int mode, char *text);"},
   {"00561480","char * __fastcall ChatResource(char *key);"},
   {"00561b00","char * __fastcall MessageResource(char *key);"},
   {"004ad4f0","char * __fastcall NpcDisplayName(int actor, unsigned int flags);"},
   {"004cf790","void __fastcall CreateMenu(unsigned int color, char *title, int x, int y, int width, int height, int kind);"},
   {"004cf990","void __fastcall AddMenuRow(int action, char *label);"},
   {"004010d0","int __cdecl sprintf(char *destination, const char *format, ...);"},
   {"00526430","int __fastcall PreferredWeapon(int actor, int order);"},
   {"0055e9f0","char * __fastcall SkillGrade(int rating);"},
   {"0055ea60","char * __fastcall SmithGrade(int rating);"},
   {"004d4020","char * __fastcall Lowercase(char *text);"},
   {"0055eff0","char * __fastcall Plural(char *text);"},
   {"0055f400","char * __fastcall Singular(char *text);"}
  };
  for(String[] signature:signatures)
   new ApplyFunctionSignatureCmd(toAddr(signature[0]),CParserUtils.parseSignature(null,currentProgram,signature[1],false),SourceType.USER_DEFINED).applyTo(currentProgram);
  Path directory=Path.of(getScriptArgs()[0]);
  TreeMap<Long,Function> functions=new TreeMap<>();
  for(int i=1;i<getScriptArgs().length;++i) {
   String target=getScriptArgs()[i];
   if(target.startsWith("callers:")) {
    long sink=Long.parseLong(target.substring(8),16);
    for(Reference reference:getReferencesTo(toAddr(sink))) {
     if(!reference.getReferenceType().isCall()) continue;
     Function caller=getFunctionContaining(reference.getFromAddress());
     functions.put(caller.getEntryPoint().getOffset(),caller);
    }
    continue;
   }
   long va=Long.parseLong(target,16);Function f=getFunctionContaining(toAddr(va));
   functions.put(f.getEntryPoint().getOffset(),f);
  }
  DecompInterface dc=new DecompInterface();dc.toggleCCode(true);dc.openProgram(currentProgram);
  try(PrintWriter calls=new PrintWriter(Files.newBufferedWriter(directory.resolve("operand-calls.tsv"),StandardCharsets.UTF_8))) {
   calls.println("caller_va\tsite_va\ttarget_va\tinputs");
   for(Function f:functions.values()) {
    var result=dc.decompileFunction(f,180,monitor);
    Files.writeString(directory.resolve(f.getEntryPoint()+".c"),result.getDecompiledFunction().getC(),StandardCharsets.UTF_8);
    Iterator<PcodeOpAST> ops=result.getHighFunction().getPcodeOps();
    while(ops.hasNext()) {
     PcodeOpAST op=ops.next();if(op.getOpcode()!=PcodeOp.CALL) continue;
     StringBuilder inputs=new StringBuilder();
     for(int i=1;i<op.getNumInputs();++i) inputs.append(i).append(':').append(expression(op.getInput(i),new HashSet<>(),0)).append(" | ");
     calls.println(f.getEntryPoint()+"\t"+op.getSeqnum().getTarget()+"\t"+String.format("%08x",op.getInput(0).getOffset())+"\t"+inputs);
    }
    calls.flush();println("Extracted operands "+f.getEntryPoint());
   }
  } finally {dc.dispose();}
 }
}
