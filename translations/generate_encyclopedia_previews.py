"""Author missing native preview summaries from existing translated passages.

Usage: python3 translations/generate_encyclopedia_previews.py /path/to/GAME.NFO
Reads the pinned asset and translation sources; does not run game code.
"""
from pathlib import Path
import re
import sys

root = Path(__file__).resolve().parent.parent
source = Path(sys.argv[1]).read_bytes().decode('cp437').splitlines()
catalog = root / 'catalog/zh-CN/cultures.tsv'
entries = dict(line.split('\t', 1) for line in catalog.read_text().splitlines()
               if line and not line.startswith('#'))
titles = dict(line.split('\t', 1) for line in
              (root / 'translations/encyclopedia-titles.zh-CN.tsv').read_text().splitlines()
              if line and not line.startswith('#'))
labels = dict(line.split('\t', 1) for line in
              (root / 'translations/encyclopedia-aliases.zh-CN.tsv').read_text().splitlines()
              if line and not line.startswith('#'))
labels.update(dict(line.split('\t', 1) for line in
                   (root / 'translations/encyclopedia-preview-terms.zh-CN.tsv').read_text().splitlines()
                   if line and not line.startswith('#')))
passages = {}
for line in (root / 'translations/encyclopedia.zh-CN.tsv').read_text().splitlines():
    if line and not line.startswith('#'):
        interval, text = line.split('\t', 1)
        passages[int(interval.split('-')[0])] = text

# Same immutable topic aliases used by the ordinary encyclopedia generator.
for number, line in enumerate(source, 1):
    if line.startswith('.') and line.endswith('.'):
        for alias in line[1:-1].split('.'):
            if alias not in labels:
                labels[alias] = titles[str(number)]

old = {118:'cultures',285:'eastern_peoples',290:'western_peoples',297:'kaumo',
       318:'kiesse',336:'driik',355:'reemi',368:'sartola',386:'islanders',
       396:'koivula',410:'northern_peoples',427:'kuikka_tribe',435:'owl_tribe',
       445:'seal_tribe',456:'njerpez',467:'language',478:'language_inflexions'}
topic = None
pending = {}
for number, line in enumerate(source, 1):
    if line.startswith('.') and line.endswith('.'):
        topic = old[number] if number in old else f'encyclopedia_{number}'
    elif line.startswith('***'):
        topic = None
    elif topic is not None and number in passages:
        key = f'culture.topic.{topic}.summary'
        if key in entries or key in pending:
            continue
        text = re.sub(r'<[^>]+>', '', passages[number]).strip()
        text = re.sub(r'\{([^}]+)\}', lambda match: labels[match[1]], text)
        if text:
            sentence = re.search(r'^.*?[。！？]', text)
            pending[key] = sentence[0] if sentence else text

with catalog.open('a') as output:
    for key, text in pending.items():
        output.write(f'{key}\t{text}\n')
print(f'Authored {len(pending)} native preview summaries from existing Chinese passages.')
