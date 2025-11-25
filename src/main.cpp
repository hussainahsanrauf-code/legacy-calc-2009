#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

#include "Loan.h"
#include "Utils.h"

using namespace std;

void printHelp() {
    cout << "Usage examples:\n";
    cout << "  ./calc -cp -a 100000 -i 12 -n 360    # calculate payment\n";
    cout << "Options:\n"
         << "  -a <amount>      principal amount\n"
         << "  -i <interest>    annual interest percent\n"
         << "  -n <months>      tenure (months)\n"
         << "  -cp              calculate monthly payment (EMI)\n"
         << "  -h, --help       show help\n";
}

int main(int argc, char* argv[]) {
    auto cfg = Utils::readConfigFile("config.txt");
    long double default_principal = 100000.0L;
    long double default_interest = 12.0L;
    unsigned long default_tenure = 360;

    auto it = cfg.find("default_principal");
    if (it != cfg.end()) {
        auto p = Utils::parseLongDouble(it->second);
        if (p.first) default_principal = p.second;
    }
    it = cfg.find("default_interest");
    if (it != cfg.end()) {
        auto r = Utils::parseLongDouble(it->second);
        if (r.first) default_interest = r.second;
    }
    it = cfg.find("default_tenure_months");
    if (it != cfg.end()) {
        auto n = Utils::parseUnsignedLong(it->second);
        if (n.first) default_tenure = n.second;
    }

    string s_a = Utils::getArgValue(argc, argv, "-a");
    string s_i = Utils::getArgValue(argc, argv, "-i");
    string s_n = Utils::getArgValue(argc, argv, "-n");
    bool wantCP = false;

    for (int i=1;i<argc;++i) {
        string a = argv[i];
        if (a == "-h" || a == "--help" || a == "-help" || a == "-?" ) {
            printHelp();
            return 0;
        }
        if (a == "-cp") wantCP = true;
    }

    long double principal = default_principal;
    if (!s_a.empty()) {
        auto p = Utils::parseLongDouble(s_a);
        if (!p.first || p.second <= 0.0L) {
            cerr << "Error: invalid principal amount\n";
            return EXIT_FAILURE;
        }
        principal = p.second;
    }

    long double rate = default_interest;
    if (!s_i.empty()) {
        auto r = Utils::parseLongDouble(s_i);
        if (!r.first || r.second < 0.0L) {
            cerr << "Error: invalid interest rate\n";
            return EXIT_FAILURE;
        }
        rate = r.second;
    }

    unsigned long tenure = default_tenure;
    if (!s_n.empty()) {
        auto n = Utils::parseUnsignedLong(s_n);
        if (!n.first || n.second == 0) {
            cerr << "Error: invalid tenure\n";
            return EXIT_FAILURE;
        }
        tenure = n.second;
    }

    try {
        Loan loan(principal, rate, tenure);

        cout << fixed << setprecision(2);
        if (wantCP) {
            long double emi = loan.monthlyEMI();
            cout << "Monthly EMI: " << emi << "\n";
            cout << "Total payment: " << loan.totalPayment() << "\n";
            cout << "Total interest: " << loan.totalInterest() << "\n";
        } else {
            cout << "Principal: " << principal << "\n";
            cout << "Annual rate (%): " << rate << "\n";
            cout << "Tenure (months): " << tenure << "\n";
            cout << "Use -cp to compute monthly payment (EMI)\n";
        }
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return 0;
}
