#include "Logger.h"
#include "ColorOutput/ColorTable.h"
#include <iostream>

namespace SurgeNight
{

// stdout logger
Logger::Logger(const unsigned int level) : m_level(level), m_handle(HANDLE_STDOUT)
{

}
// stdout/stderr/file logger
Logger::Logger(const LOG_HANDLE_TYPE handle, const unsigned int level, const std::string &filename) : m_level(level), m_handle(handle)
{
    if (HANDLE_FILE == handle) {
        m_file.open(filename, std::ofstream::app);
        if (!m_file)
            m_file.close();
    }
}

Logger::~Logger()
{
    if (HANDLE_FILE == m_handle) {
        if (m_file) {
            m_file.close();
            m_file.clear();
        }
    }
}

void Logger::setLogLevel(const unsigned int level)
{
    m_level = level;
}

const bool Logger::success(const std::string &msg)
{
    if (!(SHOW_SUCC | m_level))
        return false;
    if (HANDLE_FILE == m_handle && !m_file)
        return false;
    std::ostream &out = HANDLE_STDOUT == m_handle ? std::cout : (HANDLE_STDERR == m_handle ? std::cerr : m_file);
    out //<< snBg.Lggreen + snFg.Black << "[Succ ]" << snClear << " : "
        << snBg.Clear + snFg.Lggreen << msg << snClear << std::endl;
    return true;
}

const bool Logger::show(const std::string &msg)
{
    if (!(SHOW_SHOW | m_level))
        return false;
    if (HANDLE_FILE == m_handle && !m_file)
        return false;
    std::ostream &out = HANDLE_STDOUT == m_handle ? std::cout : (HANDLE_STDERR == m_handle ? std::cerr : m_file);
    out //<< snBg.Lgshgreen + snFg.Black << "[Info ]" << snClear << " : "
        << snBg.Clear + snFg.Lgshgreen << msg << snClear << std::endl;
    return true;
}

const bool Logger::debug(const std::string &msg)
{
    if (!(SHOW_DEBUG | m_level))
        return false;
    if (HANDLE_FILE == m_handle && !m_file)
        return false;
    std::ostream &out = HANDLE_STDOUT == m_handle ? std::cout : (HANDLE_STDERR == m_handle ? std::cerr : m_file);
    out //<< snBg.Yellow + snFg.Black << "[Debug]" << snClear << " : "
        << snBg.Clear + snFg.Lgyellow << msg << snClear << std::endl;
    return true;
}

const bool Logger::warn(const std::string &msg)
{
    if (!(SHOW_WARN | m_level))
        return false;
    if (HANDLE_FILE == m_handle && !m_file)
        return false;
    std::ostream &out = HANDLE_STDOUT == m_handle ? std::cout : (HANDLE_STDERR == m_handle ? std::cerr : m_file);
    out //<< snBg.Lgyellow + snFg.Black << "[Warn ]" << snClear << " : "
        << snBg.Clear + snFg.Lgyellow << msg << snClear << std::endl;
    return true;
}

const bool Logger::error(const std::string &msg)
{
    if (!(SHOW_ERROR | m_level))
        return false;
    if (HANDLE_FILE == m_handle && !m_file)
        return false;
    std::ostream &out = HANDLE_STDOUT == m_handle ? std::cout : (HANDLE_STDERR == m_handle ? std::cerr : m_file);
    out //<< snBg.Lgred + snFg.Black << "[Error]" << snClear << " : "
        << snBg.Clear + snFg.Lgred << msg << snClear << std::endl;
    return true;
}

}
