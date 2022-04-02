#pragma once
#include"error.h"
#include"globals.h"
#include<string>
using namespace std;

// 默认小数位数
const int DEFAULT_FIGURE = 18;

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
private:
	// 加
	string add(Number& N);
	// 减
	string reduce(Number& N);
	// 去除小数点，得到一个大整数
	string getBigNumber();
public:
	// 构造函数, 符号默认为正号
	Number(string number, bool sign = true);

	// 幂
	Number pow(Number X);

	// 算术运算符重载
	friend Number operator+(Number N1, Number N2);
	friend Number operator-(Number N1, Number N2);
	friend Number operator*(Number N1, Number N2);
	friend Number operator/(Number N1, Number N2);
	friend Number operator%(Number N1, Number N2);
	friend Number operator^(Number N1, Number N2);
	friend ostream& operator<<(ostream& cout, Number& N);
	// 关系运算符重载
	friend bool operator<(Number& N1, Number& N2);
	friend bool operator==(Number& N1, Number& N2);
	friend bool operator>(Number& N1, Number& N2);
	friend bool operator<=(Number& N1, Number& N2);
	friend bool operator>=(Number& N1, Number& N2);

	// 小数末尾添零处理
	void addZero(int len);
	// 设置符号
	void setSign(bool sign);
	// 设置数值
	void setNumber(string number);
	// 向下取整
	void floor();
	// 获取数值
	string getNumber();
	// 获取符号
	bool getSign();

	// 静态函数
	static void judgeIflag(int &digit);
	static void judgeOflag(int& digit);
	// 快速幂
	static Number quickPow(Number& N, Number& X);
	static Number getMinNumber();
};