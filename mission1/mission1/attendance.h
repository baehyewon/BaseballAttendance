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

enum DayIndexs {
	MONDAY_INDEX = 0,
	TUESDAY_INDEX,
	WENDSDAY_INDEX,
	THURSDAY_INDEX,
	FIRDAY_INDEX,
	SATURDAY_INDEX,
	SUNDAY_INDEX
};

class Attendance {
public:
	void ManageAttendance(void);

	void UpdateAttendance(const AttendanceDatas& attndanceData);
	int GetMemberID(const std::string& name);
	int GetDayIndex(const std::string& dayOfWeek);

	void PrintMembersInformation();
	void PrintKickOutMembers();

	static const int MAX_MEMBERS = 100;
	static const int NUM_DAYS_OF_WEEK = 7;

	static const int BONUS_THRESHOLD = 10;
	static const int SPECIAL_BONUS_POINTS = 10;
	static const int WENDSDAY_POINTS = 3;
	static const int WEEKENDS_POINTS = 2;

	static const int GOLD_THRESHOLD = 50;
	static const int SILVER_THRESHOLD = 30;
	static const int GRADE_INDEX_GOLD = 1;
	static const int GRADE_INDEX_SILVER = 2;
	static const int GRADE_INDEX_NORMAL = 0;

protected:
	int RegisterAndGetID(const std::string& name);
	void AddPoints(const std::string& dayOfWeek, int memberId);
	void AddSpecialPoints();

	void UpdateGrades();

	bool IsKickOutMember(int memberIndex);

private:
	map<string, int> memberID;
	int numOfMembers = 0;

	int attendance[MAX_MEMBERS][NUM_DAYS_OF_WEEK]{};
	int points[MAX_MEMBERS]{};
	int grade[MAX_MEMBERS]{};
	string names[MAX_MEMBERS]{};

	int wednesday[MAX_MEMBERS]{};
	int weekend[MAX_MEMBERS]{};
};

