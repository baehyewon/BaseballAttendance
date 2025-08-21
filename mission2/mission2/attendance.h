//attendance.h
#pragma once
#include <string>
#include <vector>
#include <map>
#include "gradePolicy.h"
#include "pointPolicy.h"
#include "kickoutPolicy.h"
using namespace std;

struct AttendanceDatas {
	string name;
	string day;
};

class Attendance {
public:
	Attendance(IGradeStrategy* gradeStrategy = new DefaultGradeStrategy(),
		IPointStrategy* pointStrategy = new DefaultPointStrategy(),
		IKickOutStrategy* kickOutStrategy = new DefaultKickOutStrategy())
		: gradeStrategy(gradeStrategy), pointStrategy(pointStrategy), kickOutStrategy(kickOutStrategy) {
	}
	void ManageAttendance(void);

	void UpdateAttendance(const AttendanceDatas& attndanceData);
	int GetMemberID(const std::string& name);
	int GetDayIndex(const std::string& dayOfWeek);

	int GetPointsOfMember(int memberId);
	int GetWendsdayOfMember(int memberId);
	int GetWeekendOfMember(int memberId);
	int GetGradeOfMember(int memberId);

protected:
	int RegisterAndGetID(const std::string& name);
	void AddPoints(const std::string& dayOfWeek, int memberId);
	void AddSpecialPoints();
	void UpdateGrades();
	void PrintMembersInformation();
	void PrintKickOutMembers();
private:
	static const int MAX_MEMBERS = 100;

	IGradeStrategy* gradeStrategy;
	IPointStrategy* pointStrategy;
	IKickOutStrategy* kickOutStrategy;
	map<string, int> memberID;
	int numOfMembers = 0;

	int attendance[MAX_MEMBERS][NUM_DAYS_OF_WEEK]{};
	int points[MAX_MEMBERS]{};
	int grade[MAX_MEMBERS]{};
	string names[MAX_MEMBERS]{};

	int wednesday[MAX_MEMBERS]{};
	int weekend[MAX_MEMBERS]{};
};

