#ifndef GRAPH_H
#define GRAPH_H

#include <set>
#include <list>
using namespace std;

#define NUM_NODES 10000
#define NUM_EDGES 10000

//type
#define IDN 0
#define OP 1
#define KW 2
#define INT 3
#define SE 4

//node
#define initialNode 0
#define INT_1 1
#define INT_2 2
#define INT_3 3
#define INT_4 4
#define VOID_1 5
#define VOID_2 6
#define VOID_3 7
#define VOID_4 8
#define VOID_5 9
#define RETURN_1 10
#define RETURN_2 11
#define RETURN_3 12
#define RETURN_4 13
#define RETURN_5 14
#define RETURN_6 15
#define RETURN_7 16
#define CONST_1 17
#define CONST_2 18
#define CONST_3 19
#define CONST_4 20
#define CONST_5 21
#define CONST_6 22
#define PLUS_1 23
#define PLUS_2 24
#define SUB_1 25
#define SUB_2 26
#define MUL_1 27
#define MUL_2 28
#define DIV_1 29
#define DIV_2 30
#define MOD_1 31
#define MOD_2 32
#define ASSIGN_1 33
#define ASSIGN_2 34
#define GREATER_1 35
#define GREATER_2 36
#define LESS_1 37
#define LESS_2 38
#define EQUAL_1 39
#define EQUAL_2 40
#define EQUAL_3 41
#define LE_1 42
#define LE_2 43
#define LE_3 44
#define GE_1 45
#define GE_2 46
#define GE_3 47
#define NE_1 48
#define NE_2 49
#define NE_3 50
#define AND_1 51
#define AND_2 52
#define AND_3 53
#define OR_1 54
#define OR_2 55
#define OR_3 56
#define LLB_1 57
#define LLB_2 58
#define LBB_1 59
#define LBB_2 60
#define RLB_1 61
#define RLB_2 62
#define RBB_1 63
#define RBB_2 64
#define SEMICOLON_1 65
#define SEMICOLON_2 66
#define COMMA_1 67
#define COMMA_2 68
#define IDN_1 69
#define IDN_2 70
#define IDN_3 71
#define IDN_4 72
#define INTNUM_1 73
#define INTNUM_2 74
#define INTNUM_3 75
#define INTNUM_4 76
#define INTNUM_5 77

//edge epsilon
#define symbol_epsilon 0

//edge a~z
#define symbol_a 1
#define symbol_b 2
#define symbol_c 3
#define symbol_d 4
#define symbol_e 5
#define symbol_f 6
#define symbol_g 7
#define symbol_h 8
#define symbol_i 9
#define symbol_j 10
#define symbol_k 11
#define symbol_l 12
#define symbol_m 13
#define symbol_n 14
#define symbol_o 15
#define symbol_p 16
#define symbol_q 17
#define symbol_r 18
#define symbol_s 19
#define symbol_t 20
#define symbol_u 21
#define symbol_v 22
#define symbol_w 23
#define symbol_x 24
#define symbol_y 25
#define symbol_z 26

//edge number
#define symbol_0 27
#define symbol_1 28
#define symbol_2 29
#define symbol_3 30
#define symbol_4 31
#define symbol_5 32
#define symbol_6 33
#define symbol_7 34
#define symbol_8 35
#define symbol_9 36

//edge other
#define symbol_plus 37
#define symbol_sub 38
#define symbol_mul 39
#define symbol_div 40
#define symbol_mod 41
#define symbol_greater 42
#define symbol_less 43
#define symbol_assign 44
#define symbol_exclaim 45
#define symbol_and 46
#define symbol_or 47
#define symbol_leftlittlebracket 48
#define symbol_rightlittlebracket 49
#define symbol_leftbigbracket 50
#define symbol_rightbigbracket 51
#define symbol_semicolon 52
#define symbol_downline 53
#define symbol_comma 54

class Edge {
public:
    int to, nxt, symbol;
};

class Graph {
public:
    int head[NUM_NODES];
    int wordType[NUM_NODES];
    int ecnt, ncnt;
    Edge e[NUM_EDGES];
    Graph();
    void addEdge(int u, int v, int symbol);
    void makeNFA();
    Graph makeDFA();
    set<int> epsilonClosure(int start);
    set<int> epsilonClosure(set<int> start);
    set<int> oneSet(int start);
    set<int> Ja(set<int> start, int a);
    int getWordType(set<int> now);
    int getNext(int now, int a);
    bool setInSet(set<int> a, set<int> b);
    pair<set<int>, bool> JaAndIfReachEmpty(set<int> start, int a);
    pair<set<int>, int> whoToDiv(list<set<int>> partition);
    Graph minimizeDFA();
};
#endif