#include "class.h"
#include <iostream>

using namespace std;

TM::TM() {
	//t.reset();
	//d.reset();
}
TM::TM(int sec, int min, int hour, int day, int mon, int data) {
	if (CorrectTime(sec, min, hour)) {
		t.sec = sec;
		t.min = min;
		t.hour = hour;
	}
	else {
		d.reset();
	}
	if (CorrectDate(day, mon, data)) {
		d.day = day;
		d.mon = mon;
		d.year = data;
	}
	else {
		d.reset();
	}
}
TM::TM(const TM& a) {
	this->d = a.d;
	this->t = a.t;
}
TM::TM(TM&& a){
	this->d = a.d;
	this->t = a.t;
}
DATE TM::date() { //метод date() возвращает дату в виде структуры
	time_t timer = std::time(&timer);
	struct tm tabl_date;	// создаём структуру содержащая календарную дату и время, разбитую на составляющие
	localtime_s(&tabl_date, &timer); //заполняем tabl_date данными из timer

	DATE n;
	n = tabl_date;
	return n;
}
TIME TM::time() { //метод time() возвращает время в виде структуры
	time_t timer = std::time(&timer);
	struct tm tabl_date;	// создаём структуру содержащая календарную дату и время, разбитую на составляющие
	localtime_s(&tabl_date, &timer); //заполняем tabl_date данными из timer

	TIME n;
	n = tabl_date; //заполняем n данными из tabl_date
	return n;
}
void TM::the_time() { //метод текущего времени
	this->t = time();
}
void TM::the_date() {//метод текущей даты
	this->d = date();
}
bool TM::CorrectDate(int day, int mon, int data) { //статический метод проверки набора чисел на корректность дате
	if ((day > 0) && (day <= 31)) {
		if ((mon > 0) && (mon <= 12)) {
			if (data >= 1900) {
				return true;
			}
		}
	}
	return false;
}
bool TM::CorrectTime(int sec, int min, int hour) { //статический метод проверки набора чисел на корректность времени
	if ((sec >= 0) && (sec <= 23)) {
		if ((min >= 0) && (min <= 59)) {
			if ((hour >= 0) && (hour <= 23)) {
				return true;
			}
		}
	}
	return false;
}

void TM::Print(string pattern) { //метод печати по заданному шаблону
	cout << DateFromString(pattern);
}

string TM::DateFromString(string pattern) {  //метод перевода даты в строку по заданному формату. Проверить метод на примерах печати в файл и в консоль
	int i = 0;
	char b;
	string s;
	while (pattern[i]) {
		b = pattern[i];
		if ((b == 'D') || (b == 'M') || (b == 'Y')) {
			if (b == 'D') {
				if (d.day < 10) { s += '0'; }
				s += to_string(d.day);
			}
			if (b == 'M') {
				if (d.mon < 10) { s += '0'; }
				s += to_string(d.mon);
			}
			if (b == 'Y') {
				s += to_string(d.year);
			}
			while (pattern[i] == b) {
				i++;
			}
		}
		else {
			s += b;
			i++;
		}
	}
	return s;
}

DATE TM::dat_date(string strok, string pattern) {//статический метод получения даты из строки, метод должен получать 2 параметра строку с датой и строку формата
	DATE dat;
	dat.reset();
	if (strok.size() >= pattern.size()) {
		int i = 0, k = 0;
		while ((i < (int)strok.size()) && (k < (int)pattern.size())) {
			if ((strok[i] >= '0') && (strok[i] <= '9')) { //если символ является числом
				if (pattern[k] == 'D') {
					dat.day *= 10;
					dat.day += (strok[i]-'0');
					k++;
				}
				else if (pattern[k] == 'M') {
					dat.mon *= 10;
					dat.mon += (strok[i]-'0'); 
					k++;
				}
				else if (pattern[k] == 'Y') {
					dat.year *= 10;
					dat.year += (strok[i]-'0');
					k++;
				}
				else {
					dat.reset();
					k = 0;
				}
			}
			else if ((pattern[k] < 'A') || (pattern[k] > 'Z')) { //защита от букв таких же как в шаблоне
				if(pattern[k] != strok[i]) {
					dat.reset();
					k = 0;
				}
				else {
					k++;
				}
			}
			else if (k) { //чтобы постоянно не занулять
					dat.reset();
					k=0;
			}
			i++;
		}
	}
	return dat;
}
