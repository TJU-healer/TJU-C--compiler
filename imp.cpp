#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>
#include <set>
#include "Graph.hpp"
#define DEBUG

using namespace std;

const int maxn = 1e4 + 5;

int char2num(char ch) {
    if(ch >= 'a' && ch <= 'z') return ch - 'a' + 1;
    if(ch >= 'A' && ch <= 'Z') return ch - 'A' + 1;
    if(ch >= '0' && ch <= '9') return ch - '0' + 27;
    if(ch == '+') return 37;
    if(ch == '-') return 38;
    if(ch == '*') return 39;
    if(ch == '/') return 40;
    if(ch == '%') return 41;
    if(ch == '>') return 42;
    if(ch == '<') return 43;
    if(ch == '=') return 44;
    if(ch == '!') return 45;
    if(ch == '&') return 46;
    if(ch == '|') return 47;
    if(ch == '(') return 48;
    if(ch == ')') return 49;
    if(ch == '{') return 50;
    if(ch == '}') return 51;
    if(ch == ';') return 52;
    if(ch == '_') return 53;
    if(ch == ',') return 54;
    return -1;
}

char ch[maxn];

stack<char> toRead, lexCache;
Graph NFA, DFA, miniDFA;
int now, suc;
bool isMinus;

void input(char *inputFilePath) {
    ifstream inFile(inputFilePath, ios::in | ios::binary);
    inFile.read((char *)&ch, sizeof(ch));
    int len = strlen(ch);
    for(int i = len - 1;i >= 0;i--) toRead.push(ch[i]); 
}

void PrintNow() {
    // minus
    if(suc == 0 || suc == 3 || (suc == 4 && lexCache.top() == ')')) isMinus = true;
    stack<char> tmp;
    while(!lexCache.empty()) { //倒序
        tmp.push(lexCache.top());
        lexCache.pop();
    }
    while(!tmp.empty()) {//依次输出
        printf("%c", tmp.top());
        tmp.pop();
    }
    printf("\t");
    if(suc == 0) {
        printf("<IDN>\n");
        isMinus = true;
    }
    else if(suc == 1) printf("<OP>\n");
    else if(suc == 2) printf("<KW>\n");
    else if(suc == 3) printf("<INT>\n");
    else printf("<SE>\n");
    suc = -1;
    now = 0;
}

void solve(char *outFilePath) {
    freopen(outFilePath, "w", stdout);
    NFA.makeNFA(); //regex -> NFA
    DFA = NFA.makeDFA();  // NFA -> DFA
    miniDFA = DFA.minimizeDFA(); // DFA -> miniDFA
    now = 0, suc = -1;
    while(!toRead.empty()) { //字符栈非空
        if(char2num(toRead.top()) == -1) {//若栈顶字符不可识别
            toRead.pop(); //弹出该字符
            if(!lexCache.empty()) 
                PrintNow(); //输出当前lexCache中存储的内容和相应wordType
        } else {
            //在miniDFA中匹配栈顶字符并进入下一状态
            now = miniDFA.getNext(now, char2num(toRead.top()));
#ifdef DEBUG
            if(isMinus && toRead.top() == '-') {
                suc = miniDFA.wordType[now];
                lexCache.push(toRead.top());
                toRead.pop();
                PrintNow();
                continue;
            }
#endif
            isMinus = false;
            if((now < 0 || miniDFA.wordType[now] == -1) && suc >= 0) {
                //如果当前处于中间状态或死结点并且刚刚经过终态则打印输出
                PrintNow();
            } else { //其余情况下则将栈顶字符放入lexCache中存储并更新suc
                lexCache.push(toRead.top());
                suc = miniDFA.wordType[now]; //-1为中间态，其余为终态
                toRead.pop();
            }
        }
    }
    if(suc != -1) PrintNow(); 
    fclose(stdout);
}

int main(int argc, char **argv) {
    input(argv[1]), solve(argv[2]); //执行词法分析器
    system("python ./leftRecursionEliminator.py"); //执行语法分析器中的消除左递归
    system("python ./tableGenerator.py");   //执行语法分析器中的生成预测分析表
    char path[300] = "python ./writeLog.py  ";  
    strcat(path, argv[2]);
    system(path);   //执行语法分析器中的输出格式化日志
    return 0;
}
