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
	case _MATRIX_SIZE_MISMATCH_ERR: matSizeMismatch(); break;
	case _NUMBER_ZERO_ERR: numZeroErr(); break;
	case _NOT_A_NUMBER_ERR: numZeroErr(); break;
	case _NEED_INTEGER_ERR: needInteger(); break;
	case _UNKNOWN_SYMBOL_ERR: unknownSymbol(); break;
	case _UNKNOWN_WORD_ERR: unknownWord(); break;
	case _TYPE_ERR: typeErr(); break;
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

void Error::matSizeMismatch() {
	errPrint();
	cout << _MATRIX_SIZE_MISMATCH_ERR << ": Matrix size mismatch." << endl;
}

void Error::numZeroErr() {
	errPrint();
	cout << _NUMBER_ZERO_ERR << ": Integer cannot start with zero." << endl;
}

void Error::notANumberErr() {
	errPrint();
	cout << _NOT_A_NUMBER_ERR << ": "+ errContent + " Not a number." << endl;
}

void Error::needInteger() {
	errPrint();
	cout << _NEED_INTEGER_ERR << ": The operation need integer." << endl;
}

void Error::unknownSymbol() {
	errPrint();
	cout << _UNKNOWN_SYMBOL_ERR << ": Unknown symbol " << errContent << "." << endl;
}

void Error::unknownWord() {
	errPrint();
	cout << _UNKNOWN_WORD_ERR << ": \"" + errContent + "\" is a unknown word." << endl;
}

void Error::typeErr() {
	errPrint();
	cout << _TYPE_ERR << ": Type is not same." << endl;
}