// attendance.cpp
#include <iostream>
#include "attendance.h"
using namespace std;

void Attendance::ManageAttendance() {
	AddSpecialPoints();
	UpdateGrades();

	PrintMembersInformation();
	PrintKickOutMembers();
}

void Attendance::UpdateAttendance(const AttendanceDatas& attndanceData) {
	string name = attndanceData.name;
	string dayOfWeek = attndanceData.day;

	int memberId = RegisterAndGetID(name);

	int	day = GetDayIndex(dayOfWeek);

	attendance[memberId][day] += 1;

	AddPoints(dayOfWeek, memberId);
}
int Attendance::RegisterAndGetID(const std::string& name)
{
	if (memberID.count(name) == 0) {
		memberID.insert({ name, ++numOfMembers });

		names[numOfMembers] = name;
	}
	return GetMemberID(name);
}
int Attendance::GetDayIndex(const std::string& dayOfWeek)
{
	if (dayOfWeek == "monday") return MONDAY_INDEX;
	else if (dayOfWeek == "tuesday") return TUESDAY_INDEX;
	else if (dayOfWeek == "wednesday") return WENDSDAY_INDEX;
	else if (dayOfWeek == "thursday") return THURSDAY_INDEX;
	else if (dayOfWeek == "friday") return FIRDAY_INDEX;
	else if (dayOfWeek == "saturday") return SATURDAY_INDEX;
	else if (dayOfWeek == "sunday") return SUNDAY_INDEX;

	throw std::invalid_argument("Invalid day of week: " + dayOfWeek);
}
void Attendance::AddPoints(const std::string& dayOfWeek, int memberId)
{
	int add_point = 0;

	if (dayOfWeek == "wednesday") {
		add_point += WENDSDAY_POINTS;
		wednesday[memberId]++;
	}
	else if (dayOfWeek == "saturday") {
		add_point += WEEKENDS_POINTS;
		weekend[memberId]++;
	}
	else if (dayOfWeek == "sunday") {
		add_point += WEEKENDS_POINTS;
		weekend[memberId]++;
	}
	else
	{
		add_point++;
	}

	points[memberId] += add_point;
}

void Attendance::AddSpecialPoints()
{
	for (int memberIndex = 1; memberIndex <= numOfMembers; memberIndex++) {
		if (attendance[memberIndex][WENDSDAY_INDEX] >= BONUS_THRESHOLD) {
			points[memberIndex] += SPECIAL_BONUS_POINTS;
		}

		if (attendance[memberIndex][SATURDAY_INDEX] + attendance[memberIndex][SUNDAY_INDEX] >= BONUS_THRESHOLD) {
			points[memberIndex] += SPECIAL_BONUS_POINTS;
		}
	}
}

void Attendance::UpdateGrades()
{
	for (int memberIndex = 1; memberIndex <= numOfMembers; memberIndex++) {
		if (points[memberIndex] >= GOLD_THRESHOLD) {
			grade[memberIndex] = GRADE_INDEX_GOLD;
		}
		else if (points[memberIndex] >= SILVER_THRESHOLD) {
			grade[memberIndex] = GRADE_INDEX_SILVER;
		}
		else {
			grade[memberIndex] = GRADE_INDEX_NORMAL;
		}
	}
}

void Attendance::PrintMembersInformation()
{
	string gradeStr;
	for (int memberIndex = 1; memberIndex <= numOfMembers; memberIndex++) {
		if (grade[memberIndex] == GRADE_INDEX_GOLD) {
			gradeStr = "GOLD";
		}
		else if (grade[memberIndex] == GRADE_INDEX_SILVER) {
			gradeStr = "SILVER";
		}
		else {
			gradeStr = "NORMAL";
		}

		cout << "NAME : " << names[memberIndex] << ", ";
		cout << "POINT : " << points[memberIndex] << ", ";
		cout << "GRADE : " << gradeStr << "\n";
	}
}

void Attendance::PrintKickOutMembers()
{
	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int memberIndex = 1; memberIndex <= numOfMembers; memberIndex++) {

		if (IsKickOutMember(memberIndex)) {
			std::cout << names[memberIndex] << "\n";
		}
	}
}
bool Attendance::IsKickOutMember(int memberIndex)
{
	if (grade[memberIndex] == 0 && wednesday[memberIndex] == 0 && weekend[memberIndex] == 0) {
		return true;
	}
	return false;
}

int Attendance::GetMemberID(const std::string& name)
{
	return memberID[name];
}
