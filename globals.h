/* ȫ������ */
#pragma once
#include<map>
#include<vector>
#include<string>
#include"matrix.h"
using namespace std;

/********* �����ֱ��� *********/
const int _SYN_WHILE = 1;
const int _SYN_IF = 2;
const int _SYN_ELSE = 3;
const int _SYN_FOR = 4;
const int _SYN_END = 5;
/* ����Ϊ�ؼ����ֱ��� */

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
const int _SYN_ID = 16;					/* ��ʶ�� */
const int _SYN_NUM = 17;				/* ���� */
const int _SYN_MAT = 18;				/* ���� */

const int _SYN_EOF = -1;                 /* ������ */
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

/* �������� */
string quotationMarksChar(char c);		/* ���ַ�'c'��Ϊ��������������ַ���"\'c\'" */