//@category Static source extraction
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;

// Offline PE decompilation only; never executes the game or delivery artifacts.
public class ancestors_Decompile extends GhidraScript {
 public void run() throws Exception {
  DecompInterface dc=new DecompInterface(); dc.toggleCCode(true); dc.openProgram(currentProgram);
  String[][] targets={
   {"004de990","ancestor_list_and_death_branch"},
   {"004dd400","ancestor_summary_and_memorial"},
   {"004dda70","load_ancestor_indexes"},
   {"004dd380","ancestor_footer_panel"},
   {"005157b0","ancestor_title_bar"},
   {"004cfaf0","native_key_control"},
   {"0050e720","native_key_markup_text"},
   {"0050e5a0","native_text"},
   {"0055dfc0","ancestor_name_pair"},
   {"004f5830","native_font_constant"},
   {"004d1120","native_menu_input"},
   {"00525a90","main_menu"}
  };
  try(PrintWriter out=new PrintWriter(Files.newBufferedWriter(Path.of(getScriptArgs()[0]), StandardCharsets.UTF_8))){
   out.println("/* Ghidra 12.1.4 PUBLIC static PE decompiler extraction. Image base 0x400000. */");
   for(String[] t:targets){
    Function f=getFunctionAt(toAddr(t[0]));
    if(f==null){disassemble(toAddr(t[0]));f=createFunction(toAddr(t[0]),t[1]);}
    DecompileResults result=dc.decompileFunction(f,120,monitor);
    out.println("\n/* "+t[1]+"; VA 0x"+t[0]+" */");
    if(result.getDecompiledFunction()==null) out.println("/* "+result.getErrorMessage()+" */");
    else out.println(result.getDecompiledFunction().getC());
    out.flush();println("Extracted "+t[1]+" at VA 0x"+t[0]);
   }
  }finally{dc.dispose();}
 }
}
