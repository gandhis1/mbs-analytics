# mbs-analytics
Ability to generate scenario/assumption-dependent cash flows and (eventually) calculate price, yield, WAL, duration, and other risk measures on MBS.

#### To-Do List:

This is a work-in-progress, and many things have yet to be implemented. Basic amortization and CPR/CDR assumptions have been implemented, as well as basic prepay penalty calculations.

- Yield curve (CMT tenors + spot/par rates) for YM calculations
  - Basic yield maintenance calculations for FNMA YM type
  - Basic yield maintenance calculations for standard CMBS present value method
- Delinquency and advancing
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
- Delinquency and advancing assumptions
