//@category Static source extraction
import ghidra.app.decompiler.*;import ghidra.program.model.listing.*;import ghidra.program.model.symbol.*;import ghidra.program.model.data.*;import ghidra.program.model.pcode.*;import java.io.*;import java.nio.charset.StandardCharsets;import java.nio.file.*;import java.util.*;
public class settlement_ValueInputs extends settlement_ArgumentSources {
 public void run()throws Exception {
  long[]targets={0x4d4020,0x55eff0,0x55f400,0x562bd0,0x562cf0};Set<Long>selected=new HashSet<>();TreeMap<Long,Function>callers=new TreeMap<>();
  DataType str=new PointerDataType(CharDataType.dataType);
  for(long va:targets){selected.add(va);Function f=getFunctionAt(toAddr(va));f.setCallingConvention("__fastcall");f.replaceParameters(Function.FunctionUpdateType.DYNAMIC_STORAGE_ALL_PARAMS,true,SourceType.USER_DEFINED,new ParameterImpl("text",str,currentProgram));f.setReturnType(str,SourceType.USER_DEFINED);for(Reference r:getReferencesTo(f.getEntryPoint())){Function c=getFunctionContaining(r.getFromAddress());if(c!=null)callers.put(c.getEntryPoint().getOffset(),c);}}
  getFunctionAt(toAddr(0x58a0ae)).setCallFixup("security_check_cookie");DecompInterface dc=new DecompInterface();dc.openProgram(currentProgram);
  try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(Path.of(getScriptArgs()[0]),StandardCharsets.UTF_8))){out.println("caller\tsite\ttarget\tliteral\tprovenance");for(Function f:callers.values()){DecompileResults r=dc.decompileFunction(f,120,monitor);if(r.getHighFunction()==null){out.println(f.getEntryPoint()+"\tFAILED\t\t\t"+r.getErrorMessage());out.flush();continue;}Iterator<PcodeOpAST>it=r.getHighFunction().getPcodeOps();while(it.hasNext()){PcodeOpAST op=it.next();if(op.getOpcode()!=PcodeOp.CALL||!selected.contains(op.getInput(0).getOffset()))continue;Varnode v=op.getNumInputs()>1?op.getInput(1):null;String literal="";for(long c:constants(v,0,new HashSet<>())){String s=textAt(c);if(!s.isEmpty())literal+=(literal.isEmpty()?"":" | ")+String.format("%08x=",c)+s;}out.println(f.getEntryPoint()+"\t"+op.getSeqnum().getTarget()+"\t"+op.getInput(0).getAddress()+"\t"+literal+"\t"+trace(v,0,new HashSet<>()));}out.flush();println("Value inputs "+f.getEntryPoint());}}
  finally{dc.dispose();}
 }
}
