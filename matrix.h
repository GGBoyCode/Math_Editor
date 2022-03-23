#pragma once
#include<string>
#include<iostream>
#include<vector>
using namespace std;

class Matrix {
private:
	int row;
	int col;
	int size;
	vector<string> content;
public:
	// 构造矩阵
	Matrix(string mat);
	// 获取矩阵行数
	int getRowSize();
	// 获取矩阵列数
	int getColSize();
	// 获取矩阵大小
	int getSize();
	// 打印矩阵
	void print();
};