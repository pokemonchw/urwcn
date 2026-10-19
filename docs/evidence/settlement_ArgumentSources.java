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
public class settlement_ArgumentSources extends GhidraScript {
 String textAt(long value) throws Exception { if(value<0x58c000L||value>=0x5e2000L)return ""; ByteArrayOutputStream b=new ByteArrayOutputStream(); for(int i=0;i<4096;i++){int v=getByte(toAddr(value+i))&255;if(v==0){String s=b.toString("ISO-8859-1");if(s.isEmpty()||!s.matches("[\\x20-\\x7e\\r\\n\\t]*")||!s.matches("(?s).*[A-Za-z].*"))return "";return s.replace("\r","\\r").replace("\n","\\n").replace("\t","\\t");}b.write(v);}return "";}
 Set<Long> constants(Varnode v,int depth,Set<Varnode> seen){Set<Long> values=new TreeSet<>();if(v==null||depth>16||!seen.add(v))return values;if(v.isConstant()||v.isAddress()){values.add(v.getOffset());return values;}PcodeOp def=v.getDef();if(def==null)return values;int op=def.getOpcode();if(op==PcodeOp.COPY||op==PcodeOp.CAST||op==PcodeOp.INT_ZEXT||op==PcodeOp.INT_SEXT){values.addAll(constants(def.getInput(0),depth+1,seen));}else if(op==PcodeOp.MULTIEQUAL){for(int n=0;n<def.getNumInputs();n++)values.addAll(constants(def.getInput(n),depth+1,new HashSet<>(seen)));}else if(op==PcodeOp.INT_ADD||op==PcodeOp.PTRSUB||op==PcodeOp.PTRADD){Set<Long>a=constants(def.getInput(0),depth+1,new HashSet<>(seen)),b=constants(def.getInput(1),depth+1,new HashSet<>(seen));long scale=op==PcodeOp.PTRADD&&def.getInput(2).isConstant()?def.getInput(2).getOffset():1;for(long x:a)for(long y:b)values.add(x+y*scale);}return values;}
 String trace(Varnode v,int depth,Set<Varnode> seen){if(v==null)return "NONE";if(v.isConstant()||v.isAddress())return String.format("0x%x",v.getOffset());if(depth>8||!seen.add(v))return v.toString();PcodeOp d=v.getDef();if(d==null)return v.toString();StringBuilder b=new StringBuilder(d.getMnemonic()).append('@').append(d.getSeqnum().getTarget()).append('(');for(int i=0;i<d.getNumInputs();i++){if(i>0)b.append(',');b.append(trace(d.getInput(i),depth+1,new HashSet<>(seen)));}return b.append(')').toString();}
 public void run() throws Exception {
  Function message=getFunctionAt(toAddr(0x4f6510));message.setCallingConvention("__fastcall");message.replaceParameters(Function.FunctionUpdateType.DYNAMIC_STORAGE_ALL_PARAMS,true,SourceType.USER_DEFINED,new ParameterImpl("message",new PointerDataType(CharDataType.dataType),currentProgram));message.setReturnType(VoidDataType.dataType,SourceType.USER_DEFINED);
  TreeMap<Long,Function> fs=new TreeMap<>();for(Reference r:getReferencesTo(message.getEntryPoint())){Function f=getFunctionContaining(r.getFromAddress());if(f!=null)fs.put(f.getEntryPoint().getOffset(),f);}
  DecompInterface dc=new DecompInterface();dc.toggleCCode(true);dc.openProgram(currentProgram);Path dest=Path.of(getScriptArgs()[0]);
  try(PrintWriter calls=new PrintWriter(Files.newBufferedWriter(dest.resolve("settlement-message-argument-sources.tsv"),StandardCharsets.UTF_8));PrintWriter literals=new PrintWriter(Files.newBufferedWriter(dest.resolve("settlement-message-literals-complete.tsv"),StandardCharsets.UTF_8))){
   calls.println("caller_va\tcallsite_va\tliteral_va\tliteral\tprovenance");literals.println("string_va\ttext");TreeMap<Long,String> strs=new TreeMap<>();int n=0;
   for(Function f:fs.values()){
    DecompileResults r=dc.decompileFunction(f,120,monitor);if(r.getHighFunction()!=null){Iterator<PcodeOpAST> ops=r.getHighFunction().getPcodeOps();while(ops.hasNext()){PcodeOpAST op=ops.next();if(op.getOpcode()!=PcodeOp.CALL||op.getInput(0).getOffset()!=0x4f6510L)continue;Varnode in=op.getNumInputs()>1?op.getInput(1):null;boolean any=false;for(long c:constants(in,0,new HashSet<>())){String value=textAt(c);if(!value.isEmpty()){strs.put(c,value);calls.println(f.getEntryPoint()+"\t"+op.getSeqnum().getTarget()+"\t"+String.format("%08x",c)+"\t"+value+"\t"+trace(in,0,new HashSet<>()));any=true;}}if(!any)calls.println(f.getEntryPoint()+"\t"+op.getSeqnum().getTarget()+"\t\t\t"+trace(in,0,new HashSet<>()));}}else calls.println(f.getEntryPoint()+"\tDECOMPILE_FAILED\t\t\t"+r.getErrorMessage().replace('\n',' '));calls.flush();println("Arguments "+(++n)+"/"+fs.size()+" "+f.getEntryPoint());
   }for(Map.Entry<Long,String>e:strs.entrySet())literals.println(String.format("%08x",e.getKey())+"\t"+e.getValue());
  }finally{dc.dispose();}
 }
}
