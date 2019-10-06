#include "catch.hpp"
#include "utilities.h"

using namespace Utilities::DateTime;

TEST_CASE("Check date difference in months matches expected value")
{
    auto date1 = createTime(2019, 1, 1);
    auto date2 = createTime(2019, 9, 1);
    auto date3 = createTime(2020, 3, 1);

    REQUIRE(monthsBetween(date1, date1) == 0);
    REQUIRE(monthsBetween(date1, date2) == 8);
    REQUIRE(monthsBetween(date1, date3) == 14);
    REQUIRE(monthsBetween(date2, date3) == 6);
    REQUIRE(monthsBetween(date2, date1) == -8);
    REQUIRE(monthsBetween(date3, date1) == -14);
    REQUIRE(monthsBetween(date3, date2) == -6);
}

TEST_CASE("Check date difference in days matches expected value")
{
    auto date1 = createTime(2019, 1, 1);
    auto date2 = createTime(2019, 3, 1);
    auto date3 = createTime(2031, 6, 1);

    REQUIRE(daysBetween(date1, date1, false) == 0);
    REQUIRE(daysBetween(date1, date2, false) == 59);
    REQUIRE(daysBetween(date1, date2, true) == 60);
    REQUIRE(daysBetween(date1, date3, false) == 4534);
}