//attendance.h
#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;

struct AttendanceDatas {
	string name;
	string day;
};

class Attendance {
public:
	void ManageAttendance(void);
	void PrintMembersInformation();
	void PrintKickOutMembers();

private:
	void UpdateAttendance(const AttendanceDatas& attndanceData);
	int RegisterAndGetID(const std::string& name);
	int GetDayIndex(const std::string& dayOfWeek);
	
	void AddPoints(const std::string& dayOfWeek, int memberId);
	void AddSpecialPoints();

	void UpdateGrades();

	bool IsKickOutMember(int memberIndex);

	static const int MAX_ATTEN_DAYS = 500;
	static const int MAX_MEMBERS = 100;

	static const int NUM_DAYS_OF_WEEK = 7;

	static const int MONDAY_INDEX = 0;
	static const int TUESDAY_INDEX = 1;
	static const int WENDSDAY_INDEX = 2;
	static const int THURSDAY_INDEX = 3;
	static const int FIRDAY_INDEX = 4;
	static const int SATURDAY_INDEX = 5;
	static const int SUNDAY_INDEX = 6;

	static const int BONUS_THRESHOLD = 10;
	static const int SPECIAL_BONUS_POINTS = 10;
	static const int WENDSDAY_POINTS = 3;
	static const int WEEKENDS_POINTS = 2;

	static const int GOLD_THRESHOLD = 50;
	static const int SILVER_THRESHOLD = 30;
	static const int GRADE_INDEX_GOLD = 1;
	static const int GRADE_INDEX_SILVER = 2;
	static const int GRADE_INDEX_NORMAL = 0;

	map<string, int> memberID;
	int numOfMembers = 0;

	int attendance[MAX_MEMBERS][NUM_DAYS_OF_WEEK]{};
	int points[MAX_MEMBERS]{};
	int grade[MAX_MEMBERS]{};
	string names[MAX_MEMBERS]{};

	int wednesday[100]{};
	int weekend[100]{};
};

