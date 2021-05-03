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
		TM(); // ������������ �� ���������, �����������, � ����������� � �����������
		TM(int sec, int min, int hour, int day, int mon, int data); // ����������� � �����������
		TM(const TM &a);//����������� �����������
		TM(TM&& a);//�����������

		TIME get_t(); //������
		DATE get_d(); //������
		void set_t(TIME a); //������
		void set_d(DATE a); //������

		DATE date(); //����� date() ���������� ���� � ���� ���������
		TIME time(); //����� time() ���������� ����� � ���� ���������

		void Print(std::string); //����� ������ �� ��������� �������

		void the_time(); //����� �������� �������
		void the_date(); //����� ������� ����

		static bool CorrectDate(int, int, int); //����������� ����� �������� ������ ����� �� ������������ ����
		static bool CorrectTime(int, int, int); //����������� ����� �������� ������ ����� �� ������������ �������

		std::string DateFromString(std::string pattern = "DD:MM:YYYY");  //����� �������� ���� � ������ �� ��������� �������. ��������� ����� �� �������� ������ � ���� � � �������

			
		
		static DATE dat_date(std::string, std::string pattern = "DD:MM:YYYY"); //����������� ����� ��������� ���� �� ������, ����� ������ �������� 2 ��������� ������ � ����� � ������ �������
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

