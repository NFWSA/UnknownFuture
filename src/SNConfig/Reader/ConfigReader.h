#ifndef SN_CONFIG_READER_H
#define SN_CONFIG_READER_H

#include <string>
#include "SNVariant/Variant.h"

namespace SurgeNight
{

class ConfigReader
{
public:
    enum ConfigFormat {
        CONFIG_FORMAT_INI,
        CONFIG_FORMAT_JSON
    };
    static inline ObjectVariant getConfigFrom(const std::string &filename, const ConfigFormat format);
    static inline const bool saveConfigTo(const std::string &filename, const ConfigFormat format);
    static ObjectVariant getINIConfigFrom(const std::string &filename);
    static const bool saveINIConfigTo(const std::string &filename);
    static ObjectVariant getJSONConfigFrom(const std::string &filename);
    static const bool saveJSONConfigTo(const std::string &filename);

  private:
    ConfigReader() = delete;
    ~ConfigReader() = delete;
};

}

#include "ConfigReader.inl"
#endif //SN_CONFIG_READER_H
