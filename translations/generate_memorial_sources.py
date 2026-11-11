"""Generate the offline-extracted memorial source grammar and catalog values."""
from pathlib import Path
import json
import re

ROOT = Path(__file__).resolve().parent.parent


def main():
    manifest = json.loads((ROOT / 'translations/messages/memorial.zh-CN.json').read_text())
    forms = list(manifest['forms'])
    # 48A600's finite season spellings. 55E910's month table is populated
    # from urw_defs MONTH_NAME, not the old calendar.moon Gregorian inventory.
    for line in (ROOT / 'translations/messages_embedded/values.calendar.zh-CN.tsv').read_text().splitlines()[1:]:
        domain, source, target = line.split('\t')
        if domain == 'calendar.season' and source:
            forms.append(dict(source=source, target=target, slots='', kind='S'))
    world = dict(line.split('\t', 1) for line in
                 (ROOT / 'catalog/zh-CN/world_hud.tsv').read_text().splitlines()
                 if line and not line.startswith('#'))
    for key, target in world.items():
        if not key.startswith('world.month.'):
            continue
        month = key[len('world.month.'):]
        forms.append(dict(source=month, target=target, slots='', kind='M'))
        for prefix, phase in (('beginning of ', 'beginning'), ('early ', 'early'),
                              ('late ', 'late'), ('end of ', 'end')):
            forms.append(dict(source=prefix + month,
                              target=world['world.month_phase.' + phase].replace('{month}', target),
                              slots='', kind='M'))
    values = {}
    cpp = []
    for row in forms:
        domain = 'memorial.form.' + row['kind'] + ('.' + row['slots'] if row['slots'] else '')
        values[(domain, row['source'])] = row['target']
        order = ''.join(re.findall(r'\{(\d+)\}', row['target']))
        cpp.append('{' + ','.join((json.dumps(row['source'], ensure_ascii=False),
                   json.dumps(row['slots']), "'" + row['kind'] + "'", json.dumps(order),
                   json.dumps(domain))) + '},')
    (ROOT / 'modules/adapter/windows_memorial_forms.inc').write_text('\n'.join(cpp) + '\n')
    (ROOT / 'translations/messages_embedded/values.memorial.zh-CN.tsv').write_text(
        '# Memorial/death grammar; generated from memorial.zh-CN.json and native season/month values.\n' +
        ''.join(d + '\t' + s + '\t' + t + '\n' for (d, s), t in sorted(values.items())))
    catalog = ROOT / 'catalog/zh-CN/messages.tsv'
    lines = [line for line in catalog.read_text().splitlines()
             if not line.startswith('message.value.memorial.form.')]
    lines.extend('message.value.' + d + '.' + s.encode().hex() + '\t' + t
                 for (d, s), t in sorted(values.items()))
    catalog.write_text('\n'.join(lines) + '\n')
    print('Memorial forms:', len(forms), 'catalog values:', len(values))


if __name__ == '__main__':
    main()
