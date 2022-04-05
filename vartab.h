#pragma once
#include<string>
#include"globals.h"

const int  MAXSIZE = 255;		/* 数组大小 */

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
	// 在符号表中查找变量
	variable* findWord(string name, int key);
	// 改变变量值
	void updateWord(variable var, int key);
	// 向符号表中添加变量
	void insertWord(variable var, int key);
	// 删除符号表中变量
	void deleteWord(string name, int key);
	// 获取字符串的hash值
	int getKey(string name);

	// 遍历TBALE
	void printTable();
};