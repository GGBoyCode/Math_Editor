#include<string>
#include"lex.h"
using namespace std;

extern string source;	/* ��Դ�ļ� */
int row,		/* �к� */
column,			/* �к� */
locate,			/* ��һ���ַ��±� */
locateStart;	/* ��һ�����ʿ�ʼλ�� */
word uWord;		/* ���� */
string keyWords[5] = { "while", "if", "else", "for", "end" };

/* �������� */
bool isDigit(char ch);					/* �ж��Ƿ�Ϊ���� */
bool isLetter(char ch);					/* �ж��Ƿ�Ϊ��ĸ */
void doStart();							/* ��ʼʶ���һ����ĸ */
void tag();								/* �ҳ���ʶ������ */
void doTag();							/* ʶ���ʶ����ؼ��� */
void num();								/* �ҳ��������� */
void doNum();							/* ʶ���� */
void doMat();							/* ʶ����� */
void end();								/* �������������ȵ��ʵ����ݸ�ֵ */
void doAssign();						/* ʶ��ֵ���� */
void doPlus();							/* ʶ��Ӻ� */
void doMinus();							/* ʶ����� */
void doTimes();							/* ʶ��˺� */
void doDivide();						/* ʶ����� */
void doPower();							/* ʶ���� */
void doLParen();						/* ʶ�������� */
void doRParen();						/* ʶ�������� */
void doComma();							/* ʶ�𶺺� */
void doColon();							/* ʶ��ֺ� */
void printWord();						/* ��ӡ���� */
void doEOF();							/* ��ӡ������ */

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
		// ��һ���ַ�����ĸ
		if (isLetter(source[locate])) {
			doTag();
		}
		// ��һ���ַ�������
		else if (isDigit(source[locate])) {
			doNum();
		}
		// ��һ���ַ���������
		else if(source[locate] == '[') {
			locate++;
			locateStart = locate;
			doMat();
		}
		else {
			// ���������������ַ����׳�δ֪�ַ��쳣
			if (source[locate] != '\n' &&
				source[locate] != '\t' &&
				source[locate] != ' ') {
				throw Error(row, column, _UNKNOWN_SYMBOL_ERR, quotationMarksChar(source[locate]));
			} // ��Ϊ���з����кż�һ���кų�ʼ��Ϊһ
			else if (source[locate] == '\n') {
				row++;
				column = 1;
			}// ��Ϊ�Ʊ�������кż�һ���Ʊ���ո�λ��
			else if (source[locate] == '\t') {
				column += _TABLE_LENGTH;
			}// ��Ϊ�ո����кż�һ
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
	// ��������ֻ���ĸ�����������̽
	while (isDigit(source[locate]) || isLetter(source[locate])) {
		locate++;
		column++;
	}
}

void doTag() {
	// ʶ���ʶ��
	tag();

	// �ֱ����ȼ�Ϊ��ʶ��
	uWord.tokenId = _SYN_ID;

	// ��ȡ��ʶ������
	uWord.val.name = new string(source.substr(locateStart, locate - locateStart));

	// �жϱ�ʶ���Ƿ�Ϊ�ؼ���
	for (int i = 0; i < 5; i++) {
		// ����ʶ��Ϊ�ؼ��֣����ֱ����Ϊ��Ӧ�ؼ����ֱ���
		if (*uWord.val.name == keyWords[i]) {
			uWord.tokenId = i + 1;
		}
	}
}

void num() {
	// ������һλ�����Ƿ�Ϊ0
	bool flag = source[locate] == '0';

	// ��������
	while (isDigit(source[locate])) { locate++; column++; }
	if (locate - locateStart > 1 && flag) throw Error(_NUMBER_ZERO_ERR);
	// С������
	if (source[locate] == '.') {
		locate++;
		column++;
		while (isDigit(source[locate])) { locate++; column++; }
	}
}

void doNum() {
	// ʶ����
	num();

	// �ֱ����Ϊ����
	uWord.tokenId = _SYN_NUM;
	// ��ȡ��������
	uWord.val.num = new string(source.substr(locateStart, locate - locateStart));
}

void doMat() {
	// ����ǰ����Ϊ���������������������������ֱ����Ϊ���󣬵������ݼ�Ϊ������
	if (source[locate] == ']') {
		uWord.tokenId = _SYN_MAT;
		uWord.val.mat = new Matrix(source.substr(locateStart, locate - locateStart));
		locate++;
		column++;
	}// ����ǰ�ַ�Ϊ��ĸ�������ǰֵΪ����
	else if (isLetter(source[locate])) {
		tag();
		doMat();
	}// ����ǰ�ַ�Ϊ���֣������ǰֵΪ����
	else if (isDigit(source[locate])) {
		num();
		doMat();
	}// ����ǰ�ַ��������ַ�����ݹ�����鿴��������
	else if (source[locate] == ',' || source[locate] == ';' || source[locate] == ' ') {
		locate++;
		column++;
		doMat();
	}// ����ǰ�ַ���Ϊ�����ַ�
	else {
		// �Ƿ�Ϊ����������ȱʧ
		if (source.length() < locate || source[locate] == '\n') throw Error(row, column, _MATRIX_RBRACKET_ERR);
		// �������зǷ��ַ�	
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