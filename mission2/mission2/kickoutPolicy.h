#pragma once
#include <string>
using namespace std;

class IKickOutStrategy {
public:
	virtual ~IKickOutStrategy() = default;
	virtual bool IsKickoutMember(int grade, int numOfWednesday, int numOfWeekend) const = 0;
};

class DefaultKickOutStrategy : public IKickOutStrategy {
public:
	bool IsKickoutMember(int grade, int numOfWednesday, int numOfWeekend) const override {
		if (grade == 0 && numOfWednesday == 0 && numOfWeekend) return true;
		return false;
	}
};