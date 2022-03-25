#include"globals.h"

string quotationMarksChar(char c) {
	return string("\'\'").insert(1, string(1, c));
}