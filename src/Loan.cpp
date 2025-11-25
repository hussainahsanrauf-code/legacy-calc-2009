#include "Loan.h"
#include <cmath>
#include <stdexcept>

Loan::Loan(long double principal, long double annualRatePercent, unsigned long tenureMonths)
    : principal_(principal), annualRatePercent_(annualRatePercent), tenureMonths_(tenureMonths)
{
    if (principal_ <= 0.0L) throw std::invalid_argument("principal must be > 0");
    if (annualRatePercent_ < 0.0L) throw std::invalid_argument("rate must be >= 0");
    if (tenureMonths_ == 0) throw std::invalid_argument("tenure must be >= 1");
}

long double Loan::monthlyEMI() const {
    long double P = principal_;
    long double r = annualRatePercent_ / 100.0L / 12.0L; // monthly rate
    unsigned long n = tenureMonths_;

    if (r == 0.0L) {
        return P / static_cast<long double>(n);
    }

    long double onepr = 1.0L + r;
    // use powl for long double precision
    long double num = powl(onepr, static_cast<long double>(n));
    long double denom = num - 1.0L;
    if (fabsl(denom) < 1e-18L) {
        // numeric guard: if denom is almost zero, fallback to P/n
        return P / static_cast<long double>(n);
    }
    long double emi = P * r * num / denom;
    return emi;
}

long double Loan::totalPayment() const {
    return monthlyEMI() * static_cast<long double>(tenureMonths_);
}

long double Loan::totalInterest() const {
    return totalPayment() - principal_;
}

std::vector<long double> Loan::amortizationSchedule() const {
    std::vector<long double> balances;
    balances.reserve(tenureMonths_);

    long double emi = monthlyEMI();
    long double balance = principal_;
    long double r = annualRatePercent_ / 100.0L / 12.0L;

    for (unsigned long month = 1; month <= tenureMonths_; ++month) {
        long double interest = balance * r;
        long double principalPaid = emi - interest;
        if (principalPaid < 0.0L) principalPaid = 0.0L; // safety
        balance -= principalPaid;
        if (balance < 0.0L) balance = 0.0L;
        balances.push_back(balance);
    }
    return balances;
}
