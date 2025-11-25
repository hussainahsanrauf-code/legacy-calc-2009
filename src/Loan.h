#pragma once
#include <vector>

class Loan {
public:
    Loan(long double principal, long double annualRatePercent, unsigned long tenureMonths);

    long double monthlyEMI() const;
    long double totalPayment() const;
    long double totalInterest() const;

    // amortization balances (remaining balance after each payment)
    std::vector<long double> amortizationSchedule() const;

private:
    long double principal_;
    long double annualRatePercent_;
    unsigned long tenureMonths_;
};
