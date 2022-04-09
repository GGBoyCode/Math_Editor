#pragma once
#include<string>
using namespace std;

/********* �������� *********/
const int _UNKNOWN_SYMBOL_ERR = 101;			/* δ֪���Ŵ��� */
const int _UNKNOWN_WORD_ERR = 102;				/* δ֪���ʴ��� */
const int _TYPE_ERR = 103;						/* ���ʹ��� */

/* �������ʹ��� */
const int _MATRIX_COLUMN_ERR = 201;				/* ����������ƥ�� */
const int _MATRIX_CHAR_ERR = 202;				/* ������ַǷ��ַ� */
const int _MATRIX_RBRACKET_ERR = 203;			/* ����������ȱʧ */
const int _MATRIX_SIZE_MISMATCH_ERR = 204;		/* �����С��ƥ�� */

/* �������ʹ��� */
const int _NUMBER_ZERO_ERR = 301;				/* �������㿪ͷ���� */
const int _NOT_A_NUMBER_ERR = 302;				/* �������� */
const int _NEED_INTEGER_ERR = 303;				/* ������Ҫ���� */

/****************************/

class Error {
private:
	int errRow;
	int errCol;
	int errType;
	string errContent;
public:
	Error(int t);
	Error(int t, string ctnt);
	Error(int r, int c, int t);
	Error(int r, int c, int t, string ctnt);
	void what();
private:
	// ��ӡ����λ����Ϣ
	void errPrint();

	// ����������ƥ��
	void matColErr();
	// �����а����Ƿ��ַ�
	void matCharErr();
	// �����������Ų�ƥ��
	void matBracketErr();
	// �����С��ƥ��
	void matSizeMismatch();
	
	// �������㿪ͷ
	void numZeroErr();
	// ����һ����
	void notANumberErr();
	// ��Ҫ����
	void needInteger();

	// δ֪����
	void unknownSymbol();
	// δ֪����
	void unknownWord();
	// ���ʹ���
	void typeErr();
};