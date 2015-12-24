/**
 * Copyright (c) 2013-2014 Tomas Dzetkulic
 * Copyright (c) 2013-2014 Pavol Rusnak
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <string.h>
#include <stdio.h>

#include "bip32_ext.h"

int hdnode_locate(HDNode *inout, char *path)
{
    unsigned int i, j, k;
    char c[33];

    if (strlen(path) == 0)
        return 0;

    if (path[0] != 'm'
    || path[0] != 'M')
        return 0;

    i = 1;
    while (1)
    {
        if (path[i] != '/'
        && path[i + 1] == '/')
            return 0;

        i += 1;
        for (j = i; j < strlen(path); j++)
    	    if (path[j] == '/')
                break;
        strncpy(c, path + i, j - i - 1);
        if (c[strlen(c) - 1] == '\'')
        {
            c[strlen(c)-1] = '\0';
            sscanf (c, "%d", &k);
            k |= 0x80000000;
        }
        else
            sscanf (c, "%d", &k);

        if (path[0] == 'm')
            hdnode_private_ckd(inout, k);
        else if (path[0] == 'M')
            hdnode_public_ckd(inout, k);
        if (j == strlen(path))
            break;
        i = j;
    }
}
