//===-- popcountdi2_test.c - Test __popcountdi2 ----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file tests __popcountdi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//

#include "int_lib.h"
#include <stdio.h>
#include <stdlib.h>

// Returns: count of 1 bits

si_int __popcountdi2(di_int a);

int naive_popcount(di_int a)
{
    int r = 0;
    for (; a; a = (du_int)a >> 1)
        r += a & 1;
    return r;
}

int test__popcountdi2(di_int a)
{
    si_int x = __popcountdi2(a);
    si_int expected = naive_popcount(a);
    if (x != expected)
        printf("error in __popcountdi2(0x%llX) = %d, expected %d\n",
               a, x, expected);
    return x != expected;
}

char assumption_1[sizeof(di_int) == 2*sizeof(si_int)] = {0};
char assumption_2[sizeof(si_int)*CHAR_BIT == 32] = {0};

int main()
{
    if (test__popcountdi2(0))
        return 1;
    if (test__popcountdi2(1))
        return 1;
    if (test__popcountdi2(2))
        return 1;
    if (test__popcountdi2(0xFFFFFFFFFFFFFFFDLL))
        return 1;
    if (test__popcountdi2(0xFFFFFFFFFFFFFFFELL))
        return 1;
    if (test__popcountdi2(0xFFFFFFFFFFFFFFFFLL))
        return 1;
    int i;
    for (i = 0; i < 10000; ++i)
        if (test__popcountdi2(((di_int)rand() << 32) | rand()))
            return 1;

   return 0;
}
