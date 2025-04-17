#define CATCH_CONFIG_MAIN
#include "../../../Catch/catch.hpp"
#include "../Date/CDate.h"

TEST_CASE("Default constructor gives 01.01.1970") {
    CDate date;
    REQUIRE(date.IsValid());
    REQUIRE(date.GetDay() == 1);
    REQUIRE(date.GetMonth() == Month::JANUARY);
    REQUIRE(date.GetYear() == 1970);
    REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
}

TEST_CASE("Constructor with day, month, year") {
    CDate date(3, Month::JANUARY, 1970);
    REQUIRE(date.IsValid());
    REQUIRE(date.GetDay() == 3);
    REQUIRE(date.GetMonth() == Month::JANUARY);
    REQUIRE(date.GetYear() == 1970);
}

TEST_CASE("Constructor with timestamp") {
    CDate date(2);
    REQUIRE(date.IsValid());
    REQUIRE(date.GetDay() == 3);
    REQUIRE(date.GetMonth() == Month::JANUARY);
    REQUIRE(date.GetYear() == 1970);
}

TEST_CASE("Leap year 29 Feb") {
    CDate date(29, Month::FEBRUARY, 2000);
    REQUIRE(date.IsValid());
    REQUIRE(date.GetDay() == 29);
    REQUIRE(date.GetMonth() == Month::FEBRUARY);
    REQUIRE(date.GetYear() == 2000);
}

TEST_CASE("Non-leap year 29 Feb is invalid") {
    CDate date(29, Month::FEBRUARY, 2001);
    REQUIRE(!date.IsValid());
}

TEST_CASE("Invalid date constructor") {
    CDate date(99, static_cast<Month>(99), 10983);
    REQUIRE(!date.IsValid());
}

TEST_CASE("Timestamp beyond limit is invalid") {
    CDate date(10000000);
    REQUIRE(!date.IsValid());
}
