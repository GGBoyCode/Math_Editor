#pragma once
#include"lex.h"
#include<stack>
using namespace std;

// ���������
const int ACC = 26;

typedef struct symbol {
	char ch;
	word uWord;
	symbol() :ch(), uWord() {}
	symbol(char ch):ch(ch),uWord() {}
}symbol;

// LR�ʷ�����
void LRPaser();