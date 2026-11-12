//@category Static source extraction
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.util.cparser.C.CParserUtils;
import ghidra.program.model.symbol.SourceType;
import java.io.PrintWriter;

public class quantity_Decompile extends GhidraScript {
    public void run() throws Exception {
        String[][] signatures={
            {"004fbd80","int __fastcall Quantity(int maximum, char *titleFormat, int x, int y);"},
            {"004fc160","int __fastcall DefaultQuantity(int unused, int maximum);"},
            {"004fc1d0","int __fastcall BoundedQuantity(int minimum, int maximum);"},
            {"004010d0","int __cdecl NativeFormat(char *output, char *format, ...);"},
            {"0058a0ae","void __fastcall SecurityCookie(unsigned int cookie);"},
            {"004f6510","void __fastcall Message(char *text);"},
            {"004cf790","void __fastcall CreateMenu(unsigned int color, char *title, int x, int y, int width, int height, int kind);"},
            {"004cf990","void __fastcall AddMenuRow(int action, char *label);"},
            {"004cfaf0","void __fastcall AddButton(int action, int x, int y, char *label);"},
            {"004cffb0","void DrawMenu(void);"},
            {"004d1120","int WaitMenu(void);"},
            {"00514680","void __fastcall DrawButton(int x, int y, char *label);"},
            {"00515e70","void __fastcall OutlinePanel(int x, int y, int width, int height, char *title, unsigned int flags);"},
            {"00516270","void __fastcall Panel(int x, int y, int width, int height, char *title, unsigned int style, unsigned int flags);"},
            {"0050e5a0","void __fastcall ShowText(int x, int y, char *text, unsigned int color, unsigned int outline);"}
        };
        for(String[] signature:signatures)
            new ApplyFunctionSignatureCmd(toAddr(signature[0]),
                CParserUtils.parseSignature(null,currentProgram,signature[1],false),
                SourceType.USER_DEFINED).applyTo(currentProgram);
        DecompInterface dc=new DecompInterface();dc.openProgram(currentProgram);
        String base=getScriptArgs()[0];
        try(PrintWriter out=new PrintWriter(base+".c","UTF-8");
            PrintWriter refs=new PrintWriter(base+"-refs.tsv","UTF-8");
            PrintWriter calls=new PrintWriter(base+"-incoming.tsv","UTF-8")) {
            refs.println("owner_va\tinstruction_va\treference_va\ttype\tdata");
            calls.println("target_va\tcaller_va\tsite_va\ttype");
            for(String target:new String[]{"004fbd80","004fc160","004fc1d0","00515e70","00516270","004cfaf0","004cf990","00514680","0050e5a0","0050f5b0","004d1120","00404030","00438240","004416a0","00447180","00455060","00468ac0","00520180"}) {
                var function=getFunctionAt(toAddr(target));
                out.println("\n/* "+function.getEntryPoint()+" .. "+function.getBody().getMaxAddress()+" */");
                out.println(dc.decompileFunction(function,180,monitor).getDecompiledFunction().getC());
                out.flush();println("Extracted "+function.getEntryPoint());
                if(target.equals("004fbd80") || target.equals("004fc160") || target.equals("004fc1d0"))
                    for(var reference:getReferencesTo(function.getEntryPoint())) {
                        var caller=getFunctionContaining(reference.getFromAddress());
                        calls.println(function.getEntryPoint()+"\t"+caller.getEntryPoint()+"\t"+reference.getFromAddress()+"\t"+reference.getReferenceType());
                    }
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
