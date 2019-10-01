#include "catch.hpp"
#include "prepayment_provision.h"

TEST_CASE("Prepayment provision object construction is reversible")
{
    REQUIRE(summarizePrepaymentProvisions(parsePrepaymentString("YM(114) O(6)")) == "YM(114) O(6)");
    REQUIRE(summarizePrepaymentProvisions(parsePrepaymentString("L(24) YM(72) 1(18) O(6)")) == "L(24) YM(72) 1(18) O(6)");
    REQUIRE(summarizePrepaymentProvisions(parsePrepaymentString("L(6) D(108) O(6)")) == "L(6) D(108) O(6)");
    REQUIRE(summarizePrepaymentProvisions(parsePrepaymentString("10(24) 9(12) 8(12) 7(12) 6(12) 5(12) O(276)")) == "10(24) 9(12) 8(12) 7(12) 6(12) 5(12) O(276)");
    REQUIRE(summarizePrepaymentProvisions(parsePrepaymentString("5(36) 4(12) 3(12) 2(12) 1(12)")) == "5(36) 4(12) 3(12) 2(12) 1(12)");
}

TEST_CASE("Prepayment provision construction matches expected behavior")
{
    auto prepaymentProvisions = parsePrepaymentString("L(24) D(30) YM(42) 1(18) O(6)");

    REQUIRE(prepaymentProvisions.size() == 5);

    REQUIRE(prepaymentProvisions[0]->getType() == PrepaymentProvisionType::LOCKOUT);
    REQUIRE(prepaymentProvisions[0]->getLength() == 24);

    REQUIRE(prepaymentProvisions[1]->getType() == PrepaymentProvisionType::DEFEASANCE);
    REQUIRE(prepaymentProvisions[1]->getLength() == 30);

    REQUIRE(prepaymentProvisions[2]->getType() == PrepaymentProvisionType::YIELD_MAINTENANCE);
    REQUIRE(prepaymentProvisions[2]->getLength() == 42);

    REQUIRE(prepaymentProvisions[3]->getType() == PrepaymentProvisionType::FIXED_PENALTY);
    REQUIRE(prepaymentProvisions[3]->getLength() == 18);

    REQUIRE(prepaymentProvisions[4]->getType() == PrepaymentProvisionType::OPEN);
    REQUIRE(prepaymentProvisions[4]->getLength() == 6);
}
