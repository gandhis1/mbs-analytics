# mbs-analytics
Generate scenario/assumption-dependent cash flows and calculate price, yield, WAL, and other risk measures on MBS.

#### Technology:

Code is developed using standard C++ and STL libraries, with a Windows-focused Makefile. The front-end CLI is developed in C# on .NET Core 2.2. All code should be largely cross-platform; however, explicit references to Windows-specific attributes (e.g. use of DLL extension) still need to be factored out and eliminated.

#### Quick Start:

- Clone and/or fork the repository, `cd` to the project root
- `make` to build the C++ library
- `cd ./src/frontend`
- `dotnet run`

#### To-Do List:

This is a work-in-progress, and many things have yet to be implemented. Basic amortization functionality has been implemented, but major work remaining includes a proper interface for parameterizing scenarios and loans, and full support of all market-standard cash flow functionality. Additionally, interfacing with freely available data portals (such as GSE web sites) is planned for the future.


- Create C# wrapper for DLL library + marshal a struct type storing cashflows returned from C++ layer
- Calculate periodic + cumulative VPRs/CDRs during projection
- Delinquency and advancing
    - Calculate non-performing fraction (perhaps overlap with defaulted fraction)
    - Do not advance on non-performing balance
    - Calculate optimal (100% advancing) interest
- Distribute all recoveryPrincipal and realize all losses at maturity depending on extendLagsPastMaturity
- Yield curve (CMT tenors + spot/par rates) for YM calculations
  - Basic yield maintenance calculations for FNMA YM type
  - Basic yield maintenance calculations for standard CMBS present value method
- Acquire factor data and loan terms directly from GSE web sites
- Use real first payment and maturity dates and derive loan age instead of an input
- Proper payment date calculation logic
- CSV output options
- Other speeds (CPJ, CPB, CPY, CPP)
- Support forward rates, resets and recasts, and other features of ARM loans
- Support true user inputs and scenario specification
- Add regression tests
- Proper WAL calc which supports each accrual basis, settlement dates
- Calculation of all risk measures, including price-to-yield and back and duration
