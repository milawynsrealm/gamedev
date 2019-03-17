/*
    Copyright (c) 2018-2019, Lee Schroeder
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
          notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
          notice, this list of conditions and the following disclaimer in the
          documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
          names of its contributors may be used to endorse or promote products
          derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL LEE SCHROEDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/*
    NOTES:
    * wWinMain() is the UNICODE version of the main program entry for Windows.
    * Windows uses 'wchar_t' while other operating systems like GNU/Linux uses
      'char' for parsing the command-line arguments. It is up to the developer(s)
      to deal with both cases.
    * This library requires Windows XP or later.
*/
#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef(_WIN32)
#include <windef.h>
#include <shellapi.h>
#endif /* _WIN32 */

#include "shared.h"

/* Reference to the main entry point of the application. Must be manually defined by the developer. */
#ifdef USE_CONSOLE_APP
extern int ConsoleMain(int argc, UNICHAR *argv[]);
#else
extern int ProgramMain(int argc, UNICHAR *argv[]);
#endif /* USE_CONSOLE_APP */

#ifdef(_WIN32)
#ifdef UNICODE
#ifdef USE_CONSOLE_APP
int wmain(int argc, UNICHAR *argv[])
{
    return ConsoleMain(argc, argv);
}
#else
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    int argc;
    WCHAR** argv;

    /* Converts the command line into a usable format */
    argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    return ProgramMain(argc, argv[]);
}
#endif /* USE_CONSOLE_APP */
#else /* ANSI */
#ifdef USE_CONSOLE_APP
int main(int argc, UNICHAR *argv[])
{
    return ConsoleMain(argc, argv);
}
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
    return ProgramMain(__argc, __argv);
}
#endif /* USE_CONSOLE_APP */
#endif /* UNICODE */
#else /* POSIX-based systems (Linux, BSD, macOS, etc.). It all uses the same entry point
         regardless of whether it's GUI or CUI. */
int main(int argc, char *argv[])
{
#ifdef USE_CONSOLE_APP
    return ConsoleMain(argc, argv);
#else
    return ProgramMain(argc, argv);
#endif /* USE_CONSOLE_APP */
}
#endif /* _WIN32 */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* MAIN_H */
