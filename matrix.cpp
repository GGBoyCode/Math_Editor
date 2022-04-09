#include"matrix.h"
#include"error.h"

Matrix::Matrix(string mat) {
	size = col = row = 0;
	content = vector<Number>();
	int column = 0;
	int len = mat.length();	
	int index = 0, pIndex = 0;

	while (index < len) {
		if (mat[index] == ',' || mat[index] == ';') {
			// ��ʼ��col
			if (!row) row++;
			if (row == 1) col++;
			column++;

			if (mat[index] == ';') {
				row++;
				// �����������Ǻͷ���ͬ������ͬ���׳�����
				if (col != column) throw Error(_MATRIX_COLUMN_ERR);
				column = 0;
			}

			content.push_back(Number(mat.substr(pIndex, index - pIndex)));
			pIndex = index + 1;
		}

		index++;
	}
	
	// �����һ������ӽ������
	if (pIndex < index) { 
		content.push_back(Number(mat.substr(pIndex, index - pIndex)));
		column++;
	}
	// �����������Ǻͷ���ͬ������ͬ���׳�����
	if (col != column) throw Error(_MATRIX_COLUMN_ERR);
	size = content.size();
}
Matrix::Matrix(int row, int col) :row(row), col(col),size(row * col) {
	content = vector<Number>(size);
}

int Matrix::getRowSize() {
	return row;
}

int Matrix::getColSize() {
	return col;
}

int Matrix::getSize() {
	return size;
}

void Matrix::print() {
	cout << "[";
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << content[i * col + j];
			if(j != col - 1) cout << ", ";
		}
		if (i != row - 1) cout << "; ";
	}
	cout << "]";
}


Matrix operator+(Matrix M1, Matrix M2) {
	// �׳�����
	if (M1.size != M2.size) throw Error(_MATRIX_SIZE_MISMATCH_ERR);

	Matrix ans(M1.row, M1.col);

	// �ӷ�����
	for (int i = 0; i < M1.size; i++) {
		ans.content[i] = M1.content[i] + M2.content[i];
	}

	return ans;
}

Matrix operator-(Matrix M1, Matrix M2) {
	// �׳�����
	if (M1.size != M2.size) throw Error(_MATRIX_SIZE_MISMATCH_ERR);

	Matrix ans(M1.row, M1.col);

	// �ӷ�����
	for (int i = 0; i < M1.size; i++) {
		ans.content[i] = M1.content[i] - M2.content[i];
	}

	return ans;
}