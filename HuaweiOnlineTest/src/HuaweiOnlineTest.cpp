#include <iostream>
using namespace std;

/**
 * 题目描述
 写出一个程序，接受一个由字母和数字组成的字符串，和一个字符，然后输出输入字符串中含有该字符的个数。不区分大小写。
 输入描述:
 第一行输入一个有字母和数字以及空格组成的字符串，第二行输入一个字符。
 输出描述:
 输出输入字符串中含有该字符的个数。
 */
void matchChar() {
	string line;
	char specChar;
	int specCharAddon = 0;
	int index = 0;
	int count = 0;
	cin >> line;
	cin >> specChar;
	if (specChar >= 'A' && specChar <= 'Z')
		specCharAddon = 'a' - 'A';
	if (specChar >= 'a' && specChar <= 'z')
		specCharAddon = 'A' - 'a';
	for (index = 0; index <= line.length() - 1; ++index) {
		if (line.at(index) == specChar
				|| line.at(index) == specChar + specCharAddon)
			++count;
	}
	cout << count << endl;
}

int main() {
	matchChar();
	return 0;
}
