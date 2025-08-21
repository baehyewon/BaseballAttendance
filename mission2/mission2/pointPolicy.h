#pragma once
#include <string>
using namespace std;

static const int NUM_DAYS_OF_WEEK = 7;

static const int BONUS_THRESHOLD = 10;
static const int SPECIAL_BONUS_POINTS = 10;
static const int NO_SPECIAL_BONUS_POINTS = 0;

static const int WENDSDAY_POINTS = 3;
static const int WEEKENDS_POINTS = 2;
static const int DEFAULT_POINTS = 1;

static const string MONDAY = "monday";
static const string TUESDAY = "tuesday";
static const string WEDNESDAY = "wednesday";
static const string THURSDAY = "thursday";
static const string FRIDAY = "friday";
static const string SATURDAY = "saturday";
static const string SUNDAY = "sunday";

enum DayIndexs {
	MONDAY_INDEX = 0,
	TUESDAY_INDEX,
	WENDSDAY_INDEX,
	THURSDAY_INDEX,
	FIRDAY_INDEX,
	SATURDAY_INDEX,
	SUNDAY_INDEX
};

class IPointStrategy {
public:
	virtual ~IPointStrategy() = default;
	virtual int GetPoints(const std::string& dayOfWeek) const = 0;
	virtual int GetSpecialPoints(int(*attendance)[NUM_DAYS_OF_WEEK], int memberIndex) const = 0;
};

class DefaultPointStrategy : public IPointStrategy {
public:
	int GetPoints(const std::string& dayOfWeek) const override {
		if (dayOfWeek == WEDNESDAY) return WENDSDAY_POINTS;
		else if (dayOfWeek == SATURDAY || dayOfWeek == SUNDAY) return WEEKENDS_POINTS;
		
		return DEFAULT_POINTS;
	}
	int GetSpecialPoints(int(*attendance)[NUM_DAYS_OF_WEEK], int memberIndex) const override {
		int specialBonusPoints = 0;

		if (attendance[memberIndex][WENDSDAY_INDEX] >= BONUS_THRESHOLD) {
			specialBonusPoints += SPECIAL_BONUS_POINTS;
		}

		if (attendance[memberIndex][SATURDAY_INDEX] + attendance[memberIndex][SUNDAY_INDEX] >= BONUS_THRESHOLD) {
			specialBonusPoints += SPECIAL_BONUS_POINTS;
		}
		return specialBonusPoints;
	}
};