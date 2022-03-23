#include"error.h"
#include<iostream>

Error::Error(int t):errRow(0), errCol(0), errType(t), errContent() {}
Error::Error(int t, string ctnt) : errRow(0), errCol(0), errType(t), errContent(ctnt) {}
Error::Error(int r,int c,int t) : errRow(r), errCol(c), errType(t), errContent() {}
Error::Error(int r, int c, int t, string ctnt) : errRow(r), errCol(c), errType(t), errContent(ctnt) {}

void Error::what() {
	switch (errType) {
	case _MATRIX_COLUMN_ERR: matColErr(); break;
	case _MATRIX_CHAR_ERR: matCharErr(); break;
	case _MATRIX_RBRACKET_ERR: matBracketErr(); break;
	case _NUMBER_ZERO_ERR: numZeroErr(); break;
	case _UNKNOWN_SYMBOL_ERR: unknownSymbol(); break;
	}
	exit(1);
}

void Error::errPrint() {
	if (errRow) {
		cout << "#row:" << errRow << " col:" << errCol;
	}
	cout << "#err";
}

void Error::matColErr() {
	errPrint();
	cout << _MATRIX_COLUMN_ERR << ": Different number of matrix columns." << endl;
}

void Error::matCharErr() {
	errPrint();
	cout << _MATRIX_CHAR_ERR << ": Character " << errContent << " are not expected." << endl;
}

void Error::matBracketErr() {
	errPrint();
	cout << _MATRIX_RBRACKET_ERR << ": Missing right bracket of matrix." << endl;
}

void Error::numZeroErr() {
	errPrint();
	cout << _NUMBER_ZERO_ERR << ": Integer cannot start with zero." << endl;
}

void Error::unknownSymbol() {
	errPrint();
	cout << _UNKNOWN_SYMBOL_ERR << ": Unknown symbol " << errContent << "." << endl;
}
