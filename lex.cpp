#include<string>
#include"lex.h"
using namespace std;

extern string source;	/* 资源文件 */
int row,		/* 行号 */
column,			/* 列号 */
locate,			/* 下一个字符下标 */
locateStart;	/* 下一个单词开始位置 */
word uWord;		/* 单词 */
string keyWords[5] = { "while", "if", "else", "for", "end" };

/* 函数声明 */
bool isDigit(char ch);					/* 判断是否为数字 */
bool isLetter(char ch);					/* 判断是否为字母 */
void doStart();							/* 开始识别第一个字母 */
void tag();								/* 找出标识符部分 */
void doTag();							/* 识别标识符或关键字 */
void num();								/* 找出常数部分 */
void doNum();							/* 识别常数 */
void doMat();							/* 识别矩阵 */
void end();								/* 对运算符、界符等单词的内容赋值 */
void doAssign();						/* 识别赋值符号 */
void doPlus();							/* 识别加号 */
void doMinus();							/* 识别减号 */
void doTimes();							/* 识别乘号 */
void doDivide();						/* 识别除号 */
void doPower();							/* 识别幂 */
void doLParen();						/* 识别左括号 */
void doRParen();						/* 识别右括号 */
void doComma();							/* 识别逗号 */
void doColon();							/* 识别分号 */
void printWord();						/* 打印单词 */
void doEOF();							/* 打印结束符 */

void read() {
	int len = source.length();
	locate = locateStart = 0;
	row = column = 1;
	while (source[locate] != _SYN_EOF) {
		scan();
	}
}

void scan() {
	doStart();
	printWord();
}

void doStart() {
	locateStart = locate;
	switch (source[locate]) {
	case '=': doAssign(); break;
	case '+': doPlus(); break;
	case '-': doMinus();	 break;
	case '*': doTimes(); break;
	case '/': doDivide();  break;
	case '^': doPower(); break;
	case '(': doLParen(); break;
	case ')': doRParen(); break;
	case ',': doComma(); break;
	case ';': doColon(); break;
	case -1: doEOF(); break;
	default:
		// 第一个字符是字母
		if (isLetter(source[locate])) {
			doTag();
		}
		// 第一个字符是数字
		else if (isDigit(source[locate])) {
			doNum();
		}
		// 第一个字符是左括号
		else if(source[locate] == '[') {
			locate++;
			locateStart = locate;
			doMat();
		}
		else {
			// 若不是以下三种字符则抛出未知字符异常
			if (source[locate] != '\n' &&
				source[locate] != '\t' &&
				source[locate] != ' ') {
				throw Error(row, column, _UNKNOWN_SYMBOL_ERR, quotationMarksChar(source[locate]));
			} // 若为换行符，行号加一，列号初始化为一
			else if (source[locate] == '\n') {
				row++;
				column = 1;
			}// 若为制表符，则列号加一个制表符空格位数
			else if (source[locate] == '\t') {
				column += _TABLE_LENGTH;
			}// 若为空格，则列号加一
			else {
				column++;
			}
			locate++;
			doStart();
		}
		break;
	}
}

bool isDigit(char ch) {
	if ('0' <= ch && ch <= '9') return true;
	return false;
}

bool isLetter(char ch) {
	if ('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z') return true;
	return false;
}

void tag() {
	// 如果是数字或字母，则继续往后探
	while (isDigit(source[locate]) || isLetter(source[locate])) {
		locate++;
		column++;
	}
}

void doTag() {
	// 识别标识符
	tag();

	// 种别码先记为标识符
	uWord.tokenId = _SYN_ID;

	// 获取标识符内容
	uWord.val.name = new string(source.substr(locateStart, locate - locateStart));

	// 判断标识符是否为关键字
	for (int i = 0; i < 5; i++) {
		// 若标识符为关键字，则将种别码记为相应关键字种别码
		if (*uWord.val.name == keyWords[i]) {
			uWord.tokenId = i + 1;
		}
	}
}

void num() {
	// 整数第一位数字是否为0
	bool flag = source[locate] == '0';

	// 整数部分
	while (isDigit(source[locate])) { locate++; column++; }
	if (locate - locateStart > 1 && flag) throw Error(_NUMBER_ZERO_ERR);
	// 小数部分
	if (source[locate] == '.') {
		locate++;
		column++;
		while (isDigit(source[locate])) { locate++; column++; }
	}
}

void doNum() {
	// 识别常数
	num();

	// 种别码记为常数
	uWord.tokenId = _SYN_NUM;
	// 获取常数内容
	uWord.val.num = new string(source.substr(locateStart, locate - locateStart));
}

void doMat() {
	// 若当前符号为右括号则矩阵输入结束，将单词种别码记为矩阵，单词内容记为矩阵类
	if (source[locate] == ']') {
		uWord.tokenId = _SYN_MAT;
		uWord.val.mat = new Matrix(source.substr(locateStart, locate - locateStart));
		locate++;
		column++;
	}// 若当前字符为字母，则矩阵当前值为变量
	else if (isLetter(source[locate])) {
		tag();
		doMat();
	}// 若当前字符为数字，则矩阵当前值为常量
	else if (isDigit(source[locate])) {
		num();
		doMat();
	}// 若当前字符以下三字符，则递归继续查看后面内容
	else if (source[locate] == ',' || source[locate] == ';' || source[locate] == ' ') {
		locate++;
		column++;
		doMat();
	}// 若当前字符不为上述字符
	else {
		// 是否为矩阵右括号缺失
		if (source.length() < locate || source[locate] == '\n') throw Error(row, column, _MATRIX_RBRACKET_ERR);
		// 矩阵中有非法字符	
		else {
			throw Error(row, column, _MATRIX_CHAR_ERR, quotationMarksChar(source[locate]));
		}
	}
}

void end() {
	uWord.val.sym = source[locate];
	locate++;
	column++;
}

void doAssign() {
	uWord.tokenId = _SYN_ASSIGN;
	end();
}

void doPlus() {
	uWord.tokenId = _SYN_PLUS;
	end();
}

void doMinus() {
	uWord.tokenId = _SYN_MINUS;
	end();
}

void doTimes() {
	uWord.tokenId = _SYN_TIMES;
	end();
}

void doDivide() {
	uWord.tokenId = _SYN_DIVIDE;
	end();
}

void doPower() {
	uWord.tokenId = _SYN_POWER;
	end();
}

void doLParen() {
	uWord.tokenId = _SYN_LPAREN;
	end();
}

void doRParen() {
	uWord.tokenId = _SYN_RPAREN;
	end();
}

void doComma() {
	uWord.tokenId = _SYN_COMMA;
	end();
}

void doColon() {
	uWord.tokenId = _SYN_COLON;
	end();
}

void doEOF() {
	uWord.tokenId = _SYN_EOF;
	uWord.val.sym = '$';
	locate++;
	column++;
}

void printWord() {
	cout << "(" << uWord.tokenId << ",";
	if (_SYN_WHILE <= uWord.tokenId && uWord.tokenId <= _SYN_END ||
		uWord.tokenId == _SYN_ID) {
		cout << *uWord.val.name;
	}
	else if (uWord.tokenId == _SYN_NUM) {
		cout << *uWord.val.num;
	}
	else if (uWord.tokenId == _SYN_MAT) {
		(*uWord.val.mat).print();
	}
	else {
		cout << uWord.val.sym;
	}

	cout << ")" << endl;
}