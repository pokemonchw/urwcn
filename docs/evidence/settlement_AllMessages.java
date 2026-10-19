//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.data.*;
import ghidra.program.model.pcode.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.*;
public class settlement_AllMessages extends GhidraScript {
 String textAt(long value) throws Exception { if(value<0x58c000L||value>=0x5e2000L)return ""; ByteArrayOutputStream b=new ByteArrayOutputStream(); for(int i=0;i<4096;i++){byte v=getByte(toAddr(value+i));if(v==0)return b.toString("ISO-8859-1").replace("\r","\\r").replace("\n","\\n").replace("\t","\\t");b.write(v);}return "";}
 public void run() throws Exception {
  Function message=getFunctionAt(toAddr(0x4f6510));message.setCallingConvention("__fastcall");message.replaceParameters(Function.FunctionUpdateType.DYNAMIC_STORAGE_ALL_PARAMS,true,SourceType.USER_DEFINED,new ParameterImpl("message",new PointerDataType(CharDataType.dataType),currentProgram));message.setReturnType(VoidDataType.dataType,SourceType.USER_DEFINED);
  TreeMap<Long,Function> fs=new TreeMap<>();for(Reference r:getReferencesTo(message.getEntryPoint())){Function f=getFunctionContaining(r.getFromAddress());if(f!=null)fs.put(f.getEntryPoint().getOffset(),f);}
  for(long va:new long[]{0x562ac0,0x55fb00,0x4f6020,0x4f6280,0x4f5c50}){Function f=getFunctionAt(toAddr(va));fs.put(va,f);}
  DecompInterface dc=new DecompInterface();dc.toggleCCode(true);dc.openProgram(currentProgram);
  Path dest=Path.of(getScriptArgs()[0]);
  try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(dest.resolve("settlement-all-callers-ghidra.c"),StandardCharsets.UTF_8));PrintWriter calls=new PrintWriter(Files.newBufferedWriter(dest.resolve("settlement-message-calls.tsv"),StandardCharsets.UTF_8));PrintWriter literals=new PrintWriter(Files.newBufferedWriter(dest.resolve("settlement-message-literals.tsv"),StandardCharsets.UTF_8));PrintWriter refs=new PrintWriter(Files.newBufferedWriter(dest.resolve("settlement-caller-string-refs.tsv"),StandardCharsets.UTF_8))){
   calls.println("caller_va\tcallsite_va\tinput\tliteral_va\tliteral");literals.println("string_va\ttext");refs.println("caller_va\tref_va\tstring_va\ttext");TreeMap<Long,String> strs=new TreeMap<>(); int n=0;
   for(Function f:fs.values()){
    out.println("\n/* Caller VA 0x"+f.getEntryPoint()+" */");DecompileResults r=dc.decompileFunction(f,120,monitor);if(r.getDecompiledFunction()!=null)out.println(r.getDecompiledFunction().getC());else out.println("/* "+r.getErrorMessage()+" */");
    if(r.getHighFunction()!=null){Iterator<PcodeOpAST> ops=r.getHighFunction().getPcodeOps();while(ops.hasNext()){PcodeOpAST op=ops.next();if(op.getOpcode()!=PcodeOp.CALL||op.getInput(0).getOffset()!=0x4f6510L)continue;Varnode in=op.getNumInputs()>1?op.getInput(1):null;String value="";String va="";if(in!=null&&in.isConstant()){value=textAt(in.getOffset());if(!value.isEmpty()){va=String.format("%08x",in.getOffset());strs.put(in.getOffset(),value);}}calls.println(f.getEntryPoint()+"\t"+op.getSeqnum().getTarget()+"\t"+(in==null?"NONE":in.toString())+"\t"+va+"\t"+value);}}
    InstructionIterator ins=currentProgram.getListing().getInstructions(f.getBody(),true);while(ins.hasNext()){Instruction i=ins.next();for(Reference ref:i.getReferencesFrom()){String value=textAt(ref.getToAddress().getOffset());if(!value.isEmpty())refs.println(f.getEntryPoint()+"\t"+i.getAddress()+"\t"+ref.getToAddress()+"\t"+value);}}
    out.flush();calls.flush();refs.flush();println("Extracted "+(++n)+"/"+fs.size()+" "+f.getEntryPoint());
   }for(Map.Entry<Long,String> e:strs.entrySet())literals.println(String.format("%08x",e.getKey())+"\t"+e.getValue());
  }finally{dc.dispose();}
 }
}
