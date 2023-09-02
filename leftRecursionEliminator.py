# 读文件
# {A:[[α], [β]]}表示A -> α | β
dist = {}
with open('./grammar.txt', 'r', encoding='utf-8') as f:
    for line in f.readlines():
        tokens = line.replace('\n', '').split(' ')
        if tokens[0] not in dist:
            dist[tokens[0]] = []
        dist[tokens[0]].append(tokens[2:len(tokens)])

# 删除 A -> A
for i in dist:
    for j in dist[i]:
        if j == [i]:
            dist[i].remove(j)

j, idx, item = [], [i for i in dist], 0

while item < len(idx):
    i = idx[item]
    # 把 dist[i] -> dist[j] γ 中的 dist[j] 展开
    for pj in j:
        for k in range(len(dist[i])):
            if dist[i][k][0] == pj:
                temp = dist[i][k].copy()
                dist[i][k] = dist[pj][0].copy()
                if len(temp) > 1:
                    for l in temp[1:len(temp)]:
                        dist[i][k].append(l)
                if len(dist[pj]) > 1:
                    for l in dist[pj][1:len(dist[pj])]:
                        dist[i].append(l.copy())
                        if len(temp) > 1:
                            for m in temp[1:len(temp)]:
                                dist[i][len(dist[i]) - 1].append(m)

    # 消除直接左递归
    # A -> A α | β
    # a = [α], b = [β]
    a, b = [], []
    for m in range(len(dist[i])):
        if dist[i][m][0] == i:
            a.append(dist[i][m][1:len(dist[i][m])])
        else:
            b.append(dist[i][m].copy())
    if a != []:
        dist[i] = b.copy()
        for m in range(len(dist[i])):
            dist[i][m].append('_' + i)
        dist['_' + i] = a.copy()
        for m in range(len(dist['_' + i])):
            dist['_' + i][m].append('_' + i)
        dist['_' + i].append('$')
        idx.append('_' + i)
    j.append(i)
    item += 1

# 保存开始符号可以推出的非终结符
save = [idx[0]]
head = 0
while len(save) - head:
    temp = len(save)
    for i in save[head:len(save)]:
        for j in dist[i]:
            for k in j:
                if k in dist and k not in save:
                    save.append(k)
    head = temp
        
with open('./grammar_alpha.txt', 'w', encoding='utf-8') as f:
    for i in save:
        for j in range(len(dist[i])):
            f.write(f'{i} ->')
            for k in range(len(dist[i][j])):
                f.write(f' {dist[i][j][k]}')
            if j != len(dist[i]) - 1 or i != save[len(save) - 1]:
                f.write(f'\n')