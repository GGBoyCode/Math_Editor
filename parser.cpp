#include<map>
#include<iostream>
#include<vector>
#include"parser.h"

extern map<char, int> Vt;
extern map<char, int> Vn;
extern vector<vector<int>> action;
extern vector<vector<int>> go;
extern word uWord;

//	状态栈
stack<int> stateStack;
// 符号栈
stack<symbol> symbolStack;

// 退栈个数
int popSize[] = { 1, 3, 2, 1, 3, 3, 3, 3, 3, 3, 3, 2, 3, 1 };
char nTers[] = { 'T', 'S', 'S', 'A', 'A', 'Q', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E' };

symbol getch();		/* 获取符号 */

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
			int index = nextS - ACC;
			for (int i = 0; i < popSize[index]; i++) {
				stateStack.pop();
				symbolStack.pop();
				// 获取归约变量信息
				// ...
			}
			// 退栈后，栈顶状态
			S = stateStack.top();

			// 根据归约，对变量进行赋值或计算
			// ...
		
			// 将归约后的符号添加进符号栈
			symbolStack.push(symbol(nTers[index]));
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