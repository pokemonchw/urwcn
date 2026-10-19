# Shared-message copied literal review

Static review of the 3.89 PE, `settlement-message-call-ledger.tsv`,
`settlement-all-callers-ghidra.c`, and `build/windows-text-disassembly.txt`.
No game execution, injection, compilation, assertions or tests were used.

## 4E8730 → 4E8C0C

The native function clears two 1,024-byte stack buffers, copies complete fixed
messages into them along the selected forest/water-state branches, and passes
the selected buffer to 4F6510 at 4E8C0C. The SSA merge is between EBP-818 and
EBP-418. The native decisions and copies remain unchanged. These are complete
embedded literals, despite their display pointer being a stack-buffer address.

The complete distinct source inventory is:

| PE VA | Complete native source |
| --- | --- |
| 005A8784 | &You feel at ease. |
| 005A8798 | &You feel pleasant. |
| 005A87AC | &You feel comfortable. |
| 005A87C4 | &You feel comfortable and safe. |
| 005A87E4 | &You feel unity with the forest around. |
| 005A880C | &You feel a bit uneasy. |
| 005A8824 | &You feel scared. |
| 005A8838 | &You feel frightened. |
| 005A8850 | !The forest around looks frightening. |
| 005A8878 | !The forest around looks extremely hostile. |
| 005A88A4 | &You sense a soothing wind. |
| 005A88C0 | &You feel comfortable breeze on your face. |
| 005A88EC | &You feel unity with the waters around. |
| 005A8914 | &You feel an angry wind passing by. |
| 005A8938 | &You feel strangely frightened about the waters around. |
| 005A8970 | !The waters around feel extremely hostile to you. |

`translations/messages_embedded/direct_copied.zh-CN.tsv` supplies the address-
indexed translations. The shared-message source service already distinguishes
an exact live owner binding from an embedded-literal lookup; this call needs
the missing finite literal inventory, not a repeated native state decision.

## 48A310 call scope

The PE has nine direct CALLs to 48A310. Six calls at 57231C, 572340, 572364,
572388, 5723AC and 5723D0 return directly to the shared-message dispatcher.
49050A and 4906D7 feed right-HUD 50E910 rendering. 4DD88B feeds the ancestor/
death-history format `%s faced %s end %s.` and 50EB40. The latter three do not
provide a shared-message, resource-tag or quest-title source in the inspected
native call chains.

## Other complete-copy message branches

* 4A10A0 → 4A11D3: the selected native stealth branch copies one of four
  complete strings (59E6A0, 59E6B8, 59E6CC, 59E6E4) into EBP-74. The sound
  tags `{walk}` and `{crack}` and the `&` control marker remain native data.
* 44C9B0 → 44CBAA: the withered-plant branch copies 598608 into EBP-40C.
  Other branches use the existing native resource/format flow; this addition
  covers the previously unlisted complete fixed-string branch.
* 51EB90 → 51F551: the dry-skin soaking branch copies 5AE028 into EBP-4A8.
  5AE070 is copied into a different buffer, EBP-378, for subsequent action
  text. It is not assumed to be another argument of this F6510 call.

These six additional fixed strings are in `direct_copied.zh-CN.tsv`; no new
source decision or display hook is needed for their exact copied contents.
