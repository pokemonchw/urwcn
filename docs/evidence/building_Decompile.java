//@category Static source extraction
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.util.cparser.C.CParserUtils;
import ghidra.program.model.symbol.SourceType;
import java.io.PrintWriter;

public class building_Decompile extends GhidraScript {
    public void run() throws Exception {
        String[][] signatures={
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
            PrintWriter refs=new PrintWriter(args[0]+"-refs.tsv","UTF-8")) {
            refs.println("owner_va\tinstruction_va\treference_va\ttype\tdata");
            for(int i=1;i<args.length;i++) {
                var function=getFunctionContaining(toAddr(args[i]));
                out.println("\n/* "+function.getEntryPoint()+" .. "+function.getBody().getMaxAddress()+" */");
                out.println(dc.decompileFunction(function,180,monitor).getDecompiledFunction().getC());
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
