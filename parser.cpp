#include<map>
#include<iostream>
#include<vector>
#include"parser.h"

extern map<char, int> Vt;
extern map<char, int> Vn;
extern vector<vector<int>> action;
extern vector<vector<int>> go;
extern word uWord;

//	״̬ջ
stack<int> stateStack;
// ����ջ
stack<symbol> symbolStack;

// ��ջ����
int popSize[] = { 1, 3, 2, 1, 3, 3, 3, 3, 3, 3, 3, 2, 3, 1 };
char nTers[] = { 'T', 'S', 'S', 'A', 'A', 'Q', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E' };

symbol getch();		/* ��ȡ���� */

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
			int index = nextS - ACC;
			for (int i = 0; i < popSize[index]; i++) {
				stateStack.pop();
				symbolStack.pop();
				// ��ȡ��Լ������Ϣ
				// ...
			}
			// ��ջ��ջ��״̬
			S = stateStack.top();

			// ���ݹ�Լ���Ա������и�ֵ�����
			// ...
		
			// ����Լ��ķ�����ӽ�����ջ
			symbolStack.push(symbol(nTers[index]));
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