#include "FormatLogger.h"
#include "ColorOutput/ColorTable.h"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

namespace SurgeNight
{

FormatLogger::FormatLogger(const unsigned int level) : Logger(level)
{

}

FormatLogger::FormatLogger(const Logger::LOG_HANDLE_TYPE handle, const unsigned int level, const std::string &filename) :
    Logger(handle, level, filename)
{

}

FormatLogger::~FormatLogger()
{

}

Logger& FormatLogger::raw()
{
    return *this;
}

inline std::tm* getNow()
{
    std::time_t t = std::time(nullptr);
    return std::localtime(&t);
}

const bool FormatLogger::success(const std::string &msg)
{
    if (!(SHOW_SUCC | m_level))
        return false;
    if (HANDLE_FILE == m_handle && !m_file)
        return false;
    std::ostream &out = HANDLE_STDOUT == m_handle ? std::cout : (HANDLE_STDERR == m_handle ? std::cerr : m_file);
    out << std::put_time(getNow(), "%Y/%m/%d %H:%M:%S ")
        << snBg.Lggreen + snFg.Black << "[Succ ]" << snClear << " : "
        << snBg.Clear + snFg.Lggreen << msg << snClear << std::endl;
    return true;
}

const bool FormatLogger::show(const std::string &msg)
{
    if (!(SHOW_SHOW | m_level))
        return false;
    if (HANDLE_FILE == m_handle && !m_file)
        return false;
    std::ostream &out = HANDLE_STDOUT == m_handle ? std::cout : (HANDLE_STDERR == m_handle ? std::cerr : m_file);
    out << std::put_time(getNow(), "%Y/%m/%d %H:%M:%S ")
        << snBg.Lgshgreen + snFg.Black << "[Info ]" << snClear << " : "
        << snBg.Clear + snFg.Lgshgreen << msg << snClear << std::endl;
    return true;
}

const bool FormatLogger::debug(const std::string &msg)
{
    if (!(SHOW_DEBUG | m_level))
        return false;
    if (HANDLE_FILE == m_handle && !m_file)
        return false;
    std::ostream &out = HANDLE_STDOUT == m_handle ? std::cout : (HANDLE_STDERR == m_handle ? std::cerr : m_file);
    out << std::put_time(getNow(), "%Y/%m/%d %H:%M:%S ")
        << snBg.Yellow + snFg.Black << "[Debug]" << snClear << " : "
        << snBg.Clear + snFg.Lgyellow << msg << snClear << std::endl;
    return true;
}

const bool FormatLogger::warn(const std::string &msg)
{
    if (!(SHOW_WARN | m_level))
        return false;
    if (HANDLE_FILE == m_handle && !m_file)
        return false;
    std::ostream &out = HANDLE_STDOUT == m_handle ? std::cout : (HANDLE_STDERR == m_handle ? std::cerr : m_file);
    out << std::put_time(getNow(), "%Y/%m/%d %H:%M:%S ")
        << snBg.Lgyellow + snFg.Black << "[Warn ]" << snClear << " : "
        << snBg.Clear + snFg.Lgyellow << msg << snClear << std::endl;
    return true;
}

const bool FormatLogger::error(const std::string &msg)
{
    if (!(SHOW_ERROR | m_level))
        return false;
    if (HANDLE_FILE == m_handle && !m_file)
        return false;
    std::ostream &out = HANDLE_STDOUT == m_handle ? std::cout : (HANDLE_STDERR == m_handle ? std::cerr : m_file);
    out << std::put_time(getNow(), "%Y/%m/%d %H:%M:%S ")
        << snBg.Lgred + snFg.Black << "[Error]" << snClear << " : "
        << snBg.Clear + snFg.Lgred << msg << snClear << std::endl;
    return true;
}

}
