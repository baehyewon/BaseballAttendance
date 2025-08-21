#include "gmock/gmock.h"
#include "attendance.h"

using namespace testing;

static const string MEMBER_NAME_UMAR = "Umar";
static const string MEMBER_NAME_DAISY = "Daisy";

static const string TUES_DAY = "tuesday";
static const string THURS_DAY = "thursday";
static const string FRI_DAY = "friday";
static const string SUN_DAY = "sunday";

static const string NORMAL_DAY = "monday";
static const string WEDNES_DAY = "wednesday";
static const string WEEKEND_DAY = "saturday";
static const string INVALID_DAY = "holiday";



class AttendanceFixture : public ::testing::Test {
protected:
    Attendance stAttendance;
    AttendanceDatas attendanceData;

    void SetUp() override {
        attendanceData = AttendanceDatas();
        attendanceData.name = MEMBER_NAME_UMAR;
        attendanceData.day = NORMAL_DAY;
	}

    void SetAttendanceData(const std::string& name, const std::string& day) {
        attendanceData.name = name;
        attendanceData.day = day;
	}
};

TEST_F(AttendanceFixture, RegisterAndGetIDTest) {
    stAttendance.UpdateAttendance(attendanceData);
    int id1 = stAttendance.GetMemberID(MEMBER_NAME_UMAR);

    SetAttendanceData(MEMBER_NAME_UMAR, WEDNES_DAY);
    stAttendance.UpdateAttendance(attendanceData);
    int id2 = stAttendance.GetMemberID(MEMBER_NAME_UMAR);

    SetAttendanceData(MEMBER_NAME_DAISY, WEDNES_DAY);
    stAttendance.UpdateAttendance(attendanceData);
    int id3 = stAttendance.GetMemberID(MEMBER_NAME_DAISY);

    EXPECT_EQ(id1, id2);
    EXPECT_NE(id1, id3);
}

TEST_F(AttendanceFixture, ValidDayTest) {
    EXPECT_EQ(stAttendance.GetDayIndex(NORMAL_DAY), MONDAY_INDEX);
    EXPECT_EQ(stAttendance.GetDayIndex(TUES_DAY), TUESDAY_INDEX);
    EXPECT_EQ(stAttendance.GetDayIndex(WEDNES_DAY), WENDSDAY_INDEX);
    EXPECT_EQ(stAttendance.GetDayIndex(THURS_DAY), THURSDAY_INDEX);
    EXPECT_EQ(stAttendance.GetDayIndex(FRI_DAY), FIRDAY_INDEX);
    EXPECT_EQ(stAttendance.GetDayIndex(WEEKEND_DAY), SATURDAY_INDEX);
    EXPECT_EQ(stAttendance.GetDayIndex(SUN_DAY), SUNDAY_INDEX);
    EXPECT_THROW(stAttendance.GetDayIndex(INVALID_DAY), std::invalid_argument);
}

TEST_F(AttendanceFixture, AddPoint_Moday) {
    SetAttendanceData(MEMBER_NAME_UMAR, NORMAL_DAY);
    stAttendance.UpdateAttendance(attendanceData);
    int id = stAttendance.GetMemberID(MEMBER_NAME_UMAR);

    EXPECT_EQ(stAttendance.GetPointsOfMember(id), 1);
    EXPECT_EQ(stAttendance.GetWendsdayOfMember(id), 0);
    EXPECT_EQ(stAttendance.GetWeekendOfMember(id), 0);
}

TEST_F(AttendanceFixture, AddPoint_Tuesday) {
    SetAttendanceData(MEMBER_NAME_UMAR, TUES_DAY);
    stAttendance.UpdateAttendance(attendanceData);
    int id = stAttendance.GetMemberID(MEMBER_NAME_UMAR);

    EXPECT_EQ(stAttendance.GetPointsOfMember(id), 1);
    EXPECT_EQ(stAttendance.GetWendsdayOfMember(id), 0);
    EXPECT_EQ(stAttendance.GetWeekendOfMember(id), 0);
}


TEST_F(AttendanceFixture, AddPoint_Thursday) {
    SetAttendanceData(MEMBER_NAME_UMAR, THURS_DAY);
    stAttendance.UpdateAttendance(attendanceData);
    int id = stAttendance.GetMemberID(MEMBER_NAME_UMAR);

    EXPECT_EQ(stAttendance.GetPointsOfMember(id), 1);
    EXPECT_EQ(stAttendance.GetWendsdayOfMember(id), 0);
    EXPECT_EQ(stAttendance.GetWeekendOfMember(id), 0);
}

TEST_F(AttendanceFixture, AddPoint_Friday) {
    attendanceData.name = MEMBER_NAME_UMAR;
    attendanceData.day = "thursday";

    SetAttendanceData(MEMBER_NAME_UMAR, THURS_DAY);
    stAttendance.UpdateAttendance(attendanceData);
    int id = stAttendance.GetMemberID(MEMBER_NAME_UMAR);

    EXPECT_EQ(stAttendance.GetPointsOfMember(id), 1);
    EXPECT_EQ(stAttendance.GetWendsdayOfMember(id), 0);
    EXPECT_EQ(stAttendance.GetWeekendOfMember(id), 0);
}

TEST_F(AttendanceFixture, AddPoint_Wednesday) {
    SetAttendanceData(MEMBER_NAME_UMAR, WEDNES_DAY);
    stAttendance.UpdateAttendance(attendanceData);
    int id = stAttendance.GetMemberID(MEMBER_NAME_UMAR);

    EXPECT_EQ(stAttendance.GetPointsOfMember(id), 3);
    EXPECT_EQ(stAttendance.GetWendsdayOfMember(id), 1);
    EXPECT_EQ(stAttendance.GetWeekendOfMember(id), 0);
}

TEST_F(AttendanceFixture, AddPoint_Saturday) {
    SetAttendanceData(MEMBER_NAME_UMAR, WEEKEND_DAY);
    stAttendance.UpdateAttendance(attendanceData);
    int id = stAttendance.GetMemberID(MEMBER_NAME_UMAR);

    EXPECT_EQ(stAttendance.GetPointsOfMember(id), 2);
    EXPECT_EQ(stAttendance.GetWendsdayOfMember(id), 0);
    EXPECT_EQ(stAttendance.GetWeekendOfMember(id), 1);
}

TEST_F(AttendanceFixture, AddPoint_Sunday) {
    SetAttendanceData(MEMBER_NAME_UMAR, SUN_DAY);
    stAttendance.UpdateAttendance(attendanceData);
    int id = stAttendance.GetMemberID(MEMBER_NAME_UMAR);

    EXPECT_EQ(stAttendance.GetPointsOfMember(id), 2);
    EXPECT_EQ(stAttendance.GetWendsdayOfMember(id), 0);
    EXPECT_EQ(stAttendance.GetWeekendOfMember(id), 1);
}

TEST_F(AttendanceFixture, SpecialPoint_Wednesday) {
    SetAttendanceData(MEMBER_NAME_UMAR, WEDNES_DAY);
    for(int day = 1; day <= 10; day++) {
        stAttendance.UpdateAttendance(attendanceData);
	}
    stAttendance.ManageAttendance();
    int id = stAttendance.GetMemberID(MEMBER_NAME_UMAR);

    EXPECT_EQ(stAttendance.GetPointsOfMember(id), 40);
    EXPECT_EQ(stAttendance.GetWendsdayOfMember(id), 10);
    EXPECT_EQ(stAttendance.GetWeekendOfMember(id), 0);
}

TEST_F(AttendanceFixture, SpecialPoint_Weekend) {
    SetAttendanceData(MEMBER_NAME_UMAR, WEEKEND_DAY);
    for (int day = 1; day <= 10; day++) {
        stAttendance.UpdateAttendance(attendanceData);
    }
    stAttendance.ManageAttendance();

    int id = stAttendance.GetMemberID(MEMBER_NAME_UMAR);

    EXPECT_EQ(stAttendance.GetPointsOfMember(id), 30);
    EXPECT_EQ(stAttendance.GetWendsdayOfMember(id), 0);
    EXPECT_EQ(stAttendance.GetWeekendOfMember(id), 10);
}

TEST_F(AttendanceFixture, SpecialPoint_MixWednesdayAndWeekend) {
    SetAttendanceData(MEMBER_NAME_UMAR, WEEKEND_DAY);
    for (int day = 1; day <= 10; day++) {
        stAttendance.UpdateAttendance(attendanceData);
    }

    SetAttendanceData(MEMBER_NAME_UMAR, WEDNES_DAY);
    for (int day = 1; day <= 10; day++) {
        stAttendance.UpdateAttendance(attendanceData);
    }

    stAttendance.ManageAttendance();
    int id = stAttendance.GetMemberID(MEMBER_NAME_UMAR);

    EXPECT_EQ(stAttendance.GetPointsOfMember(id), 70);
    EXPECT_EQ(stAttendance.GetWendsdayOfMember(id), 10);
    EXPECT_EQ(stAttendance.GetWeekendOfMember(id), 10);
}

TEST_F(AttendanceFixture, SpecialPoint_NormalGrade) {
    SetAttendanceData(MEMBER_NAME_UMAR, NORMAL_DAY);
    for (int day = 1; day <= 10; day++) {
        stAttendance.UpdateAttendance(attendanceData);
    }
    stAttendance.ManageAttendance();

    int id = stAttendance.GetMemberID(MEMBER_NAME_UMAR);

    EXPECT_EQ(stAttendance.GetGradeOfMember(id), 0);
}

TEST_F(AttendanceFixture, SpecialPoint_SilverGrade) {
    SetAttendanceData(MEMBER_NAME_UMAR, WEEKEND_DAY);
    for (int day = 1; day <= 10; day++) {
        stAttendance.UpdateAttendance(attendanceData);
    }
    stAttendance.ManageAttendance();

    int id = stAttendance.GetMemberID(MEMBER_NAME_UMAR);

    EXPECT_EQ(stAttendance.GetGradeOfMember(id), 2);
}

TEST_F(AttendanceFixture, SpecialPoint_GoldGrade) {
    SetAttendanceData(MEMBER_NAME_UMAR, WEEKEND_DAY);
    for (int day = 1; day <= 20; day++) {
        stAttendance.UpdateAttendance(attendanceData);
    }
    stAttendance.ManageAttendance();

    int id = stAttendance.GetMemberID(MEMBER_NAME_UMAR);

    EXPECT_EQ(stAttendance.GetGradeOfMember(id),1);
}
