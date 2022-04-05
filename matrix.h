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
	// ��ȡ��������
	int getRowSize();
	// ��ȡ��������
	int getColSize();
	// ��ȡ�����С
	int getSize();
	// ��ӡ����
	void print();
};