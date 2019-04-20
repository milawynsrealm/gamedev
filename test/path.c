#define USE_CONSOLE_APP
#include "lgdl/main.h"
#include "lgdl/path.h"

int ConsoleMain(int argc, UNICHAR *argv[])
{
    consoleprint(_T("Path Sepeartor: %s\n"), GetPathDirSeperator())
    
    return 0;
}
