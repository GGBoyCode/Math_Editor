#pragma once
#include<string>
using namespace std;

/********* 错误类型 *********/
const int _UNKNOWN_SYMBOL_ERR = 101;			/* 未知符号错误 */
const int _UNKNOWN_WORD_ERR = 102;				/* 未知单词错误 */
const int _TYPE_ERR = 103;						/* 类型错误 */

/* 矩阵类型错误 */
const int _MATRIX_COLUMN_ERR = 201;				/* 矩阵列数不匹配 */
const int _MATRIX_CHAR_ERR = 202;				/* 矩阵出现非法字符 */
const int _MATRIX_RBRACKET_ERR = 203;			/* 矩阵右括号缺失 */
const int _MATRIX_SIZE_MISMATCH_ERR = 204;		/* 矩阵大小不匹配 */

/* 常数类型错误 */
const int _NUMBER_ZERO_ERR = 301;				/* 整数以零开头错误 */
const int _NOT_A_NUMBER_ERR = 302;				/* 不是数字 */
const int _NEED_INTEGER_ERR = 303;				/* 运算需要整数 */

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
	// 打印错误位置信息
	void errPrint();

	// 矩阵列数不匹配
	void matColErr();
	// 矩阵中包含非法字符
	void matCharErr();
	// 矩阵中右括号不匹配
	void matBracketErr();
	// 矩阵大小不匹配
	void matSizeMismatch();
	
	// 整数以零开头
	void numZeroErr();
	// 不是一个数
	void notANumberErr();
	// 需要整数
	void needInteger();

	// 未知符号
	void unknownSymbol();
	// 未知单词
	void unknownWord();
	// 类型错误
	void typeErr();
};