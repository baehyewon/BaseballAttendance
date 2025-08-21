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
int Attendance::GetMemberID(const std::string& name)
{
	return memberID[name];
}

int Attendance::GetDayIndex(const std::string& dayOfWeek)
{
	if (dayOfWeek == MONDAY) return MONDAY_INDEX;
	else if (dayOfWeek == TUESDAY) return TUESDAY_INDEX;
	else if (dayOfWeek == WEDNESDAY) return WENDSDAY_INDEX;
	else if (dayOfWeek == THURSDAY) return THURSDAY_INDEX;
	else if (dayOfWeek == FRIDAY) return FIRDAY_INDEX;
	else if (dayOfWeek == SATURDAY) return SATURDAY_INDEX;
	else if (dayOfWeek == SUNDAY) return SUNDAY_INDEX;

	throw std::invalid_argument("Invalid day of week: " + dayOfWeek);
}
void Attendance::AddPoints(const std::string& dayOfWeek, int memberId)
{
	points[memberId] += pointStrategy->GetPoints(dayOfWeek);

	if (dayOfWeek == WEDNESDAY) wednesday[memberId]++;
	else if (dayOfWeek == SATURDAY) weekend[memberId]++;
	else if (dayOfWeek == SUNDAY) weekend[memberId]++;
}

void Attendance::AddSpecialPoints()
{
	for (int memberIndex = 1; memberIndex <= numOfMembers; memberIndex++) {
		points[memberIndex] += pointStrategy->GetSpecialPoints(attendance, memberIndex);
	}
}

void Attendance::UpdateGrades()
{
	for (int memberIndex = 1; memberIndex <= numOfMembers; memberIndex++) {
		grade[memberIndex] = gradeStrategy->GetGrade(points[memberIndex]);
	}
}

void Attendance::PrintMembersInformation()
{
	string gradeStr;
	for (int memberIndex = 1; memberIndex <= numOfMembers; memberIndex++) {
		gradeStr = gradeStrategy->GetGradeString(grade[memberIndex]);

		cout << "NAME : " << names[memberIndex] << ", ";
		cout << "POINT : " << points[memberIndex] << ", ";
		cout << "GRADE : " << gradeStr << "\n";
	}
}

void Attendance::PrintKickOutMembers()
{
	std::cout << "\n" << "Removed player\n" << "==============\n";
	for (int memberIndex = 1; memberIndex <= numOfMembers; memberIndex++) {
		if (kickOutStrategy->IsKickoutMember(grade[memberIndex], wednesday[memberIndex], weekend[memberIndex])) {
			std::cout << names[memberIndex] << "\n";
		}
	}
}

int Attendance::GetPointsOfMember(int memberId)
{
	return points[memberId];
}
int Attendance::GetWendsdayOfMember(int memberId)
{
	return wednesday[memberId];
}
int Attendance::GetWeekendOfMember(int memberId)
{
	return weekend[memberId];
}
int Attendance::GetGradeOfMember(int memberId)
{
	return grade[memberId];
}