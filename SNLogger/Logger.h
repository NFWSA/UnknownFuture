#ifndef __SN_LOGGER_H__
#define __SN_LOGGER_H__

#include <string>
#include <functional>
#include <fstream>

namespace SurgeNight
{

class FormatLogger;

class Logger
{
public:
    friend class FormatLogger;
    enum {
        SHOW_NONE = 0x0,
        SHOW_SUCC = 0x1,
        SHOW_SHOW = 0x2,
        SHOW_DEBUG = 0x4,
        SHOW_WARN = 0x8,
        SHOW_ERROR = 0x10
    };
    enum {
        LEVEL_VERBOSE = SHOW_SUCC | SHOW_SHOW | SHOW_DEBUG | SHOW_WARN | SHOW_ERROR,
        LEVEL_INFO =  SHOW_SHOW | SHOW_DEBUG | SHOW_WARN | SHOW_ERROR,
        LEVEL_DEBUG = SHOW_DEBUG | SHOW_WARN | SHOW_ERROR,
        LEVEL_WARNING = SHOW_WARN | SHOW_ERROR,
        LEVEL_ERROR = SHOW_ERROR,
        LEVEL_NONE = SHOW_NONE
    };
    enum LOG_HANDLE_TYPE {
        HANDLE_FILE,
        HANDLE_STDOUT,
        HANDLE_STDERR
    };

    // stdout logger
    Logger(const unsigned int level = LEVEL_VERBOSE);
    // stdout/stderr/file logger
    Logger(const LOG_HANDLE_TYPE handle, const unsigned int level = LEVEL_VERBOSE, const std::string &filename = "");
    ~Logger();

    void setLogLevel(const unsigned int level);

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
    unsigned int m_level, m_handle;
    std::ofstream m_file;
};

    static Logger rawOutLogger, rawErrLogger(Logger::HANDLE_STDERR);

}

#endif //__SN_LOGGER_H__
