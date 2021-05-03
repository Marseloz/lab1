#include "class.h"
#include <iostream>;
#include <fstream>;


int main() {
	TM a;
	a.the_date();
	std::cout << a.DateFromString("DD/YYYY/MM");

	std::ifstream file("text.txt");
	std::string s;
	std::getline(file, s);
	file.close();
	std::ofstream file2("text.txt", std::ios_base::out | std::ios_base::trunc);
	file2 << a.DateFromString(s);
	return 0;
}