#pragma once
#include <string>
#include <unordered_map>
#include <utility>

namespace Utils {
    std::unordered_map<std::string,std::string> readConfigFile(const std::string &path);
    std::pair<bool, long double> parseLongDouble(const std::string &s);
    std::pair<bool, unsigned long> parseUnsignedLong(const std::string &s);
    std::string getArgValue(int argc, char* argv[], const std::string &flag);
}
