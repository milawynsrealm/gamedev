/*
    Copyright (c) 2018, Lee Schroeder
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
#ifndef DEBUG_H
#define DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "shared.h"

#define DEBUG_NORMAL 0
#define DEBUG_WARNING 1
#define DEBUG_ERROR 2
}

FILE *DebugOpen(UNICHAR *file)
{
    return fileopen(file, _T("w, ccs=UTF-8"));
}

int DebugPuts(FILE *file, UNICHAR *string)
{
    /* There has to be a file to work with */
    if (file == NULL)
        return 1;

    return fileputs(_T(&string), file);
}

int DebugPrintHeader(FILE *file, UNICHAR *appname)
{
    UNICHAR *headTitle = NULL;
    UNICHAR *bodyTitle = NULL;
    UNICHAR *dateTime = NULL;
    time_t rawtime;
    struct tm *timeinfo;

    /* Make sure there's an application name and a file to work with */
    if ((appname == NULL) || (file == NULL))
        return 1;

    DebugPuts(file, _T("<!DOCTYPE html>"));
    DebugPuts(file, _T("<html>"));

    /* Header Title with CSS formatting */
    stringcopy(headTitle, _T("<head>"))
    stringcopy(headTitle, _T("<meta charset=""UTF-8"">"))
    stringcopy(headTitle, _T("<title>"))
    stringcat(headTitle, appname);
    stringcat(headTitle, _T(" - Debug Log</title>"));
    stringcat(headTitle, _T("<style>"));
    stringcat(headTitle, _T("body {"));
    stringcat(headTitle, _T("    background-color:rgb(255,255,255)"));
    stringcat(headTitle, _T("}"));
    stringcat(headTitle, _T("</style></head>"));
    DebugPuts(file, &headTitle);

    /* Body Start */
    DebugPuts(file, _T("<body>"))

    /* Body Title */
    stringcopy(bodyTitle, _T("<h1>"));
    stringcat(bodyTitle, appname);
    stringcat(bodyTitle, _T(" - Debug Log"));
    stringcat(bodyTitle, _T("</h1>"));
    DebugPuts(file, bodyTitle);

    /* Grabs the Time/Date */
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    if (timeinfo == NULL)
        return 1;

    /* Date/Time */
    stringcopy(dateTime, _T("<p>"));
    stringcat(dateTime, currenttime(timeinfo));
    stringcat(dateTime, _T("/<p>"));
    DebugPuts(file, dateTime);

    return 0;
}

int DebugPrintMessage(FILE *file, UNICHAR *message, int debugLevel)
{
    UNICHAR *messageBody;
    UNICHAR *textColor;

    /* There has to be a file and a message to work with */
    if ((file == NULL) || (message == NULL))
        return 1;

    /* If the developer goes out of bounds of the debug level, assume
       that the debug level is normal. This makes debugging easier. */
    if ((debugLevel < DEBUG_NORMAL) || (debugLevel > DEBUG_ERROR))
        debugLevel = DEBUG_NORMAL;

    /* Determines what color the text line is */
    switch(debugLevel)
    {
        case DEBUG_NORMAL: /* Black */
            stringcopy(textColor, _T(">"));
        case DEBUG_WARNING: /* Yellow */
            stringcopy(textColor, _T(" style=""color:rgb(255,165,0);"">WARNING: "));
        case DEBUG_ERROR: /* Red */
            stringcopy(textColor, _T(" style=""color:rgb(255,0,0);"">ERROR: "));
    }

    stringcopy(messageBody, _T("<p"));
    stringcat(messageBody, textColor);
    stringcat(messageBody, _T("</p>"));
    
    /* Outputs the final message to the debug log */
    DebugPuts(file, messageBody);

    return 0;
}

int DebugPrintFooter(FILE *file)
{
    /* There has to be a file to work with */
    if (file == NULL)
        return 1;

    /* Puts the closing tags for the HTML document. Technically, the HTML 
       file can be opened without it, but this ensures that it stays compliant. */
    DebugPuts(file, _T("</body>"));
    DebugPuts(file, _T("</html>"));

    return 0;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* DEBUG_H */
