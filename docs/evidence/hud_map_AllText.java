//@category Static source extraction
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.symbol.Reference;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

// Offline PE decompilation and source references. No target code is executed.
public class hud_map_AllText extends GhidraScript {
    private String literal(Address address) throws Exception {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < 512; ++i) {
            int c = getByte(address.add(i)) & 255;
            if (c == 0) return result.toString();
            if (c < 32 && c != 9 && c != 10 && c != 13) return "";
            if (c == 9) result.append("\\t");
            else if (c == 10) result.append("\\n");
            else if (c == 13) result.append("\\r");
            else result.append((char)c);
        }
        return "";
    }
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String[][] targets = {
            {"004f8e20","hud_penalty_cell"},{"004f8f80","hud_heading"},
            {"004f9030","hud_identity"},{"004f90d0","hud_command"},
            {"004f9200","hud_wielded"},{"004f9600","hud_repeat"},
            {"004f9910","hud_conditions"},{"004fa2a0","hud_complete"},
            {"004fa860","hud_direction"},{"004faa30","hud_widget"},
            {"004ff040","hud_starvation"},{"00502d10","hud_penalties"},
            {"00503640","hud_calendar"},{"004fee50","hud_penalty_value"},
            {"0048ff70","hud_world_information"},{"0048fe90","hud_scale"},
            {"0048e3d0","place_part"},{"0048e420","place_combined"},
            {"0048e4f0","place_context"},{"0049b040","region_description"},
            {"0049ad00","culture_region"},{"004a8f50","place_generator"},
            {"004a3e70","place_lexicon"},{"0048a310","date_source"},
            {"0048a600","season_source"},{"0055e910","moon_source"},
            {"0055f8e0","time_source"},{"0055f450","warmth_source"},
            {"0055ff80","nutrition_source"},
            {"004e3020","map_marker_legend"},{"004e3a50","map_culture_legend"},
            {"004e3d90","map_background"},{"004e3ee0","map_legend_composition"},
            {"004e5990","known_areas_map"},{"00562530","screen_help_source"},
            {"004e4050","map_marker_edit"},{"004e4960","map_marker_selection"},
            {"004e4c70","map_location_info"},{"004e4c40","map_info_composition"},
            {"004e2850","map_quest_annotation_store"},{"004e2960","map_quest_annotation_build"},
            {"005574b0","quest_record_load"},
            {"00547780","quest_herbs_source"},{"0054dcd0","quest_adventurer_source"},
            {"005564bb","quest_punt_source"},{"0054f45c","quest_bird_source"},
            {"0054af15","quest_wolf_source"},{"0054bdb6","quest_robbers_source"},
            {"00555130","quest_forest_source"},{"0054d542","quest_culture_source"},
            {"0055086f","quest_disoriented_source"},{"0054a055","quest_need_source"},
            {"00553da1","quest_maids_source"},{"00552316","quest_water_source"},
            {"00552b2e","quest_spirit_source"},{"0055337b","quest_stones_branches_source"},
            {"00551595","quest_random_title_source"},
            {"00563190","action_description"},{"0046c8b0","craft_description"},
            {"004076c0","terrain_description"},{"005232d0","skill_command"},
            {"00564720","main_command_description"},
            {"0050e910","native_centered_text"},{"0050efd0","native_renderer_paragraph"},
            {"004cfd10","native_map_button"},{"00514d20","native_marked_text"}
        };
        DecompInterface dc = new DecompInterface();
        dc.toggleCCode(true);
        dc.openProgram(currentProgram);
        try (PrintWriter out = new PrintWriter(Files.newBufferedWriter(Path.of(args[0]), StandardCharsets.UTF_8));
             PrintWriter refs = new PrintWriter(Files.newBufferedWriter(Path.of(args[1]), StandardCharsets.UTF_8))) {
            out.println("/* Offline Windows 3.89.1 PE extraction; image base " + currentProgram.getImageBase() + ". */");
            refs.println("function_va\tname\tsite_va\treference_va\tkind\tcandidate_literal");
            for (String[] target : targets) {
                Function f = getFunctionContaining(toAddr(target[0]));
                DecompileResults result = dc.decompileFunction(f, 180, monitor);
                out.println("\n/* " + target[1] + "; VA " + f.getEntryPoint() + " */");
                out.println(result.getDecompiledFunction() == null ? "/* " + result.getErrorMessage() + " */" : result.getDecompiledFunction().getC());
                InstructionIterator instructions = currentProgram.getListing().getInstructions(f.getBody(), true);
                while (instructions.hasNext()) {
                    Instruction instruction = instructions.next();
                    for (Reference ref : instruction.getReferencesFrom()) {
                        if (ref.getReferenceType().isCall()) {
                            refs.println(f.getEntryPoint() + "\t" + target[1] + "\t" + instruction.getAddress() + "\t" + ref.getToAddress() + "\tcall\t");
                        } else if (ref.getToAddress().getOffset() >= 0x58c600 && ref.getToAddress().getOffset() < 0x5e2000) {
                            String text = literal(ref.getToAddress());
                            if (!text.isEmpty()) refs.println(f.getEntryPoint() + "\t" + target[1] + "\t" + instruction.getAddress() + "\t" + ref.getToAddress() + "\tdata_candidate\t" + text);
                        }
                    }
                }
                out.flush(); refs.flush();
                println("Extracted " + target[1] + " " + f.getEntryPoint());
            }
        } finally {
            dc.dispose();
        }
    }
}
