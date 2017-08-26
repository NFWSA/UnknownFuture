#include "ConfigData.h"
#include "Variant.h"
#include <map>
#include <string>

namespace SurgeNight
{

Variant& ConfigData::operator[](const std::string &name)
{
    //if (m_config.find(name) == m_config.end())
    //        m_config[name] = 0;
    return m_config[name];
}

const bool ConfigData::has(const std::string &name)
{
    return m_config.find(name) != m_config.end();
}

const int ConfigData::getInt(const std::string &name, const int defaultInt)
{
    if (!has(name))
        return defaultInt;
    return m_config.at(name).asInt();
}

const float ConfigData::getFloat(const std::string &name, const float defaultFloat)
{
    if (!has(name))
        return defaultFloat;
    return m_config.at(name).asFloat();
}

const double ConfigData::getDouble(const std::string &name, const double defaultDouble)
{
    if (!has(name))
        return defaultDouble;
    return m_config.at(name).asDouble();
}

const unsigned char ConfigData::getUChar(const std::string &name, const unsigned char defaultChar)
{
    if (!has(name))
        return defaultChar;
    return m_config.at(name).asUChar();
}

const std::string ConfigData::getString(const std::string &name, const std::string &defaultStr)
{
    if (!has(name))
        return defaultStr;
    return m_config.at(name).asString();
}

}
