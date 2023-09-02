#include <iostream>
#include <cstring>
#include <list>
#include <set>
#include <map>
#include <stack>
#include "Graph.hpp"

using namespace std;

Graph::Graph() {
    memset(head, -1, sizeof head);
    memset(wordType, -1, sizeof wordType);
    ecnt = 0;
    ncnt = 1;
}

void Graph::addEdge(int u, int v, int symbol) {
    e[ecnt].to = v;
    e[ecnt].symbol = symbol;
    e[ecnt].nxt = head[u];
    head[u] = ecnt++;
}

void Graph::makeNFA() {
    // INT
    addEdge(initialNode, INT_1, symbol_epsilon);
    addEdge(INT_1, INT_2, symbol_i);
    addEdge(INT_2, INT_3, symbol_n);
    addEdge(INT_3, INT_4, symbol_t);
    wordType[INT_4] = KW;

    // void
    addEdge(initialNode, VOID_1, symbol_epsilon);
    addEdge(VOID_1, VOID_2, symbol_v);
    addEdge(VOID_2, VOID_3, symbol_o);
    addEdge(VOID_3, VOID_4, symbol_i);
    addEdge(VOID_4, VOID_5, symbol_d);
    wordType[VOID_5] = KW;

    //return
    addEdge(initialNode, RETURN_1, symbol_epsilon);
    addEdge(RETURN_1, RETURN_2, symbol_r);
    addEdge(RETURN_2, RETURN_3, symbol_e);
    addEdge(RETURN_3, RETURN_4, symbol_t);
    addEdge(RETURN_4, RETURN_5, symbol_u);
    addEdge(RETURN_5, RETURN_6, symbol_r);
    addEdge(RETURN_6, RETURN_7, symbol_n);
    wordType[RETURN_7] = KW;

    // const
    addEdge(initialNode, CONST_1, symbol_epsilon);
    addEdge(CONST_1, CONST_2, symbol_c);
    addEdge(CONST_2, CONST_3, symbol_o);
    addEdge(CONST_3, CONST_4, symbol_n);
    addEdge(CONST_4, CONST_5, symbol_s);
    addEdge(CONST_5, CONST_6, symbol_t);
    wordType[CONST_6] = KW;

    // +
    addEdge(initialNode, PLUS_1, symbol_epsilon);
    addEdge(PLUS_1, PLUS_2, symbol_plus);
    wordType[PLUS_2] = OP;

    // -
    addEdge(initialNode, SUB_1, symbol_epsilon);
    addEdge(SUB_1, SUB_2, symbol_sub);
    wordType[SUB_2] = OP;

    // *
    addEdge(initialNode, MUL_1, symbol_epsilon);
    addEdge(MUL_1, MUL_2, symbol_mul);
    wordType[MUL_2] = OP;

    // /
    addEdge(initialNode, DIV_1, symbol_epsilon);
    addEdge(DIV_1, DIV_2, symbol_div);
    wordType[DIV_2] = OP;

    // %
    addEdge(initialNode, MOD_1, symbol_epsilon);
    addEdge(MOD_1, MOD_2, symbol_mod);
    wordType[MOD_2] = OP;

    // =
    addEdge(initialNode, ASSIGN_1, symbol_epsilon);
    addEdge(ASSIGN_1, ASSIGN_2, symbol_assign);
    wordType[ASSIGN_2] = OP;

    // >
    addEdge(initialNode, GREATER_1, symbol_epsilon);
    addEdge(GREATER_1, GREATER_2, symbol_greater);
    wordType[GREATER_2] = OP;

    // <
    addEdge(initialNode, LESS_1, symbol_epsilon);
    addEdge(LESS_1, LESS_2, symbol_less);
    wordType[LESS_2] = OP;

    // ==
    addEdge(initialNode, EQUAL_1, symbol_epsilon);
    addEdge(EQUAL_1, EQUAL_2, symbol_assign);
    addEdge(EQUAL_2, EQUAL_3, symbol_assign);
    wordType[EQUAL_3] = OP;

    // <=
    addEdge(initialNode, LE_1, symbol_epsilon);
    addEdge(LE_1, LE_2, symbol_less);
    addEdge(LE_2, LE_3, symbol_assign);
    wordType[LE_3] = OP;

    // >=
    addEdge(initialNode, GE_1, symbol_epsilon);
    addEdge(GE_1, GE_2, symbol_greater);
    addEdge(GE_2, GE_3, symbol_assign);
    wordType[GE_3] = OP;

    // !=
    addEdge(initialNode, NE_1, symbol_epsilon);
    addEdge(NE_1, NE_2, symbol_exclaim);
    addEdge(NE_2, NE_3, symbol_assign);
    wordType[NE_3] = OP;

    // &&
    addEdge(initialNode, AND_1, symbol_epsilon);
    addEdge(AND_1, AND_2, symbol_and);
    addEdge(AND_2, AND_3, symbol_and);
    wordType[AND_3] = OP;

    // ||
    addEdge(initialNode, OR_1, symbol_epsilon);
    addEdge(OR_1, OR_2, symbol_or);
    addEdge(OR_2, OR_3, symbol_or);
    wordType[OR_3] = OP;

    // (
    addEdge(initialNode, LLB_1, symbol_epsilon);
    addEdge(LLB_1, LLB_2, symbol_leftlittlebracket);
    wordType[LLB_2] = SE;

    // )
    addEdge(initialNode, RLB_1, symbol_epsilon);
    addEdge(RLB_1, RLB_2, symbol_rightlittlebracket);
    wordType[RLB_2] = SE;

    // {
    addEdge(initialNode, LBB_1, symbol_epsilon);
    addEdge(LBB_1, LBB_2, symbol_leftbigbracket);
    wordType[LBB_2] = SE;

    // }
    addEdge(initialNode, RBB_1, symbol_epsilon);
    addEdge(RBB_1, RBB_2, symbol_rightbigbracket);
    wordType[RBB_2] = SE;

    // ;
    addEdge(initialNode, SEMICOLON_1, symbol_epsilon);
    addEdge(SEMICOLON_1, SEMICOLON_2, symbol_semicolon);
    wordType[SEMICOLON_2] = SE;

    // ,
    addEdge(initialNode, COMMA_1, symbol_epsilon);
    addEdge(COMMA_1, COMMA_2, symbol_comma);
    wordType[COMMA_2] = SE;

    // IDN
    addEdge(initialNode, IDN_1, symbol_epsilon);
    for(int i = symbol_a;i <= symbol_z;i++) addEdge(IDN_1, IDN_2, i);
    addEdge(IDN_1, IDN_2, symbol_downline);
    addEdge(IDN_2, IDN_3, symbol_epsilon);
    for(int i = symbol_a;i <= symbol_z;i++) addEdge(IDN_3, IDN_3, i);
    for(int i = symbol_0;i <= symbol_9;i++) addEdge(IDN_3, IDN_3, i);
    addEdge(IDN_3, IDN_3, symbol_downline);
    addEdge(IDN_3, IDN_4, symbol_epsilon);
    wordType[IDN_4] = IDN;

    // INT
    addEdge(initialNode, INTNUM_1, symbol_epsilon);
    addEdge(INTNUM_1, INTNUM_2, symbol_sub);
    addEdge(INTNUM_1, INTNUM_2, symbol_epsilon);
    addEdge(INTNUM_2, INTNUM_5, symbol_0);
    for(int i = symbol_1;i <= symbol_9;i++) addEdge(INTNUM_2, INTNUM_3, i);
    addEdge(INTNUM_3, INTNUM_4, symbol_epsilon);
    for(int i = symbol_0;i <= symbol_9;i++) addEdge(INTNUM_4, INTNUM_4, i);
    addEdge(INTNUM_4, INTNUM_5, symbol_epsilon);
    wordType[INTNUM_5] = INT;
}

set<int> Graph::epsilonClosure(int start) {
    stack<int> st;
    set<int> ret;
    map<int, bool> vis;
    st.push(start);
    ret.insert(start);
    vis[start] = true;
    while(!st.empty()) {
        int now = st.top();
        st.pop();
        for(int i = head[now];~i;i = e[i].nxt) {
            if(e[i].symbol != symbol_epsilon || vis.count(e[i].to)) continue;
            st.push(e[i].to);
            vis[e[i].to] = true;
            ret.insert(e[i].to);
        }
    }
    return ret;
}

set<int> Graph::epsilonClosure(set<int> start) {
    set<int> ret = start;
    for(set<int>::iterator it = start.begin();it != start.end();it++) {
        set<int> tmp = epsilonClosure(*it);
        for(set<int>::iterator it2 = tmp.begin();it2 != tmp.end();it2++) {
            ret.insert(*it2);
        }
    }
    return ret;
}

set<int> Graph::oneSet(int start) {
    set<int> ret;
    ret.insert(start);
    return ret;
}

set<int> Graph::Ja(set<int> start, int a) {
    set<int> ret;
    for(set<int>::iterator it = start.begin();it != start.end();it++) {
        for(int i = head[*it];~i;i = e[i].nxt) {
            if(e[i].symbol == a) ret.insert(e[i].to);
        }
    }
    return ret;
}

int Graph::getWordType(set<int> now) {
    int ret = -1;
    for(set<int>::iterator it = now.begin();it != now.end();it++) {
        ret = max(ret, wordType[*it]);
    }
    return ret;
}

Graph Graph::makeDFA() {
    map<set<int>, int> mp;
    stack<set<int>> st;
    Graph DFA;
    // 初始状态S0的epsilon闭包作为DFA初态q0入栈
    st.push(epsilonClosure(initialNode));
    mp[st.top()] = initialNode;  // mp实现DFA各状态集合的节点号映射
    DFA.wordType[initialNode] = getWordType(st.top());
    while(!st.empty()) {  // 从q0出发直到不再有新状态入栈
        set<int> now = st.top();
        st.pop();
        for(int i = symbol_a;i <= symbol_comma;i++) {// 遍历所有可能的a弧
            set<int> Ia = epsilonClosure(Ja(now, i)); // now的a弧转换
            if(Ia.size() == 0) continue;
            if(!mp.count(Ia)) { //将新的状态集合入栈并更新mp和wordType
                DFA.wordType[DFA.ncnt] = getWordType(Ia);
                mp[Ia] = DFA.ncnt++;
                st.push(Ia);
            }
            DFA.addEdge(mp[now], mp[Ia], i); //添加当前状态和新状态的边
        }
    }
    return DFA;
}

int Graph::getNext(int now, int a) {
    for(int i = head[now];~i;i = e[i].nxt) {
        if(e[i].symbol == a) return e[i].to;
    }
    return -1;
}

bool Graph::setInSet(set<int> a, set<int> b) {
    for(set<int>::iterator it = a.begin();it != a.end();it++) {
        if(b.find(*it) == b.end()) return false;
    }
    return true;
}

pair<set<int>, bool> Graph::JaAndIfReachEmpty(set<int> start, int a) {
    set<int> ret;
    bool IfReachEmpty = false; //判断是否存在死结点
    for(set<int>::iterator it = start.begin();it != start.end();it++) {
        bool ReachEmpty = true;
        for(int i = head[*it];~i;i = e[i].nxt) {//遍历当前结点所连接的所有边
            if(e[i].symbol == a) {//检查是否存在a弧
                ret.insert(e[i].to); //将当前边的终点加入到ret中
                ReachEmpty = false;
            }
        }
        if(ReachEmpty) IfReachEmpty = true; //检测到死结点
    }
    return make_pair(ret, IfReachEmpty);
}

pair<set<int>, int> Graph::whoToDiv(list<set<int>> partition) {
    for(list<set<int>>::iterator it = partition.begin();it != partition.end();it++) {
        set<int> now = *it;
        for(int i = symbol_a;i <= symbol_comma;i++) { //遍历所有可能的a弧
            bool in = false;
            for(list<set<int>>::iterator it2 = partition.begin();it2 != partition.end();it2++) {
                pair<set<int>, bool> ja_empty = JaAndIfReachEmpty(*it, i);
                //如果Ia包含在现行Pi的状态集合*it2中则无需划分(若含有死结点并且集合非空仍然需要进行划分)
                if(!(ja_empty.first.size() != 0 && ja_empty.second) && setInSet(ja_empty.first, *it2)) {
                    in = true;
                    break;
                }
            }
            if(!in) return make_pair(*it, i);// 表示需要对当前集合*it进行划分
        }
    }
    return make_pair(*partition.begin(), -1);//表示当前不需要进一步划分
}

Graph Graph::minimizeDFA() {
    list<set<int>> partition;
    set<int> startSet, endSetKw, endSetOp, endSetInt, endSetIdn, endSetSe; 
    //根据各节点的wordType构造状态的初始划分
    for(int i = 0;i < ncnt;i++) {
        if(wordType[i] == -1) startSet.insert(i);
        else if(wordType[i] == IDN) endSetIdn.insert(i);
        else if(wordType[i] == KW) endSetKw.insert(i);
        else if(wordType[i] == INT) endSetInt.insert(i);
        else if(wordType[i] == SE) endSetSe.insert(i);
        else if(wordType[i] == OP) endSetOp.insert(i);
    }
    if(!startSet.empty()) partition.push_back(startSet);
    if(!endSetKw.empty()) partition.push_back(endSetKw);
    if(!endSetIdn.empty()) partition.push_back(endSetIdn);
    if(!endSetInt.empty()) partition.push_back(endSetInt);
    if(!endSetOp.empty()) partition.push_back(endSetOp);
    if(!endSetSe.empty()) partition.push_back(endSetSe);
    pair<set<int>, int> who;
    while((who = whoToDiv(partition)).second != -1) { // 不断对状态集合进行划分，直至无需划分
        set<int> reachEmpty;
        list<set<int>> toAddList;
        for(list<set<int>>::iterator it = partition.begin();it != partition.end();it++) {
            set<int> toAdd;   // 遍历需要划分的集合who.first中的每个节点
            for(set<int>::iterator it2 = who.first.begin();it2 != who.first.end();it2++) {
                set<int> ja = Ja(oneSet(*it2), who.second); // ja为当前节点经过who.second弧后的状态集合
                if(ja.empty())  // 若ja为空，则将其加入死结点集合reachEmpty
                    reachEmpty.insert(*it2);  
                else if(setInSet(ja, *it))  // 若ja非空且是当前集合*it的子集，则将加入新集合toAdd
                    toAdd.insert(*it2);
            }
            if(!toAdd.empty()) toAddList.push_back(toAdd); // toAddList存储各个划分出的新集合toAdd
        }
        if(!reachEmpty.empty()) partition.push_back(reachEmpty); //将死结点集合单独作为划分出的新集合
        for(list<set<int>>::iterator it = toAddList.begin();it != toAddList.end();it++) {
            partition.push_back(*it); // 将toAddList中的存储的各个新集合加入partition中
        }
        partition.remove(who.first); // 将划分前的旧集合删除
    }
    int fa[NUM_NODES], id = 1; //fa存储miniDFA中的各个结点和状态集合的对应编号
    Graph ret;
    // 为Pi-final中的每一组选一代表并重新编号和计算wordType
    for(list<set<int>>::iterator it = partition.begin();it != partition.end();it++) {
        bool isInitialNode = false;
        for(set<int>::iterator it2 = (*it).begin();it2 != (*it).end();it2++) {
            if((*it2) == 0) isInitialNode = true;
        }
        for(set<int>::iterator it2 = (*it).begin();it2 != (*it).end();it2++) {
            if(isInitialNode) fa[*it2] = 0;
            else fa[*it2] = id;
        }
        if(!isInitialNode) {
            ret.wordType[id] = getWordType(*it);
            id++;
        } else {
            ret.wordType[0] = getWordType(*it);
        }
    }
    //为各个新状态集合添加相应的连接边
    for(int u = 0;u < ncnt;u++) {
        for(int i = head[u];~i;i = e[i].nxt) {
            if(ret.getNext(fa[u], e[i].symbol) != fa[e[i].to]) {
                ret.addEdge(fa[u], fa[e[i].to], e[i].symbol);
            }
        }
    }
    return ret;
}