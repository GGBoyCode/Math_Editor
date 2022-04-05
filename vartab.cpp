#include"vartab.h"

int Table::getKey(string name) {
	return hashStr(name) % MAXSIZE;
}

variable* Table::findWord(string name, int key) {
	variable* ptr = nullptr;

	for (variable* i = tab[key]; i != nullptr; i = i->next) {
		if (name == i->name) {
			ptr = i;
		}
	}

	// 若找到返回变量指针，否则返回空指针nullptr
	return ptr;
}

void Table::updateWord(variable var, int key) {
	variable* ptr = findWord(var.name, key);

	// 若当前变量不存在，则将变量添加进入符号表
	if (!ptr) {
		insertWord(var, key);
	}
	else {
		ptr->type = var.type;
		ptr->val = var.val;
	}
}

void Table::insertWord(variable var, int key) {
	variable* ptr = findWord(var.name, key);
	// 若表中没有当前变量则添加变量到表中
	if (!ptr) {
		ptr = new variable(var.name, var.val, var.type);
		variable* last = tab[key];
		if (last != nullptr) {
			while (last->next != nullptr) last = last->next;
			last->next = ptr;
		}
		else {
			tab[key] = ptr;
		}
	}
	else {
		updateWord(var, key);
	}
}

void Table::deleteWord(string name, int key) {
	variable* ptr = findWord(name, key);

	// 若变量存在则删除该变量，并将该变量前一个指针的next赋值为其后一个指针
	if (ptr) {
		variable* p = tab[key];
		if (ptr == p) tab[key] = ptr->next;
		else {
			while (p->next != ptr) p = p->next;
			p->next = ptr->next;
		}
		delete ptr;
	}
}

void Table::printTable() {
	for (int i = 0; i < MAXSIZE; i++) {
		variable* ptr = tab[i];		 
		while (ptr) {
			if (ptr->type == _SYN_NUM) {
				cout << ptr->name << "=" << (* ptr->val.num) << endl;
			}
			else {
				cout << ptr->name << "=" << endl;
				(*ptr->val.mat).print();
				cout << endl;
			}
			ptr = ptr->next;
		}		 
	}
}