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
	Matrix(int row, int col);

	// ��ȡ��������
	int getRowSize();
	// ��ȡ��������
	int getColSize();
	// ��ȡ�����С
	int getSize();
	// ��ӡ����
	void print();

	// �������������
	friend Matrix operator+(Matrix M1, Matrix M2);
	friend Matrix operator-(Matrix M1, Matrix M2);
};