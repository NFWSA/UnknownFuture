namespace SurgeNight
{

ObjectVariant ConfigReader::getConfigFrom(const std::string &filename, const ConfigReader::ConfigFormat format)
{
    switch (format) {
        case CONFIG_FORMAT_INI:
            return getINIConfigFrom(filename);
        case CONFIG_FORMAT_JSON:
            return getJSONConfigFrom(filename);
        default:
            return getINIConfigFrom(filename);
    }
}

const bool ConfigReader::saveConfigTo(const std::string &filename, const ConfigReader::ConfigFormat format)
{
    switch (format) {
        case CONFIG_FORMAT_INI:
            return saveINIConfigTo(filename);
        case CONFIG_FORMAT_JSON:
            return saveJSONConfigTo(filename);
        default:
            return saveINIConfigTo(filename);
    }
}

}
