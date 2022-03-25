#pragma once
#include"error.h"
#include"globals.h"
#include<string>
using namespace std;

// 默认小数位数
const int DEFAULT_FIGURE = 6;

class Number {
public:
	static int figure;				/* 小数位数 */
	static int iflag;				/* 进位标志 */
	static int oflag;				/* 退位标志 */
private:
	string number;					/* 数值 */
	bool sign;						/* 正负符号 */
	int integerLength;				/* 整数长度 */
	int decimalLength;				/* 小数长度 */
	int pointPos;					/* 小数点位置 */
public:
	// 构造函数, 符号默认为正号
	Number(string number, bool sign = true);

	// 重载
	friend Number operator+(Number& N1, Number& N2);
	friend Number operator-(Number& N1, Number& N2);
	friend Number operator*(Number& N1, Number& N2);
	friend Number operator/(Number& N1, Number& N2);
	friend ostream& operator<<(ostream& cout, Number& N);
	friend bool operator<(Number& N1, Number& N2);
	friend string add(Number& N1, Number& N2);
	friend string reduce(Number& N1, Number& N2);

	// 小数末尾添零处理
	void addZero(int len);
	// 设置符号
	void setSign(bool sign);

	// 静态函数
	static void judgeIflag(int &digit);
	static void judgeOflag(int& digit);
};