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

#define USE_CONSOLE_APP
#include "lgdl/main.h"
#include "lgdl/system.h"

#define TESTPRINT(x, y) consoleprint(_T("%s: %s\n"), x, y);

void GetArchName(int osArch, UNICHAR *osName)
{
    GetSystemArchitecture(osArch);
    
    switch(osArch)
    {
        case ARCH_86:
        {
            stringcopy(osName, _T("x86"));
            break;
        }
        case ARCH_AMD64:
        {
            stringcopy(osName, _T("AMD64"));
            break;
        }
        case ARCH_ITANIUM:
        {
            stringcopy(osName, _T("Itanium"));
            break;
        }
        case ARCH_ARM:
        {
            stringcopy(osName, _T("ARM"));
            break;
        }
        case ARCH_ALPHA:
        {
            stringcopy(osName, _T("Alpha"));
            break;
        }
        case ARCH_PPC:
        {
            stringcopy(osName, _T("PowerPC"));   
            break;
        }
        default:
        {
            stringcopy(osName, _T("None defined"));
            break;
        }
    }
}

void CheckWinVersions(void)
{
    TESTPRINT(_T("\t- Windows XP or later: %s"), (IsMinimumOS(MINOS_XP) ? _T("TRUE") : _T("FALSE")));
    TESTPRINT(_T("\t- Windows Vista or later: %s"), (IsMinimumOS(MINOS_VISTA) ? _T("TRUE") : _T("FALSE")));
    TESTPRINT(_T("\t- Windows 7 or later: %s"), (IsMinimumOS(MINOS_7) ? _T("TRUE") : _T("FALSE")));
    TESTPRINT(_T("\t- Windows 8 or later: %s"), (IsMinimumOS(MINOS_8) ? _T("TRUE") : _T("FALSE")));
}

int ConsoleMain(int argc, UNICHAR *argv[])
{
    UNICHAR *osName, *appName, *osArchName, *osUserName, *osCompName;
    int osArch = 0;
    DWORDLONG osTotalMem = 0;
    APP_INSTANCE testInstance;

    /* Operating Sytstem */
    if (GetSystemOsName(&osName) == 0)
    {
        TESTPRINT(_T("Operating System"), osName);
    }

    /* The name of the application */
    if (GetSystemAppName(&appName) == 0)
    {
        TESTPRINT(_T("Application Name"), appName);
    }

    /* The name of the system architecture (eg. x86, AMD64, etc.) */
    GetArchName(osArch, &osArchName);
    TESTPRINT(_T("System Architecture"), osArchName);

    /* User Name */
    if (GetSystemUserName(&osUserName) == 0)
    {
        TESTPRINT(_T("User Name"), osUserName);
    }

    /* Computer Name */
    if (GetSystemComputerName(&osCompName) == 0)
    {
        TESTPRINT(_T("Computer Name"), osCompName);
    }

    /* Total Memory */
    if (GetSystemTotalMemory(osTotalMem) == 0)
    {
        consoleprint(_T("Total Memory: %I64u"), osTotalMem);
    }

    /* Minimum Version of the OS */
    if (IsMinimumOS(MINOS_NONE) == 0)
        CheckWinVersions();

    /* Try to create two instances under the same name. This feature is useful if the user wants only one instance of something like a window */
    testInstance = CreateAppInstance(_T("lgdl_test_instance"));
    if (testInstance != NULL)
    {
        APP_INSTANCE secondInstance = CreateAppInstance(_T("lgdl_test_instance"));
        if (secondInstance == NULL)
            consoleprint(_T("ERROR: Second instance was created successfully along with the first once. This should not happen!\n"));
        else
            consoleprint(_T("SUCCESS: Second instance could not be created. This means this works correctly!\n"));

        if ((DestroyAppInstance(testInstance) == 1) || (DestroyAppInstance(secondInstance) == 1))
            consoleprint(_T("ERROR: Failed to destroy application instances"))
    }

    return 0;
}
