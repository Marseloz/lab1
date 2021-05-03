#include <ctime>
#include <string>

struct TIME {
	int sec;
	int min;
	int hour;	

	TIME() {
		reset();
	}
	
	void reset() {
		sec = 0;
		min = 0;
		hour = 0;	
	}

	TIME& operator = (const TIME n) {
		sec = n.sec;
		min = n.min;
		hour = n.hour;
		return *this;
	}

	TIME& operator=(tm n) {
		sec = n.tm_sec;
		min = n.tm_min;
		hour = n.tm_hour;
		return *this;
	}
};
struct DATE {
	int day;
	int mon;
	int year;

	DATE() {
		reset();
	}

	void reset() {
		day = 0;
		mon = 0;
		year = 0;
	}

	DATE& operator = (const DATE& n) {
		day = n.day;
		mon = n.mon;
		year = n.year;
		return *this;
	}
	DATE& operator = (tm n) {
		day = n.tm_mday;
		mon = 1 + n.tm_mon;
		year = 1900 + n.tm_year;
		return *this;
	}
};

class TM {
	private:
		TIME t;
		DATE d;
	public:
		TM(); // конструкторы по умолчанию, копирования, с параметрами и перемещения
		TM(int sec, int min, int hour, int day, int mon, int data); // конструктор с параметрами
		TM(const TM &a);//конструктор копирования
		TM(TM&& a);//перемещения

		TIME get_t(); //геттер
		DATE get_d(); //геттер
		void set_t(TIME a); //сеттер
		void set_d(DATE a); //сеттер

		DATE date(); //метод date() возвращает дату в виде структуры
		TIME time(); //метод time() возвращает время в виде структуры

		void Print(std::string); //метод печати по заданному шаблону

		void the_time(); //метод текущего времени
		void the_date(); //метод текущей даты

		static bool CorrectDate(int, int, int); //статический метод проверки набора чисел на корректность дате
		static bool CorrectTime(int, int, int); //статический метод проверки набора чисел на корректность времени

		std::string DateFromString(std::string pattern = "DD:MM:YYYY");  //метод перевода даты в строку по заданному формату. Проверить метод на примерах печати в файл и в консоль

			
		
		static DATE dat_date(std::string, std::string pattern = "DD:MM:YYYY"); //статический метод получения даты из строки, метод должен получать 2 параметра строку с датой и строку формата
};

inline TIME TM::get_t() {
	return t;
}
inline DATE TM::get_d() {
	return d;
}
inline void TM::set_t(TIME a) {
	if (CorrectTime(a.sec, a.min, a.hour)) {
		this->t = a;
	}
	else {
		a.reset();
	}
}
inline void TM::set_d(DATE a) {
	if (CorrectDate(a.day, a.mon, a.year)) {
		this->d = a;
	}
	else {
		a.reset();
	}
}
