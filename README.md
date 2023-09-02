# TJU-C--compiler
The project designs a lexical analyzer and syntax analyzer for the C-language, which can complete a complete compilation process for the input source language.

test文件夹为测试文件夹，readme.md为说明文档。

Graph.cpp和Graph.hpp文件用来对词法分析器中的各种状态图进行建模。

leftRecursionEliminator.py用来实现语法分析器中对文法的消除左递归，并将改造后的文法输出到grammar_alpha.txt中。

tableGenerator.py用于消除回溯和提取公共左因子，生成FIRST集和FOLLOW集，并构造LL(1)文法的预测分析表，期间改造的文法输出到grammar_beta.txt中，期间生成的分析表以json形式保存到到table.txt中。

writeLog.py用于根据预测分析表按照相应格式输出规约序列。

imp.cpp用于将词法分析器和语法分析器联结在一起，首先读入C- -源代码文件(存放在test文件夹中)，然后使用lex编译程序对其进行解析并将生成的单词符号序列存放到out.txt中进行输出。接着调用leftRecursionEliminator.py和tableGenerator.py生成相应文法和预测分析表，最后将out.txt中的内容输入writeLog.py生成规约序列，并将结果保存在log.txt中。

![image](https://github.com/TJU-healer/TJU-C--compiler/assets/91238369/2cab0bcc-da48-4e66-8565-52c6eafa8574)
