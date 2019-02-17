# pool-analytics
Ability to generate scenario/assumption-dependent cash flows and (eventually) calculate price, yield, WAL, duration, and other risk measures

### To-Do List:

This is a work-in-progress, and many things have yet to be implemented. As of 2/17/2019 basic amortization and CPR/CDR assumptions have been implemented, as well as basic prepay penalty calculations.

- Prepayment strings and basic fixed-penalty and yield maintenance
- Default, lag, and severities
- Use real first payment and maturity dates and derive loan age instead of an input
- Properly payment date rolling logic
- CSV output options
- Acquire factor data and loan terms directly from GSE web sites
- Other speeds (CPJ, CPB)
- Support ARM loans
- Support true user inputs and scenario specification
- Add regression tests
- Proper WAL calc which supports each accrual basis, settlement dates
- Calculation of all risk measures, including price-to-yield and back and duration
- Delinquency and advancing assumptions
