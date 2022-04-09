#pragma once
#include<string>
#include<iostream>
#include<vector>
#include"Number.h"
using namespace std;

class Matrix {
private:
	int row;
	int col;
	int size;
	vector<Number> content;
public:
	// �������
	Matrix(string mat);
	Matrix(int row, int col, string num = "0");

	// ��ȡ��������
	int getRowSize();
	// ��ȡ��������
	int getColSize();
	// ��ȡ�����С
	int getSize();
	// ��ӡ����
	void print();
	// ���쵥λ����
	void unitMat();

	// �������������
	friend Matrix operator+(Matrix M1, Matrix M2);
	friend Matrix operator-(Matrix M1, Matrix M2);
	friend Matrix operator*(Matrix M1, Matrix M2);
	friend Matrix operator*(Matrix Mat, Number Num);
	friend Matrix operator/(Matrix Mat, Number Num);
	friend Matrix operator^(Matrix Mat, Number Num);

	Number operator[](int index);
};