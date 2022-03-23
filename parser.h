#pragma once
#include"lex.h"
#include<stack>
using namespace std;

// 定义结束符
const int ACC = 26;

typedef struct symbol {
	char ch;
	word uWord;
	symbol() :ch(), uWord() {}
	symbol(char ch):ch(ch),uWord() {}
}symbol;

// LR词法分析
void LRPaser();