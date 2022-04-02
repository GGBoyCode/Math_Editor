#include<iostream>
#include<fstream>
#include"main.h"
using namespace std;

// 源文件
string source = "";
// 终结符
map<char, int> Vt;
// action表
vector<vector<int>> action;
// 非终结符
map<char, int> Vn;
// goto表
vector<vector<int>> go;

// 读取源文件
void readSourceFile();
// 读取action表
void readActionTable();
// 读取goto表
void readGotoTable();

int main() {
	/*readSourceFile();
	readActionTable();
	readGotoTable();*/
	try {
		//cout << "*****************************" << endl;
		//LRPaser();
		Number N1("21.9"), N2("3.14"), N3("9.999999");
		N2.setSign(false);
		//Number::figure = 12;
		//Number N4 = N1 + N3;
		//N1.floor();

		Number N = N1.pow(N2);
		cout << N;
	}
	catch (Error e) {
		e.what();
	}
	
	return 0;
}

void readSourceFile() {
	// 打开源文件
	ifstream in("code.txt", ios::in);
	if (!in) {
		cout << "Failed to open file" << endl;
		exit(1);
	}
	// 读取源文件
	while (!in.eof()) source += in.get();

	in.close();
}

void readActionTable() {
	// 打开action表文件
	ifstream in("action.txt", ios::in);
	if (!in) {
		cout << "Failed to open file" << endl;
		exit(1);
	}

	int index = 0;
	char c = in.get();
	while (c != '\n') {
		if (c != ' ' && c != '\t') {
			Vt[c] = index++;
		}
		c = in.get();
	}

	int size = Vt.size();
	while (!in.eof()) {
		vector<int> temp(size);
		for (int i = 0; i < size;i++) {
			in >> temp[i];
		}
		action.push_back(temp);
	}

	for (int i = 0; i < action.size(); i++) {
		for (int j = 0; j < size; j++) {
			cout << action[i][j] << "\t";
		}
		cout << endl;
	}

	in.close();
}

void readGotoTable() {
	// 打开goto表文件
	ifstream in("goto.txt", ios::in);
	if (!in) {
		cout << "Failed to open file" << endl;
		exit(1);
	}

	int index = 0;
	char c = in.get();
	while (c != '\n') {
		if (c != ' ' && c != '\t') {
			Vn[c] = index++;
		}
		c = in.get();
	}

	int size = Vn.size();
	while (!in.eof()) {
		vector<int> temp(size);
		for (int i = 0; i < size; i++) {
			in >> temp[i];
		}
		go.push_back(temp);
	}

	for (int i = 0; i < go.size(); i++) {
		for (int j = 0; j < size; j++) {
			cout << go[i][j] << "\t";
		}
		cout << endl;
	}

	in.close();
}
