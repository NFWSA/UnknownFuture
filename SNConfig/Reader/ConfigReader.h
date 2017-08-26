#ifndef __SN_CONFIG_READER_H__
#define __SN_CONFIG_READER_H__

#include <string>
#include "../Data/Variant.h"
#include "../Data/ConfigData.h"

namespace SurgeNight
{

//class ConfigData;

class ConfigReader
{
public:
    enum ConfigFormat {
        CONFIG_FORMAT_INI,
        CONFIG_FORMAT_JSON
    };
    static inline ConfigData getConfigFrom(const std::string &filename, const ConfigFormat format);
    static inline const bool saveConfigTo(const std::string &filename, const ConfigFormat format);
    static ConfigData getINIConfigFrom(const std::string &filename);
    static const bool saveINIConfigTo(const std::string &filename);
    static ConfigData getJSONConfigFrom(const std::string &filename);
    static const bool saveJSONConfigTo(const std::string &filename);

  private:
    ConfigReader() = delete;
    ~ConfigReader() = delete;
};

}

#include "ConfigReader.inl"
#endif //__SN_CONFIG_READER_H__
