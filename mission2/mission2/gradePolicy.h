#pragma once
#include <string>
using namespace std;

static const int GOLD_THRESHOLD = 50;
static const int SILVER_THRESHOLD = 30;
static const int GRADE_INDEX_GOLD = 1;
static const int GRADE_INDEX_SILVER = 2;
static const int GRADE_INDEX_NORMAL = 0;

static const string GRADE_STRING_GOLD = "GOLD";
static const string GRADE_STRING_SILVER = "SILVER";
static const string GRADE_STRING_NORMAL = "NORMAL";

class IGradeStrategy {
public:
	virtual ~IGradeStrategy() = default;
	virtual int GetGrade(int points) const = 0;
	virtual string GetGradeString(int grade) const = 0;
};

class DefaultGradeStrategy : public IGradeStrategy {
public:
	int GetGrade(int points) const override {
		if (points >= GOLD_THRESHOLD) return GRADE_INDEX_GOLD;
		else if (points >= SILVER_THRESHOLD) return GRADE_INDEX_SILVER;

		return GRADE_INDEX_NORMAL;
	}
	string GetGradeString(int grade) const override {
		if (grade == GRADE_INDEX_GOLD) return GRADE_STRING_GOLD;
		else if (grade == GRADE_INDEX_SILVER) return GRADE_STRING_SILVER;

		return GRADE_STRING_NORMAL;
	}
};