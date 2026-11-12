//@category Static source extraction
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.util.cparser.C.CParserUtils;
import ghidra.program.model.symbol.SourceType;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;
import ghidra.program.model.pcode.PcodeOp;
import ghidra.program.model.pcode.Varnode;

public class handcraft_Decompile extends GhidraScript {
    Set<Long> constants(Varnode value,Set<Varnode> seen) {
        Set<Long> result=new TreeSet<>();
        if(!seen.add(value)) return result;
        if(value.isConstant() || value.isAddress()) {result.add(value.getOffset());return result;}
        var def=value.getDef();
        if(def==null) return result;
        switch(def.getOpcode()) {
        case PcodeOp.COPY:case PcodeOp.CAST:case PcodeOp.INT_ZEXT:case PcodeOp.INT_SEXT:
            result.addAll(constants(def.getInput(0),seen));break;
        case PcodeOp.MULTIEQUAL:
            for(var input:def.getInputs()) result.addAll(constants(input,new HashSet<>(seen)));
            break;
        }
        return result;
    }
    public void run() throws Exception {
        String[][] signatures={
            {"004f6510","void __fastcall Message(char *text);"},
            {"00561b00","char * __fastcall ResourceMessage(char *key);"},
            {"004010d0","int __cdecl NativeFormat(char *output, char *format, ...);"},
            {"0046c8b0","char * __fastcall CraftMaterialName(int type);"},
            {"0046bbf0","void * __fastcall RequirementInfo(int type, char *name, void *output);"},
            {"004dc790","int __fastcall PhysicalRequirement(int actor, unsigned int flags, int third, char *action);"},
            {"005002b0","int __fastcall CommandMenu(char *title);"},
            {"00563190","char * __fastcall ActionDescription(int action);"},
            {"004ffcc0","void __fastcall UpperActionRow(int key, char *label, int action);"},
            {"00442ad0","void __fastcall RecipeRows(char *file, char *filter, char *submenu);"},
            {"0043ca90","void __fastcall TopicPreview(char *topic, char *summary);"},
            {"004d3db0","char * __fastcall Uppercase(char *text);"},
            {"004cf790","void __fastcall CreateMenu(unsigned int color, char *title, int x, int y, int width, int height, int kind);"},
            {"004cf990","void __fastcall AddMenuRow(int action, char *label);"},
            {"00562300","void __fastcall Words(int reset, char *text);"},
            {"0050e5a0","void __fastcall ShowText(int x, int y, char *text, unsigned int color, unsigned int outline);"},
            {"0050eb40","void __fastcall Paragraph(int x, int y, int width, int height, unsigned int color, unsigned int outline);"},
            {"00516270","void __fastcall Panel(int x, int y, int width, int height, char *title, unsigned int style, unsigned int flags);"}
        };
        for(String[] signature:signatures)
            new ApplyFunctionSignatureCmd(toAddr(signature[0]),
                CParserUtils.parseSignature(null,currentProgram,signature[1],false),
                SourceType.USER_DEFINED).applyTo(currentProgram);
        DecompInterface dc=new DecompInterface();dc.openProgram(currentProgram);
        String[] args=getScriptArgs();
        try(PrintWriter out=new PrintWriter(args[0]+".c","UTF-8");
            PrintWriter refs=new PrintWriter(args[0]+"-refs.tsv","UTF-8");
            PrintWriter operands=new PrintWriter(args[0]+"-operands.tsv","UTF-8")) {
            refs.println("owner_va\tinstruction_va\treference_va\ttype\tdata");
            operands.println("owner_va\tinstruction_va\tcallee_va\targument\tconstant_va");
            for(int i=1;i<args.length;i++) {
                var function=getFunctionContaining(toAddr(args[i]));
                out.println("\n/* "+function.getEntryPoint()+" .. "+function.getBody().getMaxAddress()+" */");
                var decompiled=dc.decompileFunction(function,180,monitor);
                out.println(decompiled.getDecompiledFunction().getC());
                var operations=decompiled.getHighFunction().getPcodeOps();
                while(operations.hasNext()) {
                    var op=operations.next();
                    if(op.getOpcode()!=PcodeOp.CALL) continue;
                    for(int parameter=1;parameter<op.getNumInputs();parameter++)
                        for(long constant:constants(op.getInput(parameter),new HashSet<>()))
                            operands.println(function.getEntryPoint()+"\t"+op.getSeqnum().getTarget()+"\t"+
                                op.getInput(0).getAddress()+"\t"+(parameter-1)+"\t"+String.format("%08x",constant));
                }
                out.flush();println("Extracted "+function.getEntryPoint());
                for(var reference:getReferencesTo(function.getEntryPoint()))
                    out.println("/* caller "+reference.getFromAddress()+" "+getFunctionContaining(reference.getFromAddress())+" */");
                var instructions=currentProgram.getListing().getInstructions(function.getBody(),true);
                while(instructions.hasNext()) {
                    var instruction=instructions.next();
                    for(var reference:instruction.getReferencesFrom()) {
                        var data=getDataAt(reference.getToAddress());
                        refs.println(function.getEntryPoint()+"\t"+instruction.getAddress()+"\t"+
                            reference.getToAddress()+"\t"+reference.getReferenceType()+"\t"+
                            (data==null ? "" : data.getDefaultValueRepresentation().replace("\t","\\t").replace("\n","\\n")));
                    }
                }
            }
        } finally {dc.dispose();}
    }
}
