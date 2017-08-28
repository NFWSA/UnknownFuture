#ifndef __SN_FORMAT_LOGGER_H__
#define __SN_FORMAT_LOGGER_H__

#include <string>
#include <ostream>
#include "Logger.h"

namespace SurgeNight
{

class FormatLogger : public Logger
{
public:
    FormatLogger(const unsigned int level);
    FormatLogger(const Logger::LOG_HANDLE_TYPE handle = Logger::HANDLE_STDOUT, const unsigned int level = Logger::LEVEL_VERBOSE, const std::string &filename = "");
    ~FormatLogger();

    Logger& raw();

    const bool success(const std::string &msg);
    const bool show(const std::string &msg);
    const bool debug(const std::string &msg);
    const bool warn(const std::string &msg);
    const bool error(const std::string &msg);
    inline const bool s(const std::string &msg)
    {
        return success(msg);
    }
    inline const bool operator()(const std::string &msg)
    {
        return show(msg);
    }
    inline const bool info(const std::string &msg)
    {
        return show(msg);
    }
    inline const bool d(const std::string &msg)
    {
        return debug(msg);
    }
    inline const bool w(const std::string &msg)
    {
        return warn(msg);
    }
    inline const bool e(const std::string &msg)
    {
        return error(msg);
    }

private:
};

static FormatLogger logger, errLogger(Logger::HANDLE_STDERR);

}

#endif //__SN_FORMAT_LOGGER_H__
