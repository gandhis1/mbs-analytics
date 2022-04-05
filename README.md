# mbs-analytics

Generate scenario/assumption-dependent cash flows and calculate price, yield, WAL, and other risk measures on MBS.

#### Technology:

Code is developed using standard C++ and STL libraries. The front-end CLI is developed in C# on .NET Core. All code should be largely cross-platform.

#### Quick Start:

- `docker build -t mbs-analytics .`
- `docker run -t mbs-analytics`

#### Testing:

- There are C++ tests using the catch framework.
- TODO: Integrate them into a GitHub actions workflow.

#### Features:

The cash flow engine is designed to support most of the common loan structural features and scenario specification parameters typically used in mortgage credit/prepayment analysis. While the API is extensible and allows customization of virtually any type of mortgage and (eventually) deal structure, the ultimate constraint is data availability, which would require a corresponding ETL layer that can acquire transaction information and loan-level input data.

#### To-Do List:

This is a work-in-progress, and many things have yet to be implemented. Basic amortization functionality has been implemented, but major work remaining includes a proper interface for parameterizing scenarios and loans, and full support of all market-standard cash flow functionality.

- Create C# wrapper for DLL library + marshal a struct type storing cashflows returned from C++ layer
- Add regression test for cash flow generation
- Proper deal structure and cashflow aggregation within a group (multiple loans)
- Calculate periodic + cumulative VPRs/CDRs during projection
- Toggle for whether delinquency affects cash flows
- Delinquency and advancing - confirm correct calculations and check behavior w/r/t lags
- Distribute all recoveryPrincipal and realize all losses at maturity depending on extendLagsPastMaturity
- Yield curve (CMT tenors + spot/par rates) for YM calculations
  - Basic yield maintenance calculations for FNMA YM type
  - Basic yield maintenance calculations for standard CMBS present value method
- Use real first payment and maturity dates and derive loan age instead of an input
- Proper payment date calculation logic
- CSV output options
- Other prepayment speeds (SMM, CPJ, CPB, CPY, CPP)
- Other default speeds (MDR, PLD)
- Separate term and balloon default assumptions (speed, lag, and severity)
- Support forward rates, resets and recasts, and other features of ARM loans
- Support true user inputs and scenario specification
- Proper WAL calc which supports each accrual basis, settlement dates
- Calculation of all risk measures, including price-to-yield and back and duration
