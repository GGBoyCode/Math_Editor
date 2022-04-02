/* 全局声明 */
#pragma once
#include<map>
#include<vector>
#include<string>
#include"matrix.h"
using namespace std;

/********* 定义种别码 *********/
const int _SYN_WHILE = 1;
const int _SYN_IF = 2;
const int _SYN_ELSE = 3;
const int _SYN_FOR = 4;
const int _SYN_END = 5;
/* 以上为关键字种别码 */

const int _SYN_ASSIGN = 6;				/* = */
const int _SYN_PLUS = 7;				/* + */
const int _SYN_MINUS = 8;				/* - */
const int _SYN_TIMES = 9;				/* * */
const int _SYN_DIVIDE = 10;				/* / */
const int _SYN_POWER = 11;				/* ^ */
const int _SYN_LPAREN = 12;				/* ( */
const int _SYN_RPAREN = 13;				/* ) */
const int _SYN_COMMA = 14;				/* , */
const int _SYN_COLON = 15;				/* ; */
const int _SYN_ID = 16;					/* 标识符 */
const int _SYN_NUM = 17;				/* 常数 */
const int _SYN_MAT = 18;				/* 矩阵 */

const int _SYN_EOF = -1;                 /* 结束符 */
/*****************************/

union wordContent {
    char sym;
    string *name;
    string *num;
    Matrix *mat;
};

typedef struct word {
    int tokenId;
    union wordContent val;
}word;

/* 函数声明 */
string quotationMarksChar(char c);		/* 将字符'c'变为被单引号引起的字符串"\'c\'" */