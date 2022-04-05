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

//	״̬ջ
stack<int> stateStack;
// ����ջ
stack<symbol> symbolStack;

// ��ջ����
int popSize[] = { 1, 3, 2, 1, 3, 3, 3, 3, 3, 3, 3, 2, 3, 1 };
char nTers[] = { 'T', 'S', 'S', 'A', 'A', 'Q', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E' };

symbol getch();		/* ��ȡ���� */
// �ӷ��ű����ҵ���
word findTable(word wrd);
word operation(word uWord1, word uWord2, char oper);

void LRPaser() {
	// ��ʼ��״̬ջ�ͷ���ջ 
	stateStack.push(0);
	symbolStack.push(symbol('$'));

	// ��һ���ַ�
	symbol a = getch();

	// ��ǰ״̬
	int S = stateStack.top();
	// ��һ��״̬
	int nextS = action[S][Vt[a.ch]];
	while (nextS != ACC) {
		// �ƽ���Ŀ
		if (nextS >= 0 && nextS < ACC) {
			stateStack.push(nextS);
			symbolStack.push(a);
			// ��ȡ��һ������
			a = getch();
		}// ��Լ��Ŀ
		else if(nextS >= ACC){
			// ��Լ��������
			vector<symbol> array;
			// ��Լ����
			symbol sym;
			int index = nextS - ACC;
			for (int i = 0; i < popSize[index]; i++) {	
				// ��ȡ��Լ������Ϣ
				array.insert(array.begin(), symbolStack.top());
				// ��ջ
				stateStack.pop();
				symbolStack.pop();
			}
			// ��ջ��ջ��״̬
			S = stateStack.top();
			sym.ch = nTers[index];
			// ���ݹ�Լ���Ա������и�ֵ�����
			// ��һ����Լ�����ַ�Ϊi
			if (array[0].ch == 'i') {
				// �����ķ�����Լ�����������1��Ϊ��ֵ���
				if (array.size() > 1) {
					// ����ʾ��i��ֵ��Ϊ��ֵ
					table.insertWord(variable(*array[0].uWord.val.name, array[2].uWord.val, array[2].uWord.tokenId), table.getKey(*array[0].uWord.val.name));
				}// ��Լ�����������1��Ϊ����E->i�Ĺ�Լ
				else {
					sym.uWord = array[0].uWord;
				}
			}// ��һ����Լ�����ַ�ΪE
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
		
			// ����Լ��ķ�����ӽ�����ջ
			symbolStack.push(sym);
			// ����Լ���״̬��ӽ�״̬ջ�� ����״̬��goto��������
			stateStack.push(go[S][Vn[nTers[index]]]);
		}// ����
		else {
			cout << "error" << endl;
			exit(1);
		}

		// ��ǰ״̬
		S = stateStack.top();
		// ��һ��״̬
		nextS = action[S][Vt[a.ch]];
	}
}

symbol getch() {
	symbol S;
	scan();
	// �������ֱ�Ϊ��ʶ��������������򷵻�i
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

// �ӷ��ű����ҵ���
word findTable(string name) {
	word ans;

	variable* ptr = table.findWord(name, table.getKey(name));
	// ��û���ʱ���û�иõ��ʣ��׳�����
	if (!ptr) throw Error(row, column, _UNKNOWN_WORD_ERR, name);
	ans.tokenId = ptr->type;
	ans.val = ptr->val;

	return ans;
}

word operation(word uWord1, word uWord2, char oper) {
	word ans;

	// ������Ϊ��ʶ���������ű�ȵ���ʶ������
	if (uWord1.tokenId == _SYN_ID) uWord1 = findTable(*uWord1.val.name);
	if (uWord2.tokenId == _SYN_ID) uWord2 = findTable(*uWord2.val.name);


	// ��������������ͬ�������
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
		
	}// �����׳�����
	else {
		throw Error(row, column, _TYPE_ERR);
	}

	return ans;
}