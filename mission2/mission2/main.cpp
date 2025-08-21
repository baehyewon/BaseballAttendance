// main.cpp
#include "gmock/gmock.h"
#include "attendance.h"
#include <iostream>
#include <fstream>

#ifdef _DEBUG
int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#else
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
#endif