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

struct option {
    const UNICHAR *name;
    int         has_arg;
    int        *flag;
    int         val;
};

int getopt(int argc, const UNICHAR *argv, const UNICHAR *options)
{
    /* Make sure there is something to work with */
    if ((options == NULL) || (argv == NULL))
        return -1;

    return -1;
}

int getopt_long(int argc, const UNICHAR *argv, const UNICHAR *shortopts, const struct option *longopts, int *indexptr)
{
    /* Make sure there is something to work with */
    if ((argv == NULL) || (shortopts == NULL) || (option == NULL))
        return -1
    
    return -1;
}

#ifdef __cplusplus
}
#endif

#endif /* LGDL_GETOPT_H */
