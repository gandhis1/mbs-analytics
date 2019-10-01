#include "catch.hpp"
#include "prepayment_provision.h"

TEST_CASE("Prepayment provision object construction is reversible") {
    REQUIRE( summarizePrepaymentProvisions(parsePrepaymentString("YM(114) O(6)")) == "YM(114) O(6)");
    REQUIRE( summarizePrepaymentProvisions(parsePrepaymentString("L(24) YM(72) 1(18) O(6)")) == "L(24) YM(72) 1(18) O(6)");
    REQUIRE( summarizePrepaymentProvisions(parsePrepaymentString("L(6) D(108) O(6)")) == "L(6) D(108) O(6)");
    REQUIRE( summarizePrepaymentProvisions(parsePrepaymentString("10(24) 9(12) 8(12) 7(12) 6(12) 5(12) O(276)")) == "10(24) 9(12) 8(12) 7(12) 6(12) 5(12) O(276)");
    REQUIRE( summarizePrepaymentProvisions(parsePrepaymentString("5(36) 4(12) 3(12) 2(12) 1(12)")) == "5(36) 4(12) 3(12) 2(12) 1(12)");
}
