p = {}
with open('./grammar_alpha.txt', 'r', encoding='utf-8') as f:
    for line in f.readlines():
        tokens = line.replace('\n', '').split(' ')
        if tokens[0] not in p:
            p[tokens[0]] = []
        p[tokens[0]].append(tokens[2:len(tokens)])

# A -> B y | C y, 返回first(B)和first(C), 若有重叠, 展开B、C
first = {}
# 保证 first 是集合
def add_first(key, val):
    if key not in first:
        first[key] = []
    if val not in first[key]:
        first[key].append(val)  
def gen_first(idx):
    if idx in first:
        return
    # 删除多余 $
    for i in range(len(p[idx])):
        new = [j for j in p[idx][i][0:len(p[idx][i]) - 1] if j != '$']
        new.append(p[idx][i][len(p[idx][i]) - 1])
        p[idx][i] = new.copy()
        
    # 计算first(B)和first(C)
    # 1. 把 A -> D α | β, D -> $ | γ 改成 A -> α | D α | β
    # 这样改会使 A -> α 冗余
    # 2. 把 A -> D α | β, D -> $ 改成 A -> α | β
    # 如果 α == β 则把 A -> α 删掉
    # 做完这两步，只要不管 D -> $ 就不会有 A -> $ α 的情况出现
    i = 0
    while i < len(p[idx]):
        delete = 0
        if p[idx][i][0] in p:
            gen_first(p[idx][i][0])
            if '$' in first[p[idx][i][0]]:
                if len(first[p[idx][i][0]]) == 1:
                    new = [j for j in p[idx][0:i]]
                    tmp = []
                    if len(p[idx][i]) == 1:
                        tmp.append('$')
                    else:
                        tmp = p[idx][i][1:len(p[idx][i])]
                    if tmp in p[idx]:
                        delete = 1
                    else:
                        new.append(tmp)
                    if i + 1 < len(p[idx]):
                        new += [j for j in p[idx][i + 1:len(p[idx])]]
                    p[idx] = new.copy()
                else:
                    new = p[idx][i][1:len(p[idx][i])]
                    if new not in p[idx] and new != []:
                        p[idx].append(new.copy())
        i += 1 - delete
    
    # A -> α γ | B γ | C γ
    # 定义 head(A) 为所有 A 在左边的产生式的右边第一个符号
    # 即 head(A) = [α, B, C]
    # 如果 β∈first(B), β∈head(A), B -> D | E
    # 则 B γ 需要展开成 D γ | E γ (D、E 泛指 左边是 B 的产生式的右边)
    # 注: 忽略所有 $, 这是因为 head(A) 中所有非终结符的 $ 都是冗余的
    delta = [i[0] for i in p[idx]]
    delta_t = []
    idx_n = []
    for i in range(len(delta)):
        if delta[i] in first:
            delta_t.append(first[delta[i]])
            idx_n.append(i)
        else:
            delta_t.append(delta[i])
    wait = []
    for i in range(len(idx_n)):
        tmp = [j for j in delta_t[idx_n[i]] if j in delta_t and j != '$']
        if len(tmp):
            wait.append(idx_n[i])
        for j in range(i):
            tmp = [k for k in delta_t[idx_n[i]] if k in delta_t[idx_n[j]] and k != '$']
            if len(tmp):
                if idx_n[i] not in wait:
                    wait.append(idx_n[i])
                if idx_n[j] not in wait:
                    wait.append(idx_n[j])
    idx_n = [delta[i] for i in wait]
    # idx_n是需要展开的非终结符
    
    # 非终结符展开操作
    i = 0
    while i < len(p[idx]):
        tag = p[idx][i][0]
        if p[idx][i][0] not in idx_n:
            i += 1
            continue
        tmp = []
        if len(p[idx][i]) > 1:
            tmp = p[idx][i][1:len(p[idx][i])]
        head = p[p[idx][i][0]][0].copy()
        if head != ['$'] and tmp != []:
            new = head + tmp
        else:
            new = tmp
        p[idx][i] = new.copy()
        if len(p[tag]) > 1:
            for j in range(1, len(p[tag])):
                head = p[tag][j].copy()
                if head != ['$'] and tmp != []:
                    new = head + tmp
                else:
                    new = tmp
                p[idx].append(new.copy())
        i += 1

    # 生成 first
    first[idx] = []
    for i in range(len(p[idx])):
        end = 0
        if p[idx][i][0] not in p:
            add_first(idx, p[idx][i][0])
        if p[idx][i][0] in p:
            gen_first(p[idx][i][0])
            for j in first[p[idx][i][0]]:
                if j not in first[idx]:
                    if j == '$':
                        end = 1
                    else:
                        first[idx].append(j)
        if end:
            if len(p[idx][i]) == 1:
                add_first(idx, '$')
            elif len(p[idx][i]) > 1:
                ptr, new, ctn = 1, [], 1
                while p[idx][i][ptr] in p and ctn:
                    ctn = 0
                    gen_first(p[idx][i][ptr])
                    for j in first[p[idx][i][ptr]]:
                        if j not in first[idx]:
                            if j != '$':
                                first[idx].append(j)
                            else:
                                ctn = 1
                    ptr += 1
                    if ptr == len(p[idx][i]):
                        break
                if ptr == len(p[idx][i]):
                    add_first(idx, '$')
                elif p[idx][i][ptr] not in p:
                    add_first(idx, p[idx][i][ptr])

    # 合并多重分支
    head = {}
    for i in range(len(p[idx])):
        if p[idx][i][0] not in head:
            head[p[idx][i][0]] = []
        if len(p[idx][i]) > 1:
            head[p[idx][i][0]].append(p[idx][i][1:len(p[idx][i])])
        else:
            head[p[idx][i][0]].append(['$'])
            
    new = []
    a_ = idx + '_'
    for i in head:
        if len(head[i]) == 1:
            continue
        new.append([i, a_])
        p[a_] = head[i].copy()
        a_ += '_'
    for i in range(len(p[idx])):
        if len(head[p[idx][i][0]]) == 1:
            new.append(p[idx][i].copy())
    p[idx] = new.copy()

idx = [i for i in p]
i = 0
while i < len(idx):
    gen_first(idx[i])
    idx = [j for j in p]
    i += 1

# 生成follow三步
follow = {}
def gen_follow():
    for i in first:
        follow[i] = []
    follow[idx[0]].append('#')
    
    for i in p:
        for j in range(len(p[i])):
            for k in range(len(p[i][j]) - 1):
                if p[i][j][k] in p:
                    if p[i][j][k + 1] in p:
                        for item in first[p[i][j][k + 1]]:
                            if item not in follow[p[i][j][k]]:
                                follow[p[i][j][k]].append(item)
                        if '$' in follow[p[i][j][k]]:
                            follow[p[i][j][k]].remove('$')
                    elif p[i][j][k + 1] not in follow[p[i][j][k]]:
                        follow[p[i][j][k]].append(p[i][j][k + 1])
    
    while True:
        add = 0
        for i in p:
            for j in range(len(p[i])):
                rear = len(p[i][j]) - 1
                while rear >= 0 and p[i][j][rear] in p:
                    for item in follow[i]:
                        if item not in follow[p[i][j][rear]]:
                            follow[p[i][j][rear]].append(item)
                            add = 1
                    if '$' in first[p[i][j][rear]]:
                        rear -= 1
                    else:
                        break
        if add == 0:
            break
                    
gen_follow()

save = [i for i in p]
with open('./grammar_beta.txt', 'w', encoding='utf-8') as f:
    for i in save:
        for j in range(len(p[i])):
            f.write(f'{i} ->')
            for k in range(len(p[i][j])):
                f.write(f' {p[i][j][k]}')
            if j != len(p[i]) - 1 or i != save[len(save) - 1]:
                f.write(f'\n')

t = []
for i in p:
    for j in p[i]:
        for k in j:
            if k not in p and k not in t:
                t.append(k)
if '$' in t:
    t.remove('$')
t.append('#')
table = {}
for i in p:
    table[i] = {}
    for j in t:
        table[i][j] = []
for i in p:
    for j in p[i]:
        # 生成 table 的三个判断
        if j == ['$']:
            for k in follow[i]:
                table[i][k] = ['$']
        elif j[0] not in p:
            table[i][j[0]] = j.copy()
        else:
            for k in first[j[0]]:
                if k != '$':
                    table[i][k] = j.copy()

import json
with open('./table.txt', 'w', encoding='utf-8') as f:
    f.write(json.dumps(table))
