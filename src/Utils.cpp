#include "Utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

static inline string trim(const string &s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

namespace Utils {

std::unordered_map<std::string,std::string> readConfigFile(const std::string &path) {
    unordered_map<string,string> out;
    ifstream in(path);
    if (!in) return out;
    string line;
    while (getline(in, line)) {
        string t = trim(line);
        if (t.empty()) continue;
        if (t.size()>0 && t[0] == '#') continue;
        size_t eq = t.find('=');
        if (eq == string::npos) continue;
        string key = trim(t.substr(0, eq));
        string val = trim(t.substr(eq+1));
        if (!key.empty()) out[key] = val;
    }
    return out;
}

pair<bool,long double> parseLongDouble(const string &s) {
    try {
        size_t idx = 0;
        long double v = stold(s, &idx);
        if (idx != s.size()) return {false, 0.0L};
        return {true, v};
    } catch (...) {
        return {false, 0.0L};
    }
}

pair<bool,unsigned long> parseUnsignedLong(const string &s) {
    try {
        size_t idx = 0;
        unsigned long v = stoul(s, &idx);
        if (idx != s.size()) return {false, 0};
        return {true, v};
    } catch (...) {
        return {false, 0};
    }
}

string getArgValue(int argc, char* argv[], const string &flag) {
    for (int i = 1; i < argc; ++i) {
        string a = argv[i];
        if (a == flag && i+1 < argc) return string(argv[i+1]);
        if (a.rfind(flag, 0) == 0 && a.size() > flag.size()) {
            return a.substr(flag.size());
        }
    }
    return "";
}

} // namespace Utils
