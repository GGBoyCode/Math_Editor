#include"number.h"

// 小数位数为默认位数
int Number::figure = DEFAULT_FIGURE;
// 初始化进位与退位标志
int Number::iflag = 0;
int Number::oflag = 0;

Number::Number(string number, bool sign) :sign(sign) {
	// 数字长度
	int size = number.size();
	// 记录整数和小数部分长度
	integerLength = decimalLength = 0;

	// 是否为小数
	pointPos = -1;

	// 检查是否为数字
	for (int i = 0; i < size; i++) {
		if (number[i] < '0' || number[i] > '9') {
			if (pointPos == -1 && number[i] == '.') { pointPos = i; continue; }
			else throw Error(_NOT_A_NUMBER_ERR, quotationMarksChar(number[i]));
		}
		if (pointPos == -1) integerLength++;
		else decimalLength++;
	}
	// 判断是否有以零开头的非一位整数
	if (integerLength > 1 && number[0] == '0') throw Error(_NUMBER_ZERO_ERR);

	// 若整数部分位数为0
	if (!integerLength) { number = '0' + number; integerLength = 1; }
	// 若小数部分位数为0
	if (!decimalLength) { number += '.'; }
	// 小数点位置
	pointPos = integerLength;
	// 超出默认位数将被裁剪
	decimalLength = decimalLength > figure ? figure : decimalLength;

	this->number = number.substr(0, integerLength + decimalLength + 1);
}

Number operator+(Number& N1, Number& N2) {
	// N1 - N2 或 N2 - N1
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
	}// N1 + N2 或 -(N1 + N2)
	else {
		return Number(add(N1, N2), N1.sign);
	}
}

Number operator-(Number& N1, Number& N2) {
	// N1 - N2 或 N2 - N1
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
	}// N1 + N2 或 -(N1 + N2)
	else {
		return Number(add(N1, N2), N1.sign);
	}
}

Number operator*(Number& N1, Number& N2) {
	int len1 = N1.integerLength + N1.decimalLength;
	int len2 = N2.integerLength + N2.decimalLength;
	string num = "0";

	// 将小数点抹去，看作大整数相乘
	for (int i = len2; i >= 0; i--) {
		if (i != N2.pointPos) {
			string n;
			// 若当前乘数为零，则n=0
			if (N2.number[i] == '0') {
				n = "0";
			}// 若当前乘数不为零，则计算n
			else {
				for (int j = len1; j >= 0; j--) {
					if (j != N1.pointPos) {
						int digit = (N1.number[j] - '0') * (N2.number[i] - '0') + Number::iflag;
						Number::iflag = digit / 10;
						digit %= 10;
						n = char(digit + '0') + n;
					}
				}

				// 进位符不为零
				if (Number::iflag) {
					n = char(Number::iflag + '0') + n;
					Number::iflag = 0;
				}
			}			

			// 乘10
			if (num != "0") num += '0';

			// 相加
			Number n1(num), n2(n);
			num = add(n1, n2);
		}
	}

	// 添加小数点
	num.insert(num.end() - N1.decimalLength - N2.decimalLength, '.');

	return Number(num, !(N1.sign ^ N2.sign));
}

Number operator/(Number& N1, Number& N2) {
	string num;

	// 补零处理
	int len = max(N1.decimalLength, N2.decimalLength);
	N1.addZero(len), N2.addZero(len);

	// 小数位数
	int decimal = 0;
	// 将小数去除小数点变为大整数
	string num1 = N1.number.erase(N1.number.find("."));
	string num2 = N2.number.erase(N2.number.find("."));
	int len1 = num1.length();
	int len2 = num2.length();

	string n;
	// 指向num1补数位置的指针
	int index = len2;
	// 小数计算开始标志
	bool flag = false;

	// 记录当前与num2相除的数n
	if (len1 > len2) {
		n = num1.substr(0, len2);
	}
	else {
		n = num1;
	}

	while (n != "0" && decimal != Number::figure) {
		len = n.size();
		
		Number n2(num2);
		int i = 0;
		// 将数n减至小于数num2
		while (len > len2 || n >= num2) {
			i++;
			Number n1(n);
			n = reduce(n1, n2);
			len = n.size();
		}
		num += char(i + '0');

		// 判断是否是小数部分
		if (flag) decimal++;

		// 计算整数部分
		if (len1 > index) {
			n += N1.number[index];
			index++;
		}// 补零操作，开始计算小数部分
		else {
			n += '0';
			if (!flag && n != "0") { num += '.'; flag = true; }
		}
	}

	return Number(num, !(N1.sign ^ N2.sign));
}

ostream& operator<<(ostream& cout, Number& N) {
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
// 加
string add(Number& N1, Number& N2) {
	string num;

	// 补零处理
	int len = max(N1.decimalLength, N2.decimalLength);
	N1.addZero(len), N2.addZero(len);

	// 计算小数部分
	for (int i = len; i > 0; i--) {
		int digit = N1.number[N1.pointPos + i] + N2.number[N2.pointPos + i] - '0' + Number::iflag;
		Number::judgeIflag(digit);
		num = char(digit) + num;
	}

	// 若不为整数则加小数点
	if (len != 0) num = '.' + num;

	// 整数部分相同位长度
	len = max(N1.integerLength, N2.integerLength);
	// 计算整数部分
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
// 减
string reduce(Number& N1, Number& N2) {
	string num;
	
	// 补零处理
	int len = max(N1.decimalLength, N2.decimalLength);
	N1.addZero(len), N2.addZero(len);

	// 小数部分处理
	for (int i = len; i > 0; i--) {
		int digit = N1.number[N1.pointPos + i] - N2.number[N2.pointPos + i] - Number::oflag;
		Number::judgeOflag(digit);
		num = char(digit + '0') + num;
	}

	// 若不为整数则加小数点
	if(len != 0) num = '.' + num;

	// 整数部分处理
	// 记录前缀零
	int preZero = 0;
	len = max(N1.integerLength, N2.integerLength);
	for (int i = 1; i <= len; i++) {
		int digit = 0;
		// 要保证被减数大于减数，否则值为负数
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

	// 去除前缀零
	if (preZero) num = num.substr(preZero);

	return num;
}

// 添零
void Number::addZero(int len) {
	for (int i = decimalLength; i < len; i++) {
		number += '0';
	}

	decimalLength = len;
}
// 设置符号
void Number::setSign(bool sign) {
	this->sign = sign;
}

// 判断是否进位
void Number::judgeIflag(int &digit) {
	iflag = 0;
	if (digit > '9') { digit -= 10; iflag = 1; };
}

// 判断是否退位
void Number::judgeOflag(int& digit) {
	oflag = 0;
	if (digit < 0) { digit += 10; oflag = 1; }
}