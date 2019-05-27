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
#ifndef DEBUG_H
#define DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "shared.h"

#define DEBUG_NORMAL 0
#define DEBUG_WARNING 1
#define DEBUG_ERROR 2

FILE *DebugOpen(UNICHAR *file)
{
    /* Use UTF-8 as the encoding format since HTML5 expects it */
    return _fileopen(file, _T("w, ccs=UTF-8"));
}

int DebugPrintHeader(FILE *file, UNICHAR *appname)
{
    UNICHAR *headTitle = NULL;
    UNICHAR *bodyTitle = NULL;
    UNICHAR *dateTime = NULL;
    UNICHAR *genMsg = NULL;
    time_t rawtime;
    struct tm *timeinfo;

    /* Make sure there's an application name and a file to work with */
    if ((appname == NULL) || (file == NULL))
        return 1;

    /* Lets the user know that this file was generated by a program. */
    _stringcopy(genMsg, _T("<!-- This file has been automatically generated by "));
    _stringcat(genMsg, appname);
    _stringcat(genMsg, _T(". -->"));

    /* Lets the browser know this is an HTML5 document */
    _fileputs(genMsg, file);
    _fileputs(_T("<!DOCTYPE html>"), file);
    _fileputs(_T("<html>"), file);

    /* Header Title with CSS formatting */
    _stringcopy(headTitle, _T("<head>"));
    _stringcat(headTitle, _T("<meta charset=""UTF-8"">"));
    _stringcat(headTitle, _T("<title>"));
    _stringcat(headTitle, appname);
    _stringcat(headTitle, _T(" - Debug Log</title>"));
    _stringcat(headTitle, _T("<style>"));
    _stringcat(headTitle, _T("body {"));
    _stringcat(headTitle, _T("    background-color:rgb(255,255,255)"));
    _stringcat(headTitle, _T("}"));
    _stringcat(headTitle, _T("</style></head>"));
    _fileputs(headTitle, file);

    /* Body Start */
    _fileputs(_T("<body>"), file);

    /* Body Title */
    _stringcopy(bodyTitle, _T("<h1>"));
    _stringcat(bodyTitle, appname);
    _stringcat(bodyTitle, _T(" - Debug Log"));
    _stringcat(bodyTitle, _T("</h1>"));
    _fileputs(bodyTitle, file);

    /* Grabs the Time/Date */
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    if (timeinfo == NULL)
        return 1;

    /* Date/Time */
    _stringcopy(dateTime, _T("<p style=""font-style:italic;"">"));
    _stringcat(dateTime, _currenttime(timeinfo));
    _stringcat(dateTime, _T("/<p>"));
    _fileputs(dateTime, file);

    /* Puts divider to divide the header from the content */
    _fileputs(_T("<hr>"), file);

    /* Starts an unordered list so messages can now be added 
       to the debug log */
    _fileputs(_T("<ul>"), file);

    return 0;
}

int DebugPrintMessage(FILE *file, UNICHAR *message, int debugLevel)
{
    UNICHAR *messageBody = NULL;
    UNICHAR *textColor = NULL;

    /* There has to be a file and a message to work with */
    if ((file == NULL) || (message == NULL))
        return 1;

    /* If the developer goes out of bounds of the debug level, assume
       that the debug level is normal. This makes development easier. */
    if ((debugLevel < DEBUG_NORMAL) || (debugLevel > DEBUG_ERROR))
        debugLevel = DEBUG_NORMAL;

    /* Determines what color the text line is */
    switch(debugLevel)
    {
        case DEBUG_NORMAL: /* Bold Black */
            _stringcopy(textColor, _T(" style=""font-weight:bold;"">"));
        case DEBUG_WARNING: /* Yellow */
            _stringcopy(textColor, _T(" style=""color:rgb(255,165,0);"">"));
        case DEBUG_ERROR: /* Red */
            _stringcopy(textColor, _T(" style=""color:rgb(255,0,0);"">"));
    }

    /* Starts the list item for the message */
    _stringcopy(messageBody, _T("<li"));
    _stringcat(messageBody, textColor);

    /* Outputs the final message to the debug log */
    _fileputs(messageBody, file);

    /* Close the list item so that separate items cannot overlap */
    _stringcat(messageBody, _T("</li>"));

    return 0;
}

int DebugPrintFooter(FILE *file)
{
    /* There has to be a file to work with */
    if (file == NULL)
        return 1;

    /* Puts the closing tags for the HTML document. Technically, the HTML 
       file can be opened without it, but this ensures that it stays compliant. */
    _fileputs(_T("</ul>"), file);
    _fileputs(_T("</body>"), file);
    _fileputs(_T("</html>"), file);

    return 0;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* DEBUG_H */
