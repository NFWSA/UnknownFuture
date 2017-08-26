#ifndef __SN_CONFIG_DATA_H__
#define __SN_CONFIG_DATA_H__

#include <map>
#include <string>

namespace SurgeNight
{

class Variant;

class ConfigData
{
public:
    ConfigData() = default;
    ~ConfigData() = default;
    Variant &operator[](const std::string &name);
    const bool has(const std::string &name);

    const int getInt(const std::string &name, const int defaultInt = 0);
    const float getFloat(const std::string &name, const float defaultFloat = 0.0f);
    const double getDouble(const std::string &name, const double defaultDouble = 0.0);
    const unsigned char getUChar(const std::string &name, const unsigned char defaultChar = '\0');
    const std::string getString(const std::string &name, const std::string &defaultStr = "");

private:
    std::map<std::string, Variant> m_config;
};

}

#endif //__SN_CONFIG_DATA_H__
