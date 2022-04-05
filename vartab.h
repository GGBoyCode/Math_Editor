#pragma once
#include<string>
#include"globals.h"

const int  MAXSIZE = 255;		/* �����С */

typedef struct variable {
	struct variable* next;
	string name;
	union wordContent val;
	int type;
	variable(string name, union wordContent val, int type):next(nullptr), name(name), val(val), type(type) {}
} variable;

class Table {
private:
	variable* tab[MAXSIZE];
	hash<string> hashStr;
public:
	// �ڷ��ű��в��ұ���
	variable* findWord(string name, int key);
	// �ı����ֵ
	void updateWord(variable var, int key);
	// ����ű�����ӱ���
	void insertWord(variable var, int key);
	// ɾ�����ű��б���
	void deleteWord(string name, int key);
	// ��ȡ�ַ�����hashֵ
	int getKey(string name);

	// ����TBALE
	void printTable();
};