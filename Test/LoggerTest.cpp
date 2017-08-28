#include <iostream>
#include <fstream>
#include "SNLogger/FormatLogger.h"

using namespace std;
using namespace SurgeNight;

int main()
{
    // stdout format logger
    logger.success("A successful format msg~");
    logger.show("An information format msg.");
    logger.debug("A debug format msg...");
    logger.warn("A warning format msg!");
    logger.error("An error format msg!!");
    logger.s("A successful format msg with alias name~");
    logger("An information format msg with alias name.");
    logger.d("A debug format msg with alias name...");
    logger.w("A warning format msg with alias name!");
    logger.e("An error format msg with alias name!!");
    logger.info("An information format msg with alias name.");
    // stdout raw logger
    logger.raw().success("This is a successful msg~");
    logger.raw().show("This is an information msg.");
    logger.raw().debug("This is a debug msg...");
    logger.raw().warn("This is a warning msg!");
    logger.raw().error("This is an error msg!!");
    logger.raw().s("This is a successful msg with alias name~");
    logger.raw()("This is an information msg with alias name.");
    logger.raw().d("This is a debug msg with alias name...");
    logger.raw().w("This is a warning msg with alias name!");
    logger.raw().e("This is an error msg with alias name!!");
    logger.raw().info("This is an information msg with alias name.");
    // file format logger
    FormatLogger myLogger(Logger::HANDLE_FILE, Logger::LEVEL_WARNING, "log.log");
    myLogger.success("A successful format msg~");
    myLogger.show("An information format msg.");
    myLogger.debug("A debug format msg...");
    myLogger.warn("A warning format msg!");
    myLogger.error("An error format msg!!");
    // file raw logger
    myLogger.raw().success("This is a successful msg~");
    myLogger.raw().show("This is an information msg.");
    myLogger.raw().debug("This is a debug msg...");
    myLogger.raw().warn("This is a warning msg!");
    myLogger.raw().error("This is an error msg!!");
    // stderr format logger
    errLogger.success("A successful format msg~");
    errLogger.show("An information format msg.");
    errLogger.debug("A debug format msg...");
    errLogger.warn("A warning format msg!");
    errLogger.error("An error format msg!!");
    // strerr raw logger
    errLogger.raw().success("This is a successful msg~");
    errLogger.raw().show("This is an information msg.");
    errLogger.raw().debug("This is a debug msg...");
    errLogger.raw().warn("This is a warning msg!");
    errLogger.raw().error("This is an error msg!!");
    return 0;
}
