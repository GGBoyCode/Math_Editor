#include"number.h"

// С��λ��ΪĬ��λ��
int Number::figure = DEFAULT_FIGURE;
// ��ʼ����λ����λ��־
int Number::iflag = 0;
int Number::oflag = 0;

Number::Number(string number, bool sign) :sign(sign) {
	// ���ֳ���
	int size = number.size();
	// ��¼������С�����ֳ���
	integerLength = decimalLength = 0;

	// �Ƿ�ΪС��
	pointPos = -1;

	// ����Ƿ�Ϊ����
	for (int i = 0; i < size; i++) {
		if (number[i] < '0' || number[i] > '9') {
			if (pointPos == -1 && number[i] == '.') { pointPos = i; continue; }
			else throw Error(_NOT_A_NUMBER_ERR, quotationMarksChar(number[i]));
		}
		if (pointPos == -1) integerLength++;
		else decimalLength++;
	}
	// �ж��Ƿ������㿪ͷ�ķ�һλ����
	if (integerLength > 1 && number[0] == '0') throw Error(_NUMBER_ZERO_ERR);

	// ����������λ��Ϊ0
	if (!integerLength) { number = '0' + number; integerLength = 1; }
	// ��С������λ��Ϊ0
	if (!decimalLength) { number += '.'; }
	// С����λ��
	pointPos = integerLength;
	// ����Ĭ��λ�������ü�
	decimalLength = decimalLength > figure ? figure : decimalLength;

	this->number = number.substr(0, integerLength + decimalLength + 1);
}

Number operator+(Number& N1, Number& N2) {
	// N1 - N2 �� N2 - N1
	if (N1.sign && !N2.sign || !N1.sign && N2.sign) {
		string num;
		if (N1 < N2) {
			num = reduce(N2, N1);
			return Number(num, !N1.sign);
		}
		else {
			num = reduce(N1, N2);
			return Number(num, N1.sign);
		}
	}// N1 + N2 �� -(N1 + N2)
	else {
		return Number(add(N1, N2), N1.sign);
	}
}

Number operator-(Number& N1, Number& N2) {
	// N1 - N2 �� N2 - N1
	if(N1.sign && N2.sign || !N1.sign && !N2.sign) {
		string num;
		if (N1 < N2) {
			num = reduce(N2, N1);
			return Number(num, !N1.sign);
		}
		else {
			num = reduce(N1, N2);
			return Number(num, N1.sign);
		}
	}// N1 + N2 �� -(N1 + N2)
	else {
		return Number(add(N1, N2), N1.sign);
	}
}

Number operator*(Number& N1, Number& N2) {
	int len1 = N1.decimalLength + N1.decimalLength;
	int len2 = N1.decimalLength + N1.decimalLength;
	string num = "0";

	for (int i = len2; i >= 0; i--) {
		if (i != N2.pointPos) {
			string n;
			for (int j = len1; j >= 0; j--) {
				if (j != N1.pointPos) {
					int digit = (N1.number[j] - '0') * (N2.number[i] - '0') + Number::iflag;
					Number::iflag = digit / 10;
					digit %= 10;
					n = char(digit + '0') + n;
				}
			}
			// ��λ����Ϊ��
			if (Number::iflag) {
				n = char(Number::iflag + '0') + n;
				Number::iflag = 0;				
			}

			// ��10
			if (num != "0") num += '0';

			// ���
			Number N1(num), N2(n);
			num = add(N1, N2);
		}
	}
	return Number("0");
}

Number operator/(Number& N1, Number& N2) {
	return Number("0");
}

ostream& operator<<(ostream& cout, Number& N) {
	N.addZero(Number::figure);
	if (!N.sign) cout << "-";
	cout << N.number;
	return cout;
}

bool operator<(Number& N1, Number& N2) {
	if (N1.integerLength < N2.integerLength) {
		return true;
	}
	else if (N1.integerLength > N2.integerLength) {
		return false;
	}
	return N1.number < N2.number;
}
// ��
string add(Number& N1, Number& N2) {
	string num;

	// ���㴦��
	int len = max(N1.decimalLength, N2.decimalLength);
	N1.addZero(len), N2.addZero(len);

	// ����С������
	for (int i = len; i > 0; i--) {
		int digit = N1.number[N1.pointPos + i] + N2.number[N2.pointPos + i] - '0' + Number::iflag;
		Number::judgeIflag(digit);
		num = char(digit) + num;
	}

	num = '.' + num;

	// ����������ͬλ����
	len = max(N1.integerLength, N2.integerLength);
	// ������������
	for (int i = 1; i <= len; i++) {
		int digit = 0;
		if (N1.integerLength < i) {
			digit = N2.number[N2.pointPos - i] + Number::iflag;
		}
		else if (N2.integerLength < i) {
			digit = N1.number[N1.pointPos - i] + Number::iflag;
		}
		else {
			digit = N1.number[N1.pointPos - i] + N2.number[N2.pointPos - i] - '0' + Number::iflag;
		}
		Number::judgeIflag(digit);
		num = char(digit) + num;
	}

	if (Number::iflag) {
		num = char('0' + Number::iflag) + num;
		Number::iflag = 0;
	}

	return num;
}
// ��
string reduce(Number& N1, Number& N2) {
	string num;
	
	// ���㴦��
	int len = max(N1.decimalLength, N2.decimalLength);
	N1.addZero(len), N2.addZero(len);

	// С�����ִ���
	for (int i = len; i > 0; i--) {
		int digit = N1.number[N1.pointPos + i] - N2.number[N2.pointPos + i] - Number::oflag;
		Number::judgeOflag(digit);
		num = char(digit + '0') + num;
	}

	num = '.' + num;

	// �������ִ���
	// ��¼ǰ׺��
	int preZero = 0;
	len = max(N1.integerLength, N2.integerLength);
	for (int i = 1; i <= len; i++) {
		int digit = 0;
		// Ҫ��֤���������ڼ���������ֵΪ����
		if (N2.integerLength < i) {
			digit = N1.number[N1.pointPos - i] - '0' - Number::oflag;
		}
		else {
			digit = N1.number[N1.pointPos - i] - N2.number[N2.pointPos - i] - Number::oflag;
		}
		Number::judgeOflag(digit);
		if (digit) preZero = 0; else preZero++;
		num = char(digit + '0') + num;
	}

	// ȥ��ǰ׺��
	if (preZero) num = num.substr(preZero);

	return num;
}

// ����
void Number::addZero(int len) {
	for (int i = decimalLength; i < len; i++) {
		number += '0';
	}

	decimalLength = len;
}
// ���÷���
void Number::setSign(bool sign) {
	this->sign = sign;
}

// �ж��Ƿ��λ
void Number::judgeIflag(int &digit) {
	iflag = 0;
	if (digit > '9') { digit -= 10; iflag = 1; };
}

// �ж��Ƿ���λ
void Number::judgeOflag(int& digit) {
	oflag = 0;
	if (digit < 0) { digit += 10; oflag = 1; }
}