"""Offline PE/string census for the HUD and known-area map; executes no game code."""
import csv
import re
import struct
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
ANALYSIS = ROOT / 'build/analysis/hud-map-20261110'
PE = Path('/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe').read_bytes()
pe_header = struct.unpack_from('<I', PE, 60)[0]
section_count = struct.unpack_from('<H', PE, pe_header + 6)[0]
section_table = pe_header + 24 + struct.unpack_from('<H', PE, pe_header + 20)[0]
sections = [struct.unpack_from('<IIII', PE, section_table + 40 * i + 8) for i in range(section_count)]


def file_offset(va):
    rva = va - 0x400000
    for virtual_size, virtual_address, raw_size, raw_offset in sections:
        if virtual_address <= rva < virtual_address + raw_size:
            return raw_offset + rva - virtual_address


def literal(va):
    offset = file_offset(va)
    return PE[offset:PE.index(0, offset)].decode('latin1')


def canonical(va):
    offset = file_offset(va)
    start = PE.rfind(b'\0', max(0, offset - 512), offset) + 1
    raw = PE[start:PE.index(0, offset)]
    # References into memcpy operands include suffixes and address-table bytes.
    # The source inventory retains only complete Western-text byte runs. Raw
    # instruction references remain in the separate, explicitly candidate file.
    if len(raw) > 512 or any(c < 32 or (c > 126 and c not in (0xe4, 0xf6, 0xc4, 0xd6)) for c in raw):
        return None
    return va - offset + start, raw.decode('latin1')


refs = list(csv.DictReader((ANALYSIS / 'source-refs.tsv').open(), delimiter='\t'))
resources = defaultdict(lambda: {'sites': set(), 'functions': set()})
for ref in refs:
    if ref['kind'] != 'data_candidate':
        continue
    value = canonical(int(ref['reference_va'], 16))
    if value is None:
        continue
    address, source = value
    if address == 0x5dd9d0:  # Native Rect's x=100 bytes, not text.
        continue
    resources[(address, source)]['sites'].add(ref['site_va'])
    resources[(address, source)]['functions'].add(ref['name'])

# All 39 F90D0 callers are retained separately. These are their direct literal
# operands; the other sources are 163190, 164720, or native skill-table names.
direct_commands = [0x59ec54, 0x59ec60, 0x59ed30, 0x5b14d4, 0x5b14e0, 0x5b14f4,
                   0x5b1508, 0x5b1510, 0x5dc34c, 0x5ac71c, 0x5dc41c, 0x5d89e4,
                   0x5d89b4, 0x5dc458, 0x5dc460, 0x5dc474, 0x5dc484, 0x5dc4d0,
                   0x5dc4e0, 0x5dc500, 0x5dc4ec]
for address in direct_commands:
    resources[(address, literal(address))]['functions'].add('hud_command_direct_caller')
for source in ('Run', 'Wield'):
    resources[(0, source)]['functions'].add('hud_command_immediate')
    resources[(0, source)]['sites'].add('immediate ASCII copies; hud-command-callers.asm / main_command_description')

# The decompiler identifies these native pointer tables explicitly. Their
# pointed-to strings are sources; the pointer bytes themselves are not.
for table, count, function, site in [(0x58e938, 7, 'hud_conditions', '004fa27e'),
                                      (0x58ea40, 8, 'hud_widget', '004facf2')]:
    for index in range(count):
        address = struct.unpack_from('<I', PE, file_offset(table) + index * 4)[0]
        source = literal(address)
        resources[(address, source)]['functions'].add(function)
        resources[(address, source)]['sites'].add(site)

help_lines = (Path('/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld') /
              'gameinfo/urw_scrinfo.txt').read_text().splitlines()
start = help_lines.index('.KNOWN_AREAS_MAP.')
for index in range(start + 1, len(help_lines)):
    if help_lines[index] == '***':
        break
    # File identities use their true record numbers, not visual line slots.
    resources[(0, help_lines[index])]['functions'].add('known_map_help_file')
    resources[(0, help_lines[index])]['sites'].add(f'urw_scrinfo.txt:{index + 1}')

# Add the finite activity/skill branches to the dedicated command display
# domain. Reuse reviewed translations at extraction time, not a runtime search.
value_rows = {}
for path in sorted((ROOT / 'translations/messages_embedded').glob('values*.zh-CN.tsv')):
    for row in csv.reader(path.open(), delimiter='\t'):
        if len(row) == 3 and row[0] != 'domain' and not row[0].startswith('#'):
            value_rows[(row[0], row[1])] = row[2]
command_path = ROOT / 'translations/messages_embedded/values.hud-map.zh-CN.tsv'
command_rows = list(csv.reader(command_path.open(), delimiter='\t'))
authored = {row[1] for row in command_rows if len(row) == 3 and row[0] == 'hud.command'}
additions = []
for (domain, source), target in sorted(value_rows.items()):
    if domain == 'activity' or (domain == 'skill' and source.isupper()):
        if source not in authored:
            additions.append(['hud.command', source, target])
            authored.add(source)
with command_path.open('a') as output:
    for row in additions:
        output.write('\t'.join(row) + '\n')


def consumer(functions, source):
    if source in {'INIT', 'SHIELD', 'KNOWN_AREAS_MAP', 'NOTEXTSPOT'}:
        return '内部控制标识，保持原值'
    if any(s in source for s in ('.png', '.jpg', '.ogg', 'gameinfo/', 'regstat_terrain')) or source == 'rb':
        return '内部资源路径/文件模式，保持原值'
    if not re.search('[A-Za-z]', re.sub('<[^>]+>', '', source)):
        return '标点/格式语法/数值，原生保留；%s操作数按来源翻译'
    if source in {'R', 'G', 'B', 'Y', 'W'}:
        return '原生颜色快捷键，保持输入动作'
    if source in {'w', 'e', 'q'}:
        return '原生界面快捷键，保持输入动作'
    if any(name in functions for name in ('hud_command_direct_caller', 'hud_command_immediate', 'main_command_description')):
        return 'hud.command完整指令词库；F91E7中文字形截短'
    if 'action_description' in functions:
        return 'activity既有词库；hud.command；F98F1重复动作消费'
    if 'craft_description' in functions:
        return 'craft-requirement既有词库；F9869源捕获/F98F1消费'
    if 'place_lexicon' in functions:
        return '原生地名组合：芬兰语专名保持原值，英文释义进入world_place_lexemes既有词库'
    if any(name.startswith('map_quest_annotation') for name in functions):
        return 'hud.map任务句式+原生任务标题来源；E2850实际复制结果绑定'
    if any(name in functions for name in ('map_marker_edit', 'map_marker_selection', 'map_location_info')):
        return 'hud.map/culture.map标记控件；162300段落来源；姓名/玩家文字保留'
    if 'known_map_help_file' in functions:
        return 'urw_scrinfo.txt的KNOWN_AREAS_MAP段→culture.map.help实际记录词库'
    if any(name.startswith('map_') or name == 'known_areas_map' for name in functions):
        return 'culture.map/topic既有词库；原生地图构建/绘制边界'
    if 'screen_help_source' in functions:
        return 'urw_scrinfo.txt实际记录→culture.map.help；可选屏幕帮助路径保持原值'
    if any(name.startswith('native_') for name in functions):
        return '原生文本语法/格式标签；按字形度量及绘制扩展消费'
    if 'skill_command' in functions:
        return 'skill及hud.command；消息提示使用既有MessageFlow'
    return 'hud/world既有词库或MessageFlow消息来源；实际原生显示调用消费'


evidence = ROOT / 'docs/evidence'
inventory = evidence / '20261110-hud-map-text-resources.tsv'
with inventory.open('w') as output:
    writer = csv.writer(output, delimiter='\t', lineterminator='\n')
    writer.writerow(['literal_va', 'source', 'functions', 'reference_sites_va', 'consumer_or_policy'])
    for (address, source), origins in sorted(resources.items()):
        names = sorted(origins['functions'])
        writer.writerow([f'{address:08x}', source, ','.join(names), ','.join(sorted(origins['sites'])), consumer(names, source)])
(evidence / '20261110-hud-map-source-references.tsv').write_bytes((ANALYSIS / 'source-refs.tsv').read_bytes())
(evidence / '20261110-hud-map-decompiled.c').write_bytes((ANALYSIS / 'hud-map-ghidra.c').read_bytes())

assembly = (ROOT / 'build/analysis/windows-3891-native-full.asm').read_text().splitlines()
with (evidence / '20261110-hud-command-callers.asm').open('w') as output:
    for index, line in enumerate(assembly):
        if re.search(r'call\s+0x4f90d0\b', line):
            output.write('\n'.join(assembly[max(0, index - 14):index + 3]) + '\n\n')
print(f'Extracted {len(resources)} complete literal resources from 50 native functions; added {len(additions)} activity/skill command entries.')
