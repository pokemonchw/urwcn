"""Materialize the statically extracted native conversation source grammar.

This authors source metadata and catalog values only. It never runs the game or
lays out text. The source manifest records the native literal/helper provenance.
"""
from pathlib import Path
import json
import re

ROOT = Path(__file__).resolve().parent.parent
CONVERSIONS = re.compile(r'%(?:[-+ #0]*\d*(?:\.\d+)?[hlL]?[sdiucfg])')
MARKERS = re.compile(r'\{(\d+)\}')
DOMAINS = {
    'activity', 'article', 'corpse', 'count', 'craft', 'crafted-animal-format',
    'crafted-material', 'crafted-name-format', 'crafted-name', 'crafted-wood-format',
    'culture', 'culture.native', 'direction', 'flora', 'geography.crust',
    'geography.direction', 'geography.distance', 'geography.format', 'geography.prefix',
    'geography.region', 'geography.separator', 'geography.size', 'geography.snow',
    'geography.suffix', 'geography.terrain-part', 'geography.terrain-prefix',
    'geography.tree-condition', 'grammar', 'identity', 'item', 'item.alternate',
    'item.portion', 'item.quality', 'item.wood', 'list', 'location-relative',
    'material', 'material.animal', 'material.cut-native', 'material.cut',
    'material.field', 'material.word', 'nameatom', 'nearby-object', 'npc',
    'object-description', 'posture', 'quest.culture', 'quest.need', 'quest.title',
    'reputation', 'skill', 'sound', 'spell', 'status', 'terrain', 'time',
    'track-age', 'track-kind', 'track-size', 'track-subject', 'treatment', 'tree',
    'unit', 'work',
}

def lexical_kind(domain):
    if domain == 'identity': return 'p'
    if domain == 'npc': return 'c'
    if domain.startswith(('item', 'material', 'crafted')) or domain in ('grammar', 'nameatom', 'flora', 'tree', 'corpse', 'craft'): return 'i'
    if domain.startswith('geography') or domain == 'terrain': return 'g'
    if domain == 'direction': return 'd'
    if domain in ('culture', 'culture.native', 'quest.culture'): return 'k'
    if domain == 'unit': return 'u'
    if domain == 'time': return 'h'
    if domain == 'list': return 'l'
    return 't'


def native_plural(text):
    """Exact finite source spellings selected by native 55EFF0, RVA 15EFF0."""
    text = text.lower()
    if '/' in text:
        return text.split('/', 1)[1]
    if text.endswith('fe'):
        return text[:-2] + 'ves'
    if text.endswith('f') and (text[-2:-1] in 'lraeiou' or text.endswith('staff')):
        return text[:-2 if text.endswith('staff') else -1] + 'ves'
    if text.endswith('tooth'):
        return text[:-4] + 'eeth'
    if 'lock of ' in text:
        return text.replace('lock of ', 'locks of ', 1)
    if text.endswith('x'):
        return text[:-1] + 'xes'
    if len(text) > 2 and text.endswith('ch'):
        return text[:-2] + 'ches'
    if len(text) > 2 and text.endswith('ry'):
        return text[:-2] + 'ries'
    return text if text.endswith('s') else text + 's'


def normalized(source, target):
    conversions = CONVERSIONS.findall(source)
    index = iter(range(len(conversions)))
    source = CONVERSIONS.sub(lambda _: '{' + str(next(index)) + '}', source)
    remaining = list(enumerate(conversions))
    def replace(match):
        position = next(i for i, value in remaining if value == match[0])
        remaining.remove((position, match[0]))
        return '{' + str(position) + '}'
    target = CONVERSIONS.sub(replace, target)
    return source, target, ''.join('t' if c[-1] == 's' else 'v' for c in conversions)


def main():
    manifest = json.loads((ROOT / 'translations/messages/conversation.zh-CN.json').read_text())
    authored = manifest['forms']
    forms = []
    values = {}
    lexemes = {}
    for row in authored:
        # The same English surface form can have different operand semantics
        # and Chinese order: player name/culture, NPC/action, item/material,
        # and number/unit all use "{0} {1}" in the original constructors.
        domain = 'conversation.form'
        if row['slots']:
            domain += '.' + row['kind'] + '.' + row['slots']
        row = dict(row, domain=domain)
        forms.append(row)
        values[(row['domain'], row['source'])] = row['target']

    # Read the existing semantic catalog by exact domain. The menu.prefix
    # inventory is deliberately not a lexical source for conversation inputs.
    for line in (ROOT / 'catalog/zh-CN/messages.tsv').read_text().split('\n'):
        if not line.startswith('message.value.'):
            continue
        key, target = line.split('\t', 1)
        domain, _, spelling = key[len('message.value.'):].rpartition('.')
        if domain not in DOMAINS:
            continue
        original = bytes.fromhex(spelling).decode('utf-8')
        if not original:
            continue
        if CONVERSIONS.search(original):
            source, target, slots = normalized(original, target)
            if not MARKERS.sub('', source):
                continue  # Native pure copies do not introduce a grammar rule.
            kind = lexical_kind(domain)
            slots = slots.replace('t', kind)
            if domain == 'npc' and original == '%s the %s': slots = 'nc'
            if domain == 'npc' and original == '%s called %s': slots = 'cn'
            if domain == 'npc' and original == '%s %s': slots = 'cc'
            if domain == 'npc' and original in ('the %s', 'The %s'): slots = 'c'
            if domain == 'identity': slots = slots.replace('t', 'p')
            if domain == 'geography.format' and original == '%s "%s"': slots = 'tn'
            if domain == 'geography.format' and original == 'at the region called %s': slots = 'n'
            imported = 'conversation.lexical.' + domain
            forms.append(dict(source=source, target=target, slots=slots, kind=kind,
                              domain=imported, origins=['existing semantic source: ' + domain]))
            values[(imported, source)] = target
            if domain in ('crafted-name-format', 'crafted-wood-format'):
                plural_source = native_plural(source)
                forms.append(dict(source=plural_source, target=target, slots=slots, kind=kind,
                                  domain=imported, origins=['55EFF0 + ' + domain]))
                values[(imported, plural_source)] = target
            continue
        spellings = {original, original.lower(), original[:1].upper() + original[1:]}
        if domain in ('item', 'npc', 'grammar', 'nameatom', 'crafted-name'):
            spellings.add(native_plural(original))
            spellings.add(native_plural(original).capitalize())
        if domain == 'grammar' and '/' in original:
            spellings.update((original.split('/')[0], original.split('/')[1]))
        for source in spellings:
            lexemes[(source, domain)] = original

    # Prefixes/suffixes below are complete native authored append operands.
    appends = sorted({r['source'] for r in authored if not r['slots'] and
                      (r['source'].startswith(' ') or r['source'].endswith(' ')) and
                      r['source'].strip()}, key=lambda s: (-len(s), s))
    unique = {}
    for row in forms:
        key = (row['source'], row['slots'], row['kind'], row['domain'])
        if key not in unique:
            unique[key] = row
    forms = list(unique.values())
    cpp = []
    for row in forms:
        order = ''.join(MARKERS.findall(row['target']))
        cpp.append('{' + ','.join((json.dumps(row['source'], ensure_ascii=False),
                    json.dumps(row['slots']), "'" + row['kind'] + "'", json.dumps(order),
                    json.dumps(row['domain']))) + '},')
    adapter = ROOT / 'modules/adapter'
    (adapter / 'windows_conversation_forms.inc').write_text('\n'.join(cpp) + '\n')
    (adapter / 'windows_conversation_lexemes.inc').write_text(''.join(
        '{' + ','.join(json.dumps(s, ensure_ascii=False) for s in (source, domain, original)) + ", '" + lexical_kind(domain) + "'},\n"
        for (source, domain), original in sorted(lexemes.items())))
    (adapter / 'windows_conversation_appends.inc').write_text(''.join(
        json.dumps(s, ensure_ascii=False) + ',\n' for s in appends))
    source_file = ROOT / 'translations/messages_embedded/values.conversation.zh-CN.tsv'
    source_file.write_text('# Complete native conversation grammar; generated from conversation.zh-CN.json.\n' +
        ''.join(d + '\t' + s + '\t' + t + '\n' for (d, s), t in sorted(values.items())))
    catalog = ROOT / 'catalog/zh-CN/messages.tsv'
    existing = [line for line in catalog.read_text().split('\n') if line and
                not line.startswith('message.value.conversation.form.') and
                not line.startswith('message.value.conversation.lexical.')]
    existing.extend('message.value.' + d + '.' + s.encode().hex() + '\t' + t
                    for (d, s), t in sorted(values.items()))
    catalog.write_text('\n'.join(existing) + '\n')
    print('Conversation forms:', len(forms), 'lexical spellings:', len(lexemes),
          'native append pieces:', len(appends), 'catalog values:', len(values))


if __name__ == '__main__':
    main()
