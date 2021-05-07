#include "class.h"
#include <iostream>
#include <ctime>

using namespace std;

//STRUCT TIME
TIME::TIME() {
	reset();
}
void TIME::reset() {
	sec = 0;
	min = 0;
	hour = 0;
}
TIME& TIME::operator= (const TIME n) {
	sec = n.sec;
	min = n.min;
	hour = n.hour;
	return *this;
}
TIME& TIME::operator= (tm n) {
	sec = n.tm_sec;
	min = n.tm_min;
	hour = n.tm_hour;
	return *this;
}

//STRUCT DATE
DATE::DATE() {
	reset();
}
void DATE::reset() {
	day = 0;
	mon = 0;
	year = 0;
}
DATE& DATE::operator = (const DATE& n) {
	day = n.day;
	mon = n.mon;
	year = n.year;
	return *this;
}
DATE& DATE::operator = (tm n) {
	day = n.tm_mday;
	mon = 1 + n.tm_mon;
	year = 1900 + n.tm_year;
	return *this;
}

//CLASS----------------------------------------------------------------
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
TM::TM(TM&& a) {
	this->d = a.d;
	this->t = a.t;
}
DATE TM::date() { //метод date() возвращает дату в виде структуры
	return d;
}
TIME TM::time() { //метод time() возвращает время в виде структуры
	return t;
}
void TM::the_time() { //метод текущего времени
	time_t timer = std::time(&timer);
	struct tm tabl_date;	// создаём структуру содержащая календарную дату и время, разбитую на составляющие
	localtime_s(&tabl_date, &timer); //заполняем tabl_date данными из timer

	t = tabl_date; //заполняем n данными из tabl_date
}
void TM::the_date() {//метод текущей даты
	time_t timer = std::time(&timer);
	struct tm tabl_date;	// создаём структуру содержащая календарную дату и время, разбитую на составляющие
	localtime_s(&tabl_date, &timer); //заполняем tabl_date данными из timer

	d = tabl_date;
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
	cout << DateToString(pattern);
}

string IntToStr(int n) { // добавление нуля перед числом
	if ((n > 9) || (n < 0)) {
		return to_string(n);
	}
	else {
		return "0" + to_string(n);
	}
}

string TM::DateToString(string pattern) {  //метод перевода даты в строку по заданному формату. Проверить метод на примерах печати в файл и в консоль

	int buff = pattern.find("YYYY");
	if (buff != -1) { pattern.replace(buff, 4, IntToStr(d.year)); }

	buff = pattern.find("MM");
	if (buff != -1) { pattern.replace(buff, 2, IntToStr(d.mon)); }

	buff = pattern.find("DD");
	if (buff != -1) { pattern.replace(buff, 2, IntToStr(d.day)); }

	buff = pattern.find("hh");
	if (buff != -1) { pattern.replace(buff, 2, IntToStr(t.hour)); }

	buff = pattern.find("mm");
	if (buff != -1) { pattern.replace(buff, 2, IntToStr(t.min)); }

	buff = pattern.find("ss");
	if (buff != -1) { pattern.replace(buff, 2, IntToStr(t.sec)); }

	return pattern;
}

TM TM::dat_date(string strok, string pattern) {//статический метод получения даты из строки, метод должен получать 2 параметра строку с датой и строку формата
	DATE buff_d;
	TIME buff_t;
	if (strok.size() >= pattern.size()) {
		for (int i = 0, k = 0; (i < (int)strok.size()) && (k < (int)pattern.size()); i++) {
			if ((strok[i] >= '0') && (strok[i] <= '9')) { //если символ является числом
				if (pattern[k] == 'D') {
					buff_d.day *= 10;
					buff_d.day += (strok[i] - '0');
					k++;
				}
				else if (pattern[k] == 'M') {
					buff_d.mon *= 10;
					buff_d.mon += (strok[i] - '0');
					k++;
				}
				else if (pattern[k] == 'Y') {
					buff_d.year *= 10;
					buff_d.year += (strok[i] - '0');
					k++;
				}
				else if (pattern[k] == 'h') {
					buff_t.hour *= 10;
					buff_t.hour += (strok[i] - '0');
					k++;
				}
				else if (pattern[k] == 'm') {
					buff_t.min *= 10;
					buff_t.min += (strok[i] - '0');
					k++;
				}
				else if (pattern[k] == 's') {
					buff_t.sec *= 10;
					buff_t.sec += (strok[i] - '0');
					k++;
				}
				else {
					buff_d.reset();
					buff_t.reset();
					k = 0;
				}
			}
			else if (((pattern[k] < 'a') || (pattern[k] > 'z')) || ((pattern[k] < 'A') || (pattern[k] > 'Z'))) { //защита от букв таких же как в шаблоне
				if (pattern[k] != strok[i]) {
					buff_d.reset();
					buff_t.reset();
					k = 0;
				}
				else {
					k++;
				}
			}
			else if (k) { //чтобы постоянно не занулять
				buff_d.reset();
				buff_t.reset();
				k = 0;
			}
		}
	}

	TM a;
	a.set_d(buff_d);
	a.set_t(buff_t);
	return a;
}
