#include "ConfigReader.h"
#include "SNVariant/Variant.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

namespace SurgeNight
{

using SurgeNight::ObjectVariant;

std::string& trim(std::string &str)
{
    for (auto it = str.begin(); it != str.end(); ) {
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

ObjectVariant ConfigReader::getINIConfigFrom(const std::string &filename)
{
    std::ifstream fin(filename);
    if (!fin) {
        fin.close();
        return ObjectVariant();
    }
    ObjectVariant rlt;
    std::string line, nowTag("");
    unsigned int lineNum = 0;
    while (std::getline(fin, line)) {
        ++lineNum;
        trim(line);
#if defined DEBUG || _DEBUG
        std::clog << lineNum << " :>" << line << "< " << line.size() << " " << line.empty() << std::endl;
#endif
        if (line.empty() || line.at(0) == ';')
            continue;
        if (line.size() > 3 && line.at(0) == '[') {
            if (line.at(line.size() - 1) != ']') {
                std::cerr << "Error! (" << filename << ":" << lineNum << ") tag is not closed." << std::endl;
                continue;
            }
            nowTag = line.substr(1, line.size() - 2);
            if (rlt[nowTag].isNull())
                rlt[nowTag] = ObjectVariant();
#if defined DEBUG || _DEBUG
            std::clog << "Tag:" << nowTag << " & begin " << std::endl;
#endif
            continue;
        }
        auto mid = line.find('=');
        std::string key(line.substr(0, mid));
        trim(key);
        if (mid == std::string::npos) {
            std::cerr << "Error! (" << key << ") at (" << filename << ":" << lineNum << ") is not assigned value." << std::endl;
            continue;
        }
        std::string valueStr(line.substr(mid + 1));
        trim(valueStr);
#if defined DEBUG || _DEBUG
        std::clog << "key:" << key << " & value string:>" << valueStr << "<" << std::endl;
#endif
        Variant value(toVariant(valueStr));
        if (!nowTag.empty())
            rlt[nowTag].asObject()[key] = value;
        else
            rlt[key] = value;
#if defined DEBUG || _DEBUG
        std::clog << '[' << key << "] & type: " << (value.isInt() || value.isUInt() ? "int" : (value.isDouble() ? "double" : (value.isString() ? "string" : (value.isChar() || value.isUChar() ? "char" : "float"))))  << " & value: >" << valueStr << "<" << std::endl;
#endif
    }
    return rlt;
}

const bool ConfigReader::saveINIConfigTo(const std::string &filename)
{
    return true;
}

ObjectVariant ConfigReader::getJSONConfigFrom(const std::string &filename)
{
    return ObjectVariant();
}

const bool ConfigReader::saveJSONConfigTo(const std::string &filename)
{
    return true;
}

}
