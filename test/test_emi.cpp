#include <iostream>
#include <cassert>
#include "../src/Loan.h"

// simple long-double abs (macOS doesn't provide fabsl)
long double ld_abs(long double x) {
    return x < 0 ? -x : x;
}

int main() {
    // Test: principal = 1200, rate = 12% annual, tenure = 12 months
    Loan loan(1200.0L, 12.0L, 12);

    long double emi = loan.monthlyEMI();

    // expected EMI ≈ 106.62
    long double expected = 106.62L;

    // compare with small tolerance
    assert(ld_abs(emi - expected) < 1e-2L);

    std::cout << "Test passed.\n";
    return 0;
}

