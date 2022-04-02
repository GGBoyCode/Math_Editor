#pragma once
#include"error.h"
#include"globals.h"
#include<string>
using namespace std;

// Ĭ��С��λ��
const int DEFAULT_FIGURE = 18;

class Number {
public:
	static int figure;				/* С��λ�� */
	static int iflag;				/* ��λ��־ */
	static int oflag;				/* ��λ��־ */
private:
	string number;					/* ��ֵ */
	bool sign;						/* �������� */
	int integerLength;				/* �������� */
	int decimalLength;				/* С������ */
	int pointPos;					/* С����λ�� */
private:
	// ��
	string add(Number& N);
	// ��
	string reduce(Number& N);
	// ȥ��С���㣬�õ�һ��������
	string getBigNumber();
public:
	// ���캯��, ����Ĭ��Ϊ����
	Number(string number, bool sign = true);

	// ��
	Number pow(Number X);

	// �������������
	friend Number operator+(Number N1, Number N2);
	friend Number operator-(Number N1, Number N2);
	friend Number operator*(Number N1, Number N2);
	friend Number operator/(Number N1, Number N2);
	friend Number operator%(Number N1, Number N2);
	friend Number operator^(Number N1, Number N2);
	friend ostream& operator<<(ostream& cout, Number& N);
	// ��ϵ���������
	friend bool operator<(Number& N1, Number& N2);
	friend bool operator==(Number& N1, Number& N2);
	friend bool operator>(Number& N1, Number& N2);
	friend bool operator<=(Number& N1, Number& N2);
	friend bool operator>=(Number& N1, Number& N2);

	// С��ĩβ���㴦��
	void addZero(int len);
	// ���÷���
	void setSign(bool sign);
	// ������ֵ
	void setNumber(string number);
	// ����ȡ��
	void floor();
	// ��ȡ��ֵ
	string getNumber();
	// ��ȡ����
	bool getSign();

	// ��̬����
	static void judgeIflag(int &digit);
	static void judgeOflag(int& digit);
	// ������
	static Number quickPow(Number& N, Number& X);
	static Number getMinNumber();
};