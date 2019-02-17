#include <iostream>
#include <exception>
#include <string>
#include <cstring>
#include "scenario.h"
#include "pool.h"
#include "engine.h"
#include "utilities.h"

int main(int argc, char *argv[])
{
    if (argc == 1 || (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)))
    {
        std::cout
            << "usage: run_analytics [-h] identifier\n"
            << "\n"
            << "positional arguments:\n"
            << "  identifier    Agency CMBS CUSIP or pool ID with \'FN\' or \'GN\' prefix \n"
            << "\n"
            << "optional arguments:\n"
            << "  -h, --help    show this help message and exit\n"
            << "  --vpr         annualized voluntary prepayment rate (defaults to 0)\n"
            << "  --vpr_type    voluntary prepayment rate type (CPR|CPY|CPJ|CPB, defaults to CPR)\n"
            << "  --cdr         annualized involuntary prepayment rate (defaults to 0)\n";
        return -1;
    }

    // Parse the arguments, skipping the first one (binary name)
    std::string identifier;
    double vpr = -1;
    std::string vpr_type;
    double cdr = -1;
    std::string argumentName;
    for (int i = 1; i < argc; ++i)
    {
        std::string argumentValue = argv[i];
        if (argumentName.empty())
        {
            // If last argument then it is the security identifier
            if (i == argc - 1)
            {
                identifier = argv[i];
            }
            else
            {
                argumentName = argumentValue;
            }
        }
        else
        {
            if (argumentName == "--vpr")
            {
                vpr = std::stod(argumentValue);
            }
            else if (argumentName == "--vpr_type")
            {
                vpr_type = argumentValue;
            }
            else if (argumentName == "--cdr")
            {
                cdr = std::stod(argumentValue);
            }
            else
            {
                std::cout << "Invalid argument provided: " << argumentName << std::endl;
                return -1;
            }
            argumentName.clear();
        }
    }

    // Convert the arguments into a Scenario
    Scenario userScenario;
    if (vpr < 0 and cdr < 0)
    {
        // Will default to zero speeds
    }
    else if (vpr > -1 and cdr < 0)
    {
        Scenario userScenario(vpr);
    }
    else if (vpr > -1 and cdr > -1)
    {
        Scenario userScenario(vpr, cdr);
    }
    else if (vpr < 0 and cdr > -1)
    {
        std::cout << "Invalid arguments - CDR cannot be specified without VPR" << std::endl;
        return -2;
    }

    // Override the input scenario for now
    userScenario = Scenario(0.05, 0.01);

    // Initialize the test security
    std::string poolName = "AN3073";
    std::string loanID = "1717469130";
    double originalBalance = 763000.00;
    double cutoffBalance = 737056.10;
    struct tm factorDate = Utilities::createTime(2019, 2, 1);
    int originalLoanTerm = 60;
    int originalAmortTerm = 360;
    int originalIOTerm = 0;
    int currentLoanAge = 27;
    double grossCoupon = 0.0496;
    double feeStrip = 0.0496 - 0.0248;
    std::string originalPrepaymentString = "L(30) 5%(24) 4%(24) 3%(12) 2%(12) 1%(12) O(6)";
    Loan loan(loanID, originalBalance, cutoffBalance, factorDate, originalLoanTerm, originalAmortTerm, originalIOTerm, currentLoanAge, grossCoupon, feeStrip, ACTUAL_360, originalPrepaymentString);
    Pool testPool = Pool(poolName); // For now create a dummy pool
    testPool.addLoan(loan);

    // Create a cash flow engine
    CashFlowEngine cashFlowEngine{};
    auto &&cashFlows = cashFlowEngine.runCashflows(testPool, userScenario);
    cashFlows.prettyPrint(24);  // Only print the first 24 rows
}
