// main.cpp
#include "attendance.h"
#include <iostream>
#include <fstream>

static const int MAX_ATTEN_DAYS = 500;

int main() {
	Attendance stAttendance;
	ifstream fin{ "attendance_weekday_500.txt" };
	AttendanceDatas attndanceData;

	for (int day = 0; day < MAX_ATTEN_DAYS; day++) {
		fin >> attndanceData.name >> attndanceData.day;
		stAttendance.UpdateAttendance(attndanceData);
	}
	stAttendance.ManageAttendance();
	return 0;
}