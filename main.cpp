#include "class.h";
#include <iostream>;
#include <string>;

using namespace std;


int main() {
	TM a;
	a.the_date();
	cout << a.DateToString("DD/YYYY/MM");

	string f = "ffff 4 fbfh 02.12.12-13:12:2013 fhg";
	string h = "ss.mm.hh-DD:MM:YYYY";
	cout << endl;
	a.dat_date(f, h).Print(h);

	//std::ifstream file("text.txt");
	//std::string s;
	//std::getline(file, s);
	//file.close();
	//std::ofstream file2("text.txt", std::ios_base::out | std::ios_base::trunc);
	//file2 << a.DateToString(s);
	return 0;
}
