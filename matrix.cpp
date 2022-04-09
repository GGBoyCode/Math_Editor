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

Matrix::Matrix(int row, int col, string num) :row(row), col(col),size(row * col) {
	content = vector<Number>(size, Number(num));
}

void Matrix::unitMat() {
	// �������Ϊ����
	if (row != col) throw Error(_NON_SQUARE_MATRIX_ERR);
	for (int i = 0; i < row; i++) {
		content[i * col + i] = Number("1");
	}
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

Number Matrix::operator[](int index) {
	return content[index];
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

Matrix operator*(Matrix M1, Matrix M2) {
	// ��M1������������M2������������������
	if (M1.col != M2.row) throw Error(_MATRIX_MUT_ERR);

	Matrix ans(M1.row, M2.col);

	for (int i = 0; i < M1.row; i++) {
		for (int j = 0; j < M2.col; j++) {
			for (int k = 0; k < M1.col; k++) {
				Number n = M1[i * M1.col + k] * M2[k * M2.col + j];
				ans.content[i * M2.col + j] = ans.content[i * M2.col + j] + n;
			}
		}
	}

	return ans;
}

Matrix operator*(Matrix Mat, Number Num) {
	Matrix ans(Mat.row, Mat.col);
	for (int i = 0; i < Mat.size; i++) {
		ans.content[i] = Mat[i] * Num;
	}

	return ans;
}

Matrix operator/(Matrix Mat, Number Num) {
	Matrix ans(Mat.row, Mat.col);
	for (int i = 0; i < Mat.size; i++) {
		ans.content[i] = Mat[i] / Num;
	}

	return ans;
}

Matrix operator^(Matrix Mat, Number Num) {
	Number n2("2");
	Matrix ans(Mat.row, Mat.col);
	// �������Ϊ����
	if (Mat.row != Mat.col) throw Error(_NON_SQUARE_MATRIX_ERR);

	// ʹansΪn�׵�λ����
	ans.unitMat();

	while(Num.getNumber() != "0") {
		Number mod = Num % n2;
		if (mod.getNumber() == "1") {
			ans = ans * Mat;
		}

		Mat = Mat * Mat;
		Num = Num / n2;
		Num.floor();
	}

	return ans;
}