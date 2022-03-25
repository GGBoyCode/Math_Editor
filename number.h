#pragma once
#include"error.h"
#include"globals.h"
#include<string>
using namespace std;

// Ĭ��С��λ��
const int DEFAULT_FIGURE = 6;

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
public:
	// ���캯��, ����Ĭ��Ϊ����
	Number(string number, bool sign = true);

	// ����
	friend Number operator+(Number& N1, Number& N2);
	friend Number operator-(Number& N1, Number& N2);
	friend Number operator*(Number& N1, Number& N2);
	friend Number operator/(Number& N1, Number& N2);
	friend ostream& operator<<(ostream& cout, Number& N);
	friend bool operator<(Number& N1, Number& N2);
	friend string add(Number& N1, Number& N2);
	friend string reduce(Number& N1, Number& N2);

	// С��ĩβ���㴦��
	void addZero(int len);
	// ���÷���
	void setSign(bool sign);

	// ��̬����
	static void judgeIflag(int &digit);
	static void judgeOflag(int& digit);
};