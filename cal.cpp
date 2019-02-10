#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

using std::cout;
using std::string;

int get_maxday(int month, int year);
int get_day_of_week(const int year, const int month);
void output_date(string month_name, int year, int first_day, int maxday);

int main(int argc, char *argv[])
{
	string month_name[] = { "January","February","March","April","May","June","July",
		"August","September","October","November","December" };

	std::time_t now = time(0);
	tm *date = std::localtime(&now);

	if (argc == 2) {
		string tmp = argv[1];
		int month = 0;
		int year = 1900 + date->tm_year;
		for (auto c : tmp)
			month = month * 10 + c - '0';

		int maxday = get_maxday(month, year);
		
		int first_day = get_day_of_week(year, month);

		output_date(month_name[month - 1], year, first_day, maxday);

	} else if (argc == 3) {
		string tmp_month = argv[1];
		string tmp_year = argv[2];
		int month = 0, year = 0;
		for (auto c : tmp_month)
			month = month * 10 + c - '0';
		for (auto c : tmp_year)
			year = year * 10 + c - '0';

		int maxday = get_maxday(month, year);

		int first_day = get_day_of_week(year, month);

		output_date(month_name[month - 1], year, first_day, maxday);

	} else cout << "Error!!!\n";

	return 0;
}

int get_maxday(int month, int year)
{
	switch (month) {
		case 1:
			return 31;
		case 2:
			if (year % 4 == 0)
				return 29;
			else
				return 28;
		case 3: case 5: case 7: case 8: case 10: case 12:
			return 31;
		default:
			return 30;
	}

}

int get_day_of_week(const int year, const int month)
{	/* 0 = Sunday */
	const int d = 1;
	int y = year - (month < 3);
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	return (y + y / 4 - y / 100 + y / 400 + t[month - 1] + d) % 7;
}

void output_date(string month_name, int year, int first_day, int maxday)
{
	cout << month_name << ' ' << year << '\n';
	cout << "Su Mo Tu We Th Fr Sa" << '\n';
	cout << "--------------------" << '\n';
	cout << std::setw(3 * first_day + 2) << 1;
	++first_day;
	for (int i = 2; i <= maxday; i++) {
		cout << std::setw((first_day == 0) ? 2 : 3) << i;

		if (first_day == 6) {
			cout << '\n';
			first_day = 0;
		} else ++first_day;
	}
	cout << std::endl;
}
