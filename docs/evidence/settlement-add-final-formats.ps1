# Static source catalog update. No game or compiled artifact is executed.
$all=@(Import-Csv "$PSScriptRoot/settlement-all-format-sites.tsv" -Delimiter "`t")+
    @(Import-Csv "$PSScriptRoot/settlement-dispatch-all-format-sites.tsv" -Delimiter "`t")
$rows=@(Import-Csv "$PSScriptRoot/settlement-formats-implemented-sites.tsv" -Delimiter "`t")
$specs=@'
0040b857|control|00612200 indexed sound-event key table, consumed by40B8D0 audio lookup; preserve business identifier
00410106|control|40FC30 unresolved skill-code diagnostic displays its actual unrecognized input identifier
0042243c|npc|42241E NPC record+8 class name; coordinates then same buffer to5010C0
004311a7|bound|Three native branches;5627A0 fish-list result; alternative43115F copy
004490c4|bound|448D50 actual bow-property message producer
0048a01d|bound|4AAF20 writes NPC helper list ESP+2D78 at489F9A; three number branches
004a09a8|npc|4A0920 loop copies NPC record+8, or actual creature literal;4D4020 normalizes
004d535c|fatigue-prefix;fatigue|58E938..58E96C seven fatigue words/five phrase prefixes;4D5348 normalization
0051b91f|none|Native literal sprintf branch to shared F6510 buffer
0051b948|none|Native literal sprintf branch to shared F6510 buffer
0051b971|none|Native literal sprintf branch to shared F6510 buffer
0051b99a|none|Native literal sprintf branch to shared F6510 buffer
0051b9c3|none|Native literal sprintf branch to shared F6510 buffer
0051b9e8|none|Native literal sprintf branch to shared F6510 buffer
0051c04e|bound|51C036 constructs at %d meters in EBP-70 before message
0051c91a|npc|Corpse NPC record copied to local descriptor; argument is its+8 class/species
0051ccc7|bound|4AD4F0 name copied at51CAC0; typed integer count
0051cd7f|bound|Actual %s bones item-name fragment later read by51CE1A; native bytes unchanged
0051ce1a|bound|Name field ESP+689 from51CD7F (%s bones)
0051de3a|bound;bound|563190 actions43/37 through4D4020 and two recovered copy sites
0051ee5a|bound;bound|563190 actions43/38 through4D4020 and two recovered copy sites
0052f257|control|EBP-10 native key roster from ASCII D/B/1/2/I option codes,consumed bystrchr
00565cce|bound|452640 name returned565B77,copy EBP-70 at565B7C
005663f5|none|Native literal sprintf branch to shared F6510 buffer
005664be|none|Native literal sprintf branch to shared F6510 buffer
005664db|none|Native literal sprintf branch to shared F6510 buffer
005714b6|numeric|5714C5 directly consumes this numeric sprintf result atF6510
00571501|numeric|571510 directly consumes this coordinate sprintf result atF6510
0057297b|bound|A621AC8 treasure title source;572991 consumes result atF6510
00572bdb|bound|A621AC8 treasure title source;572BF1 consumes result atF6510
00572ca8|numeric|572CB7 directly consumes coordinate output atF6510
00574021|numeric|57402C directF6510
00574076|numeric|574081 directF6510
005740d2|numeric|5740DD directF6510
00574127|numeric|574132 directF6510
0057417c|numeric|574187 directF6510
005741d4|numeric|5741DF directF6510
00574227|numeric|574232 directF6510
0057427a|numeric|574285 directF6510
00574d97|numeric|Nativework-time scalar fragment feeds574DCC
00574ee0|numeric|Nativework-time scalar fragment feeds574F15
00575060|numeric|Nativework-time scalar fragment feeds575095
00574dcc|bound|Actual574D97 TYOAIKA_mod fragment thenF6510
00574f15|bound|Actual574EE0 TYOAIKA_mod fragment thenF6510
00575095|bound|Actual575060 TYOAIKA_mod fragment thenF6510
00575421|control;identity;control|Northf dataset label,4C1BF0(CL F,EDX8) generated propername,empty suffix
00575461|control;identity;control|Westf dataset label,4C1BF0(CL F,EDX1) generated propername,empty suffix
0057a542|bound;bound|4846C0 actual native identity/classification results;57A575 wrapper displays
0057a662|numeric|57A671 directF6510
0057b382|numeric|57B391 directF6510
00432f06|herbal.effect|43B9D0 initializes22 herb effect names at67D5F9+index*CCB;432F14 directF6510
004d95ca|herbal.effect|Same finite herb effect record name;4D95FA debug wrapper thenF6510
004d984d|herbal.effect|Same finite herb effect record name;4D9885 debug wrapper thenF6510
0048b525|literal:0059d104;identity;control|50F5B0 actual entered search text EBP-70;literalprefix and empty suffix
0048b588|identity|40CE40 NPC record+30 proper name copied to EBP-9A8
005233a4|literal:005af088;skill;control|Actual configured skill name A72A708+index*C, TEXTILECRAFT branch and4F90D0 normalization;empty suffix
00465282|literal:0059a1d0;bound;literal:0059a1cc|4633B0 descriptor+64 explanation;copied at46439C;actual wrapper delimiters
00469182|literal:0059a1d0;bound;literal:0059a1cc|4633B0 descriptor+64 explanation;copied at46439C;actual wrapper delimiters
00469222|bound|4633B0 descriptor name from02130B28 row, including actual annotation branch
004d817e|literal:005a5570;bound;injury-change|4D4EF0 name copied4D7FE4;actual four finite healing suffixes
004d81f8|literal:005a5584;bound;literal:005a5578|Same actual4D4EF0 injury name;fixed recovery phrase
00558bc1|bound|55751E loadedQST record title+31 bindsA83C5AF;type35 source remains separately pending
00567a82|track-size|Actualsmall prefix005E9A34 before tracking noun append
00567aa2|track-size|Actualbig prefix005E9A84 before tracking noun append
00567b28|bound;bound;bound|567880 actualage;567B07 subjectandgaitsource binding
00567b4a|literal:005d9990|Actualmany-mixed trail suffix before567C09 append
00567b94|literal:005d99b4|Actualother-unclear trail suffix before567C09 append
00567bda|direction|Native0058E710 direction table before567C09 append
0043faca|literal:005964ac;menu.recipe;menu.recipe|43F7F0 actual requested recipe and matched file header normalized by4D3DB0;fixed debug prefix contains literal percent characters
'@ -split "`r?`n"
foreach($spec in $specs) {
    $site,$domains,$proof=$spec -split '\|',3
    foreach($record in $all | Where-Object format_callsite -eq $site) {
        $present=$rows | Where-Object { $_.callsite -eq $site -and $_.format_va -eq $record.format_va }
        if($present) {continue}
        $rows += [pscustomobject]@{callsite=$site;format_va=$record.format_va;format=$record.format;category='message';parameter_domains=$domains;evidence=$proof}
    }
}
$manual=@'
004225c2|005919f4|Metsästys kohti %d,%d (%s)|npc|4225C2 native NPC record+8 and coordinates to5010C0
004341af|0059365c|Yhteisravintoesinelisäys: %s ravintoesineWT: %.2f -> %.2f|item|4341AF item descriptor name + two native double values, actual nested debug message
004364a6|00593c64|Sailioi: säiliöidään esineeseen %s (ESINE:%u)|item|4364A6 native item name + unsigned item identifier, actual nested debug message
00567ccc|005d99fc|Ikä päivinä: %d|numeric|567CCC native integer days, later5010C0 wrapper
0057da23|005dbb74|Päiväys: %d.%d.   %d:%d|numeric|57DA23 native byte day/month/hour/minute toF6510
005838a1|005dcba4|Vaikuttava lämpötila: %.2f|numeric|5838A1 native computed double to5010C0
00583c71|005dcbec|Kylmäpoikkeutettu lämpötila: %d|numeric|583C71 actual cold branch format, integer todebug wrapper
00583c71|005dcc0c|Lämminpoikketettu lämpötila: %d|numeric|583C71 actual warm branch format, integer todebug wrapper
0057ad14|005dba78|Huonelämpö: %d|numeric|57AD23 directF6510
0044908b|005903bc|%d|numeric|Actual var tag writer005E98D0;449098 resource -> shared message
00530a8c|005903bc|%d|numeric|Actual var tag writer005E98D0;530AA0 resource -> shared message
00532289|005903bc|%d|numeric|Actual var tag writer005E98D0;532296 resource -> shared message
004692d3|00000000|%s|bound|RAWMAT_INVALID actual 561B00 format;4633B0 descriptor row name ->4D4020 at4692BA
0052899e|005b05fc|Haavatulos: %s|control|A612808 wound code copied528980 and consumedstrchrF/S/E5289EC onward
005289ce|005aad8c|? %s|bound|52899E resultEBP-470 passedtodirect5289DB F6510
0044152d|00000000|%s|optional_bound|Actualrecord+184: resourcecopy51E0A0/51E981 or previouslyexpanded520DAD/521C9B;extra440B20operandignoredwhenformatcontainsno%s
00441624|00000000|%s|bound|Actualrecord+584 fixedtemplate5AE188copied51F826;actual4199B0timeoperand
00520dad|00000000|%s|bound|RETTING_SET resource561B00;452640actualitemname;outputrecord+184later44152D
00521c9b|00000000|%s|bound|DRYING_SET/TENDON_DRYING_SET resource561B00;452640actualitemname;outputrecord+184later44152D
00437140|00000000|%s|bound|Actual467A30selectedmaterialorMixed;nativeformat='%s '+recipeheaderorbeverage;suffixcopybound436A68/437059
0046d63b|00000000|%s|bound|Actual467A30selectedmaterialorMixed;nativeformat='%s '+recipeheader;suffixcopybound46D5E8
'@ -split "`r?`n"
foreach($record in $manual) {
    $site,$va,$pattern,$domains,$proof=$record -split '\|',5
    if($rows|Where-Object{$_.callsite -eq $site -and $_.format_va -eq $va}) {continue}
    $rows += [pscustomobject]@{callsite=$site;format_va=$va;format=$pattern;category='message_debug';parameter_domains=$domains;evidence=$proof}
}
foreach($row in $rows | Where-Object callsite -eq '00441cd1') {
    $row.parameter_domains='bound;bound'
    $row.evidence='Actual440000recipeheader->441881copy->55EFF0->4D4020;4633B0scratchname->4D4020;two independentsourceoperands'
}
$rows | Sort-Object callsite,format_va | Export-Csv "$PSScriptRoot/settlement-formats-implemented-sites.tsv" -Delimiter "`t" -NoTypeInformation -Encoding utf8
& "$PSScriptRoot/generate-settlement-format-entries.ps1"
