import json
with open('./table.txt', 'r', encoding='utf-8') as f:
    data = f.read()
table = json.loads(data)

import sys
input = []
with open(sys.argv[1], 'r', encoding='utf-8') as f:
    for line in f.readlines():
        token = line.replace('\n', '').split('\t')
        if token[1] == '<IDN>':
            input.append('IDN')
        elif token[1] == '<INT>':
            input.append('INT')
        else:
            input.append(token[0])
    input.append('#')


step, psym, pinput, sym = 1, 1, 0, ['#']
sym.append([i for i in table][0])
log = ''

def eof(token):
    if token == '#':
        return 'EOF'
    return token
# 推导的三个判断
while True:
    if sym[psym] == input[pinput] and sym[psym] == '#':
        log += f'{eof(sym[psym])}#{eof(input[pinput])}\taccept'
        break
    if sym[psym] == input[pinput]:
        log += f'{eof(sym[psym])}#{eof(input[pinput])}\tmove\n'
        pinput += 1
        psym -= 1
        sym.pop()
    elif sym[psym] in table:
        reduction = table[sym[psym]][input[pinput]].copy()
        reduction.reverse() # 翻转
        if len(reduction) == 0:
            log += f'{eof(sym[psym])}#{eof(input[pinput])}\terror'
            break
        log += f'{eof(sym[psym])}#{eof(input[pinput])}\treduction\n'
        sym.pop()
        sym += reduction
        psym += len(reduction) - 1
        if reduction == ['$']:
            sym.pop()
            psym -= 1
    step += 1

with open('./log.txt', 'w', encoding='utf-8') as f:
    f.write(log)
    f.write('\n')