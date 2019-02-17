# pool-analytics
Cash flow/analytics engine specifically for CMBS Agency pools, with ability to generate assumption-dependent cash flows and calculate price, yield, duration, and other risk measures (main purpose of this was as a C++ refresher)

### To-Do List:

- Prepayment strings and basic fixed-penalty and yield maintenance
- Default, lag, and severities
- Use real first payment and maturity dates and derive loan age instead of an input
- Properly payment date rolling logic
- CSV output options
- Acquire factor data and loan terms directly from FNMA web site
- Other speeds (CPJ, CPB)
- Support ARM loans
- Support true user inputs and scenario specification
- Add regression tests
- Proper WAL calc which supports each accrual basis, settlement dates

