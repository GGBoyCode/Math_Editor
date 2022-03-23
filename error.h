#pragma once
#include<string>
using namespace std;

/********* �������� *********/
const int _MATRIX_COLUMN_ERR = 1;			/* ����������ƥ�� */
const int _MATRIX_CHAR_ERR = 2;				/* ������ַǷ��ַ� */
const int _MATRIX_RBRACKET_ERR = 3;			/* ����������ȱʧ */
const int _NUMBER_ZERO_ERR = 4;				/* �������㿪ͷ���� */
const int _UNKNOWN_SYMBOL_ERR = 5;			/* δ֪���Ŵ��� */
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
	
	// �������㿪ͷ
	void numZeroErr();
	// δ֪����
	void unknownSymbol();
};