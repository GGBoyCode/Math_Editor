#include<map>
#include<iostream>
#include<vector>
#include"parser.h"

extern map<char, int> Vt;
extern map<char, int> Vn;
extern vector<vector<int>> action;
extern vector<vector<int>> go;
extern word uWord;
extern Table table;
extern int row, column;

//	状态栈
stack<int> stateStack;
// 符号栈
stack<symbol> symbolStack;

// 退栈个数
int popSize[] = { 1, 3, 2, 1, 3, 3, 3, 3, 3, 3, 3, 2, 3, 1 };
char nTers[] = { 'T', 'S', 'S', 'A', 'A', 'Q', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E' };

symbol getch();		/* 获取符号 */
// 从符号表中找单词
word findTable(word wrd);
word operation(word uWord1, word uWord2, char oper);

void LRPaser() {
	// 初始化状态栈和符号栈 
	stateStack.push(0);
	symbolStack.push(symbol('$'));

	// 第一个字符
	symbol a = getch();

	// 当前状态
	int S = stateStack.top();
	// 下一个状态
	int nextS = action[S][Vt[a.ch]];
	while (nextS != ACC) {
		// 移进项目
		if (nextS >= 0 && nextS < ACC) {
			stateStack.push(nextS);
			symbolStack.push(a);
			// 读取下一个符号
			a = getch();
		}// 归约项目
		else if(nextS >= ACC){
			// 归约变量数组
			vector<symbol> array;
			// 归约符号
			symbol sym;
			int index = nextS - ACC;
			for (int i = 0; i < popSize[index]; i++) {	
				// 获取归约变量信息
				array.insert(array.begin(), symbolStack.top());
				// 退栈
				stateStack.pop();
				symbolStack.pop();
			}
			// 退栈后，栈顶状态
			S = stateStack.top();
			sym.ch = nTers[index];
			// 根据归约，对变量进行赋值或计算
			// 第一个归约变量字符为i
			if (array[0].ch == 'i') {
				// 根据文法，归约变量数组大于1，为赋值语句
				if (array.size() > 1) {
					// 将表示符i的值赋为右值
					table.insertWord(variable(*array[0].uWord.val.name, array[2].uWord.val, array[2].uWord.tokenId), table.getKey(*array[0].uWord.val.name));
				}// 归约变量数组等于1，为规则E->i的归约
				else {
					sym.uWord = array[0].uWord;
				}
			}// 第一个归约变量字符为E
			else if(array[0].ch == 'E') {
				sym.uWord = operation(array[0].uWord, array[2].uWord, array[1].ch);
			}
			else if (array[0].ch == '-') {
				sym.uWord = array[1].uWord;
				if (sym.uWord.tokenId == _SYN_NUM) {
					sym.uWord.val.num->setSign(!sym.uWord.val.num->getSign());
				}
			}
			else if (array[0].ch == '(') {
				sym.uWord = array[1].uWord;
			}
		
			// 将归约后的符号添加进符号栈
			symbolStack.push(sym);
			// 将归约后的状态添加进状态栈， 其中状态由goto函数给出
			stateStack.push(go[S][Vn[nTers[index]]]);
		}// 错误
		else {
			cout << "error" << endl;
			exit(1);
		}

		// 当前状态
		S = stateStack.top();
		// 下一个状态
		nextS = action[S][Vt[a.ch]];
	}
}

symbol getch() {
	symbol S;
	scan();
	// 若单词种别为标识符，常数或矩阵，则返回i
	if (uWord.tokenId == _SYN_ID ||
		uWord.tokenId == _SYN_NUM ||
		uWord.tokenId == _SYN_MAT) {
		S.ch = 'i';
	}
	else {
		S.ch = uWord.val.sym;
	}

	S.uWord = uWord;

	return S;
}

// 从符号表中找单词
word findTable(string name) {
	word ans;

	variable* ptr = table.findWord(name, table.getKey(name));
	// 若没单词表中没有该单词，抛出错误
	if (!ptr) throw Error(row, column, _UNKNOWN_WORD_ERR, name);
	ans.tokenId = ptr->type;
	ans.val = ptr->val;

	return ans;
}

word operation(word uWord1, word uWord2, char oper) {
	word ans;

	// 若单词为标识符，则查符号表等到标识符内容
	if (uWord1.tokenId == _SYN_ID) uWord1 = findTable(*uWord1.val.name);
	if (uWord2.tokenId == _SYN_ID) uWord2 = findTable(*uWord2.val.name);


	// 若单词是类型相同，则计算
	if (uWord1.tokenId == uWord2.tokenId) {
		ans.tokenId = uWord1.tokenId;
		if (uWord1.tokenId == _SYN_NUM) {
			Number* num = new Number();
			switch (oper) {
			case '+': *num = *uWord1.val.num + *uWord2.val.num; break;
			case '-': *num = *uWord1.val.num - *uWord2.val.num; break;
			case '*': *num = *uWord1.val.num * *uWord2.val.num; break;
			case '/': *num = *uWord1.val.num / *uWord2.val.num; break;
			case '^': *num = *uWord1.val.num ^ *uWord2.val.num; break;
			}
			ans.val.num = num;
		}
		
	}// 否则抛出错误
	else {
		throw Error(row, column, _TYPE_ERR);
	}

	return ans;
}