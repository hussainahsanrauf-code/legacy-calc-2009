#include <iostream>
#include <cassert>
#include "../src/Loan.h"

int main() {
    // zero interest test
    {
        Loan L(1200.0L, 0.0L, 12);
        long double emi = L.monthlyEMI();
        assert(fabsl(emi - 100.0L) < 1e-12L);
        std::cout << "Zero-interest test passed\n";
    }
    // sanity test (prints value)
    {
        Loan L(100000.0L, 12.0L, 360);
        long double emi = L.monthlyEMI();
        std::cout << "EMI for 100000 @12% over 360 months: " << emi << "\n";
    }
    return 0;
}
