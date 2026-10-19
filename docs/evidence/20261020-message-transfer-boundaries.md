# Actual native message-copy boundaries

Static PE 3.89 evidence from `build/windows-text-disassembly.txt` and
`settlement-all-callers-ghidra.c`. Implementation:
`modules/adapter/windows_message_transfers.inc`, IDs EC00–EC3A.
No tests, assertions, game execution, injection or compilation were performed.

## Selected-item explanation, 455060 → 6F2C30 → 458D57

The complete-copy entries are 456881 (595D34 literal),
456C30/456D20/456E10/456F20 (ESP+798), and
456CB0/456DA0/456EB1 (ESI, actual selected 561B00 result).
The corresponding native `strchr("!:?+=>", first_byte)` success branches copy
from source+1 at 4568B0, 456C70/456D60/456E50/456F60, and
456CEA/456DDA/456EEA. Only those executed +1 branches construct the new
`without_initial_marker` source node. Its child keeps its complete English
lookup identity, while its parent models removal of the original marker.

Loop-head hooks cover a complete MOV, including the original backedge target;
ECX==0 selects the first actual iteration. The ESI copies hook the complete
MOV EDX,destination immediately preceding the loop. None of the overwritten
instructions adjusts ESP or crosses an internal branch destination.

## Resource selections and composition

| Native boundary | Exact operation |
| --- | --- |
| 41BF14 | EAX selected resource → EBP-40C, consumed at 41BF33 |
| 4D9EF0, 4DA07D, 4DA0A7, 4DA116 | Four actual bedding-resource selections → EBP-40C, consumed at 4DA165 |
| 403249, 403298, 403318 | ESI selected resource appended to EBP-408; 4032BA appends the native single space; consumed at 40332C |
| 52B727, 52B78B, 52B847, 52B91B | Four actual projectile-result selections → EBP-4DC |
| 52B940 | EBP-4DC → A611B78; the complete MOV loop head is captured only for EDX==0 |
| 44E74B, 5300A1, 53031A | Actual native period append to A611B78, before direct F6510 or visibility wrapper |
| 4D7D28 | Native fixed `:@` prefix plus actual 4D4EF0 injury-name return → EBP-70 |
| 4D7D93, 4D7DAA | Actual selected ` seems to ease and go away!` / ` has fully healed!` append, consumed at 4D7E1E |

All entries are stateless. Each expression is attached to the actual destination
owner with the exact anticipated bytes of the uninterrupted native copy or
append. The original instructions still write English. No translated snapshot,
global string search, branch recalculation or UI position is stored. The new
source Kind is appended after existing enum values and uses the existing Text
serialization fields.

5008F0 also writes 6F2C30 through its own menu-selected row and `|` truncation
path. Its source selection is owned by the separately reviewed menu-return
module, not inferred from the 455060 paths above.
