#include "ConfigReader.h"
#include "../Data/ConfigData.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

namespace SurgeNight
{

using SurgeNight::ConfigData;

std::string& trim(std::string &str)
{
    for (auto it = str.begin(); it!=str.end(); ) {
        if (*it == ' ' || *it == '\r' || *it == '\n' || *it == '\t') {
            it = str.erase(it);
            continue;
        }
        break;
    }
    for (auto it = str.end(); it != str.begin();) {
        --it;
        if (*it == ' ' || *it == '\r' || *it == '\n' || *it == '\t') {
                it = str.erase(it);
                continue;
        }
        break;
    }
    return str;
}

ConfigData ConfigReader::getINIConfigFrom(const std::string &filename)
{
    std::ifstream fin(filename);
    if (!fin) {
        fin.close();
        return ConfigData();
    }
    ConfigData rlt;
    std::string line;
    unsigned int lineNum = 0;
    while (std::getline(fin, line)) {
        ++lineNum;
        trim(line);
        if (!line.empty() && line.at(0) == ';')
                continue;
        if (!line.empty() && line.at(0) == '[')
                continue;
        auto mid = line.find('=');
        std::string key(line.substr(0, mid));
        trim(key);
        if (mid == std::string::npos) {
            std::cerr << "Error! (" << key << ") at (" << filename << " " << lineNum << ") is not assigned value." << std::endl;
            continue;
        }
        std::string valueStr(line.substr(mid + 1));
        trim(valueStr);
#if defined DEBUG || _DEBUG
        std::cerr << key << " &----& " << valueStr << std::endl;
#endif
        Variant value;
        auto it =
            std::find_if(valueStr.begin(), valueStr.end(), [](char ch) -> bool {
                    return (ch != '-' &&
                           ch != '+' && ch != '.') && (ch < '0' || ch > '9');
            });
        if (it != valueStr.end()) {
            // string mode (if size == 1 char mode)
            if (valueStr.size() == 1)
                value = valueStr.at(0);
            else
                value = valueStr;
        }
        else {
            it = std::find_if(valueStr.begin(), valueStr.end(), [](char ch) -> bool {
                    return ch == '.';
            });
            if (it != valueStr.end()) {
                // double mode (same as float mode)
                try {
                    value = stod(valueStr);
                }
                catch (std::invalid_argument) {
                    // string mode (if size == 1 char mode)
                    if (valueStr.size() == 1)
                        value = valueStr.at(0);
                    else
                        value = valueStr;
                }
                catch (std::out_of_range) {
                    // string mode (if size == 1 char mode)
                    if (valueStr.size() == 1)
                        value = valueStr.at(0);
                    else
                        value = valueStr;
                }
            }
            else {
                // int mode
                try {
                    value = stoi(valueStr);
                }
                catch (std::invalid_argument) {
                    // string mode (if size == 1 char mode)
                    if (valueStr.size() == 1)
                        value = valueStr.at(0);
                    else
                        value = valueStr;
                }
                catch (std::out_of_range) {
                    // string mode (if size == 1 char mode)
                    if (valueStr.size() == 1)
                        value = valueStr.at(0);
                    else
                        value = valueStr;
                }
            }
        }
        rlt[key] = value;
#if defined DEBUG || _DEBUG
        std::cerr << '[' << key << "] &" << (value.isInt() ? "int" : (value.isDouble() ? "double" : (value.isString() ? "string" : (value.isUChar() ? "char" : "float"))))  << "& " << valueStr << std::endl;
#endif
    }
    return rlt;
}

const bool ConfigReader::saveINIConfigTo(const std::string &filename)
{
    return true;
}

ConfigData ConfigReader::getJSONConfigFrom(const std::string &filename)
{
    return ConfigData();
}

const bool ConfigReader::saveJSONConfigTo(const std::string &filename)
{
    return true;
}

}
