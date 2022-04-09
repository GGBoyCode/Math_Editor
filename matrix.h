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
	// 构造矩阵
	Matrix(string mat);
	Matrix(int row, int col, string num = "0");

	// 获取矩阵行数
	int getRowSize();
	// 获取矩阵列数
	int getColSize();
	// 获取矩阵大小
	int getSize();
	// 打印矩阵
	void print();
	// 构造单位矩阵
	void unitMat();

	// 算术运算符重载
	friend Matrix operator+(Matrix M1, Matrix M2);
	friend Matrix operator-(Matrix M1, Matrix M2);
	friend Matrix operator*(Matrix M1, Matrix M2);
	friend Matrix operator*(Matrix Mat, Number Num);
	friend Matrix operator/(Matrix Mat, Number Num);
	friend Matrix operator^(Matrix Mat, Number Num);

	Number operator[](int index);
};