/*
    Copyright (c) 2012-2017, Kim Grasman <kim.grasman@gmail.com>
    Copyright (c) 2018, Lee Schroeder <spaceseel at gmail dot com>
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
#ifndef LGDL_GETOPT_H
#define LGDL_GETOPT_H

#include "shared.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* flags used for getopt_long */
#define no_argument       0
#define required_argument 1
#define optional_argument 2

/* If the function fails, this value is set to the proper error code */
int opterr = 0;

/* This must be set to 1 before any other call is made */
int optind = 1;

/* If the option isn't found in options, then store the value here */
int optopt = 0;

/* Used to grab the argument value */
UNICHAR *optarg = NULL;
static UNICHAR *optcursor = NULL;

/* This structure is used in getopt_long */
struct option {
    const UNICHAR *name;
    int           has_arg;
    int           *flag;
    int           val;
};

int getopt(int argc, const UNICHAR *argv, const UNICHAR *options)
{
    int optchar = -1;
    const UNICHAR* optdecl = NULL;

    /* Reset the values so they can be used again */
    optarg = NULL;
    opterr = 0;
    optopt = 0;

    /* Make sure it doesn't go out of bounds */
    if (optind >= argc)
        goto no_more_optchars;

    /* Make sure there's something to work with */
    if (argv[optind] == NULL)
        goto no_more_optchars;

    /* Make sure the first character is valid */
    if (*argv[optind] != '-')
        goto no_more_optchars;

    /* An option must be given */
    if (stringcompare(argv[optind], _T("-")))
        goto no_more_optchars;

    /* This function doesn't process long options */
    if (stringcompare(argv[optind], _T("--")))
    {
        ++optind;
        goto no_more_optchars;
    }

    /* if optcursor is empty, fill it with the current value */
    if ((optcursor == NULL) || (*optcursor == _T('\0')))
        optcursor = argv[optind] + 1;

    optchar = *optcursor;

    /* Save the last known character */
    optopt = optchar;

    optdecl = findstring(options, optchar);
    if (optdecl)
    {
        if (optdecl[1] == _T(':'))
        {
            optarg = ++optcursor;

            if (*optarg == _T('\0'))
            {
                if (optdecl[2] != _T(':'))
                {
                    if (++optind < argc)
                        optarg = argv[optind];
                    else
                    {
                        optarg == NULL;
                        optchar = (optstring[0] == _T(':')) ? _T(':') : _T('?');
                    }
                }
            }
            else
                optarg = NULL;
        }
        optcursor = NULL;
    }
    else
        optchar = _T('?');

    if ((optcursor == NULL) || (*optcursor == _T('\0')))
        ++optind;

    return optchar;

no_more_optchars:
    optcursor = NULL;
    return -1;
}

int getopt_long(int argc, const UNICHAR *argv, const UNICHAR *shortopts, const struct option *longopts, int *longindex)
{
    const struct option* o = longopts;
    const struct option* match = NULL;
    int num_matches = 0;
    size_t argument_name_length = 0;
    const UNICHAR* current_argument = NULL;
    int retval = -1;

    optarg = NULL;
    optopt = 0;

    /* Make sure it doesn't go out of bounds */
    if (optind >= argc)
        return  -1;

    /* If the string is missing the -- at the beginning, assume that it might be a single character to work with */
    if (stringlength(argv[optind) < 3 || stringncompare(argv[optind], _T("--"), 2) != 0)
        return getopt(argc, argv, shortopts);

    /* Grabs the current argument since it meets the criteria */
    current_argument = argv[optind] + 2;
    argument_name_length = stringspan(current_argument, _T("="));
    for (;o->name; ++o)
    {
        if (stringncompare(o->name, current_argument, argument_name_length) == 0)
        {
            match = o;
            ++num_matches;
        }
    }

    /* If one match is found, then parse it */
    if (num_matches == 1)
    {
        if (longindex)
            *longindex = (match - longopts);

        if (match->flag)
            *(match->flag) = match->val;

        retval = match->flag ? 0 : match->val;

        if (match->has_arg != no_argument)
        {
            optarg = findstring(argv[optind], _T('='));
            if (optarg != NULL)
                ++optarg;

            if (match->has_arg == required_argument)
            {
                if ((optarg == NULL) && (++optind < argc))
                    optarg = argv[optind];
                
                if (optarg == NULL)
                    retval = _T(':');
            }
            else if (findstring(argv[optind], _T('=')))
                retval = _T('?');
            else
                retval = _T('?');
        }
    }

    ++optind;
    return retval;
}

#ifdef __cplusplus
}
#endif

#endif /* LGDL_GETOPT_H */
