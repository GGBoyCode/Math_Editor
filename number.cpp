#include"number.h"

// 小数位数为默认位数
int Number::figure = DEFAULT_FIGURE;
// 初始化进位与退位标志
int Number::iflag = 0;
int Number::oflag = 0;
// 泰勒展开式
Number Taylor(Number& T, Number& X);
// 泰勒展开式第N项
Number term(Number T, Number X, Number N);
// 添加小数点
string addPoint(string num, int point);

Number::Number(string number, bool sign) :sign(sign) {
	setNumber(number);
}

Number operator+(Number N1, Number N2) {
	// N1 - N2 或 N2 - N1
	if (N1.sign && !N2.sign || !N1.sign && N2.sign) {
		string num;
		if (N1 < N2) {
			num = N2.reduce(N1);
			return Number(num, !N1.sign);
		}
		else {
			num = N1.reduce(N2);
			return Number(num, N1.sign);
		}
	}// N1 + N2 或 -(N1 + N2)
	else {
		return Number(N1.add(N2), N1.sign);
	}
}

Number operator-(Number N1, Number N2) {
	// N1 - N2 或 N2 - N1
	if(N1.sign && N2.sign || !N1.sign && !N2.sign) {
		string num;
		if (N1 < N2) {
			num = N2.reduce(N1);
			return Number(num, !N1.sign);
		}
		else {
			num = N1.reduce(N2);
			return Number(num, N1.sign);
		}
	}// N1 + N2 或 -(N1 + N2)
	else {
		return Number(N1.add(N2), N1.sign);
	}
}

Number operator*(Number N1, Number N2) {
	string num1 = N1.getBigNumber();
	string num2 = N2.getBigNumber();
	int len1 =  num1.length();
	int len2 = num2.length();
	string num = "0";
	string suffixZero = "";

	// 将小数点抹去，看作大整数相乘
	for (int i = len2 - 1; i >= 0; i--) {
		string n;
		// 若当前乘数为零，则n=0
		if (num2[i] == '0') {
			n = "0";
		}// 若当前乘数不为零，则计算n
		else {
			for (int j = len1 - 1; j >= 0; j--) {
				int digit = (num1[j] - '0') * (num2[i] - '0') + Number::iflag;
				Number::iflag = digit / 10;
				digit %= 10;
				n = char(digit + '0') + n;
			}

			// 进位符不为零
			if (Number::iflag) {
				n = char(Number::iflag + '0') + n;
				Number::iflag = 0;
			}
		}			

		// 乘10
		if (n != "0") {
			n = n + suffixZero;
		}
		suffixZero += "0";

		// 相加
		Number n1(num), n2(n);
		num = n1.add(n2);
	}

	// 若结果不为零，则添加小数点
	if(num != "0") num = addPoint(num, N1.decimalLength + N2.decimalLength);

	return Number(num, !(N1.sign ^ N2.sign));
}

Number operator/(Number N1, Number N2) {
	string num = "";

	// 补零处理
	int len = max(N1.decimalLength, N2.decimalLength);
	N1.addZero(len), N2.addZero(len);

	// 小数位数
	int decimal = 0;
	// 将小数去除小数点变为大整数
	string num1 = N1.getBigNumber();
	string num2 = N2.getBigNumber();
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
		Number n1(n);
		int i = 0;
		// 将数n减至小于数num2
		while (n2 <= n1) {
			i++;
			n = n1.reduce(n2);
			n1.setNumber(n);
		}
		if(i != 0 || num != "") num += char(i + '0');

		// 判断是否是小数部分
		if (flag) decimal++;

		// 计算整数部分
		if (index < len1) {
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

Number operator%(Number N1, Number N2) {
	// 判断是否为小数
	if (N1.decimalLength || N2.decimalLength) throw Error(_NEED_INTEGER_ERR);

	// 整数长度
	int len1 = N1.number.length();
	int len2 = N2.number.length();

	// 除数n
	string n;
	// 指向num1补数位置的指针
	int index = len2;

	// 记录当前与num2相除的数n
	if (N2 <= N1) {
		n = N1.number.substr(0, len2);
	}
	else {
		return N1;
	}

	Number n2(N2.number);
	Number n1(n);
	while (index <= len1) {		
		// 将数n减至小于数num2
		while (n2 <= n1) {
			n = n1.reduce(n2);
			n1.setNumber(n);
		}

		// 计算整数部分
		if(index < len1) n += N1.number[index];
		index++;
	}

	return n1;
}

Number operator^(Number& N1, Number& N2) {
	return Number("");
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

bool operator==(Number& N1, Number& N2) {
	return N1.number == N2.number;
}

bool operator>(Number& N1, Number& N2) {
	return !(N1 < N2);
}

bool operator<=(Number& N1, Number& N2) {
	return N1 < N2 || N1 == N2;
}

bool operator>=(Number& N1, Number& N2) {
	return N1 > N2 || N1 == N2;
}
// 加
string Number::add(Number& N) {
	string num;

	// 补零处理
	int len = max(decimalLength, N.decimalLength);
	addZero(len), N.addZero(len);

	// 计算小数部分
	for (int i = len; i > 0; i--) {
		int digit = number[pointPos + i] + N.number[N.pointPos + i] - '0' + Number::iflag;
		Number::judgeIflag(digit);
		num = char(digit) + num;
	}

	// 若不为整数则加小数点
	if (len != 0) num = '.' + num;

	// 整数部分相同位长度
	len = max(integerLength, N.integerLength);
	// 计算整数部分
	for (int i = 1; i <= len; i++) {
		int digit = 0;
		if (integerLength < i) {
			digit = N.number[N.pointPos - i] + Number::iflag;
		}
		else if (N.integerLength < i) {
			digit = number[pointPos - i] + Number::iflag;
		}
		else {
			digit = number[pointPos - i] + N.number[N.pointPos - i] - '0' + Number::iflag;
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
string Number::reduce(Number& N) {
	string num;
	
	// 补零处理
	int len = max(decimalLength, N.decimalLength);
	addZero(len), N.addZero(len);

	// 小数部分处理
	for (int i = len; i > 0; i--) {
		int digit = number[pointPos + i] - N.number[N.pointPos + i] - Number::oflag;
		Number::judgeOflag(digit);
		num = char(digit + '0') + num;
	}

	// 若不为整数则加小数点
	if(len != 0) num = '.' + num;

	// 整数部分处理
	// 记录前缀零
	int preZero = 0;
	len = max(integerLength, N.integerLength);
	for (int i = 1; i <= len; i++) {
		int digit = 0;
		// 要保证被减数大于减数，否则值为负数
		if (N.integerLength < i) {
			digit = number[pointPos - i] - '0' - Number::oflag;
		}
		else {
			digit = number[pointPos - i] - N.number[N.pointPos - i] - Number::oflag;
		}
		Number::judgeOflag(digit);
		if (digit) preZero = 0; else preZero++;
		num = char(digit + '0') + num;
	}

	// 去除前缀零
	if (preZero) num = num.substr(preZero);

	return num;
}
// 得到大整数
string Number::getBigNumber() {
	string ans;
	int len = number.size();
	int index = 0;
	while (index < len && (number[index] == '0' || number[index] == '.')) index++;
	
	if (index >= len) ans = "0";
	while (index < len) {
		if (number[index] != '.') ans += number[index];
		index++;
	}

	return ans;
}
// 幂
Number Number::pow(Number X) {
	Number T = *this, N1("1");
	
	// 若数字大于2且指数为正
	if (number.length() > 1 || number >= "2") {
		T = N1 / T;
		T = T - N1;
		
		// 如果指数为负
		if (!X.getSign()) {
			X.setSign(true);
			T = Taylor(T, X);
		}
		else {
			T = Taylor(T, X);
			T = N1 / T;
		}
		
	}
	else {
		if (!X.getSign()) {
			X.setSign(true);
			T = Taylor(T, X);
			T = N1 / T;
		}
		else {
			T = Taylor(T, X);
		}
	}

	return T;
}

Number Taylor(Number& T, Number& X) {
	Number N("0"), N1("1"), ans("0");

	Number item = term(T, X, N);
	Number exp = Number::getMinNumber();
	while (item > exp) {
		N = N1 + N;
		ans = ans + item;
		item = term(T, X, N);
	}

	return ans;
}

Number term(Number T, Number X, Number N) {
	Number N1("1"), ans("1");
	while (N.getNumber() != "0") {
		Number n = T * X;
		n = n / N;
		ans = ans * n;
		N = N - N1;
		X = X - N1;
	}

	return ans;
}

string addPoint(string num, int point) {
	string ans;

	for (int i = point - 1, index = num.length() - 1; i >= 0 || index >= 0; i--) {
		if (index < 0) {
			ans = "0" + ans;
		}
		else {
			ans = num[index] + ans;
			index--;
		}

		if(i == 0) {
			ans = "." + ans;
		}
	}

	return ans;
}

// 快速幂，其中X必须为整数
Number Number::quickPow(Number& N, Number& X) {
	if (X.getNumber() == "0") return Number("1");
	if (X.getNumber() == "1") return N;

	Number N2("2");
	// 取余运算
	Number mod = X % N2;
	// 向下取整
	X = X / N2;
	X.floor();
	Number ans = quickPow(N, X);
	N = N * N;
	if (mod.getNumber() == "1") ans = N * ans;
	return ans;
}

// 向下取整
void Number::floor() {
	decimalLength = 0;
	number = number.substr(0, integerLength);
}

// 添零
void Number::addZero(int len) {
	// 若小数部分位数为0
	if (!decimalLength) { number += '.'; }
	for (int i = decimalLength; i < len; i++) {
		number += '0';
	}

	decimalLength = len;
}
// 设置符号
void Number::setSign(bool sign) {
	this->sign = sign;
}
// 设置数值
void Number::setNumber(string number) {
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
	
	// 小数点位置
	pointPos = integerLength;
	// 超出默认位数将被裁剪
	decimalLength = decimalLength > figure ? figure : decimalLength;

	this->number = number.substr(0, integerLength + decimalLength + 1);
}
// 获取数字串
string Number::getNumber() {
	return number;
}
// 获取符号
bool Number::getSign() {
	return sign;
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

Number Number::getMinNumber() {
	string num = ".";
	for (int i = 0; i < Number::figure - 1; i++) num += "0";
	num += "1";

	return Number(num);
}