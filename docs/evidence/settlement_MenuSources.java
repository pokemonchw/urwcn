//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.data.*;
import ghidra.program.model.pcode.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.*;
public class settlement_MenuSources extends settlement_ArgumentSources {
 void prototype(long va,int stackWords)throws Exception {
  Function f=getFunctionAt(toAddr(va));f.setCallingConvention("__fastcall");
  Parameter[] ps=new Parameter[2+stackWords];
  ps[0]=new ParameterImpl("key",IntegerDataType.dataType,currentProgram);
  ps[1]=new ParameterImpl("text",new PointerDataType(CharDataType.dataType),currentProgram);
  for(int i=2;i<ps.length;i++)ps[i]=new ParameterImpl("arg"+i,IntegerDataType.dataType,currentProgram);
  f.replaceParameters(Function.FunctionUpdateType.DYNAMIC_STORAGE_ALL_PARAMS,true,SourceType.USER_DEFINED,ps);
  f.setReturnType(VoidDataType.dataType,SourceType.USER_DEFINED);
 }
 public void run()throws Exception {
  long[] targets={0x4ffb30,0x4ffcc0,0x4ffd60,0x4fff30};
  prototype(targets[0],0);prototype(targets[1],1);prototype(targets[2],2);prototype(targets[3],2);
  TreeMap<Long,Function> functions=new TreeMap<>();
  for(long target:targets)for(Reference ref:getReferencesTo(toAddr(target))) {
   Function f=getFunctionContaining(ref.getFromAddress());if(f!=null)functions.put(f.getEntryPoint().getOffset(),f);
  }
  for(Reference ref:getReferencesTo(toAddr(0x5002b0))) {
   Function f=getFunctionContaining(ref.getFromAddress());if(f!=null)functions.put(f.getEntryPoint().getOffset(),f);
  }
  Function sprintf=getFunctionAt(toAddr(0x4010d0));sprintf.setCallingConvention("__cdecl");
  DataType str=new PointerDataType(CharDataType.dataType);
  sprintf.replaceParameters(Function.FunctionUpdateType.DYNAMIC_STORAGE_ALL_PARAMS,true,SourceType.USER_DEFINED,
   new ParameterImpl("output",str,currentProgram),new ParameterImpl("pattern",str,currentProgram),
   new ParameterImpl("key",IntegerDataType.dataType,currentProgram),new ParameterImpl("caption",str,currentProgram));
  sprintf.setVarArgs(false);sprintf.setReturnType(IntegerDataType.dataType,SourceType.USER_DEFINED);
  DecompInterface dc=new DecompInterface();dc.toggleCCode(true);dc.openProgram(currentProgram);
  Path dest=Path.of(getScriptArgs()[0]);
  try(PrintWriter calls=new PrintWriter(Files.newBufferedWriter(dest.resolve("settlement-menu-label-sources.tsv"),StandardCharsets.UTF_8));
      PrintWriter code=new PrintWriter(Files.newBufferedWriter(dest.resolve("settlement-menu-callers-ghidra.c"),StandardCharsets.UTF_8))) {
   calls.println("caller_va\tcallsite_va\tbuilder_va\tliteral_va\tliteral\tprovenance");int index=0;
   for(Function f:functions.values()) {
    DecompileResults result=dc.decompileFunction(f,600,monitor);
    code.println("\n/* Function "+f.getEntryPoint()+" */");
    if(result.getDecompiledFunction()!=null)code.println(result.getDecompiledFunction().getC());
    if(result.getHighFunction()!=null) {
     Iterator<PcodeOpAST> it=result.getHighFunction().getPcodeOps();
     while(it.hasNext()) {PcodeOpAST op=it.next();if(op.getOpcode()!=PcodeOp.CALL)continue;
      long target=op.getInput(0).getOffset();boolean wanted=false;for(long t:targets)if(t==target)wanted=true;
      int labelIndex=2;
      if(target==0x4010d0 && op.getNumInputs()>4) {
       for(long address:constants(op.getInput(2),0,new HashSet<>())) {
        String pattern=textAt(address);if(pattern.startsWith("%c.") && pattern.contains("%s"))wanted=true;
       }
       labelIndex=4;
      }
      if(!wanted)continue;Varnode input=op.getNumInputs()>labelIndex?op.getInput(labelIndex):null;
      String prefix=f.getEntryPoint()+"\t"+op.getSeqnum().getTarget()+"\t"+String.format("%08x",target)+"\t";
      boolean found=false;for(long value:constants(input,0,new HashSet<>())) {
       String text=textAt(value);if(text.isEmpty())continue;found=true;
       calls.println(prefix+String.format("%08x",value)+"\t"+text+"\t"+trace(input,0,new HashSet<>()));
      }
      if(!found)calls.println(prefix+"\t\t"+trace(input,0,new HashSet<>()));
     }
    }
    code.flush();calls.flush();println("Menu sources "+(++index)+"/"+functions.size()+" "+f.getEntryPoint());
   }
  }finally{dc.dispose();}
 }
}
