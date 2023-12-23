/*
 * Copyright (c) 2023 Matheus Cardoso (casmatheus44@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* The First time this file is included and ONLY Then, TEST_H_IMPL should be Defined. */

#ifndef TEST_H_
#define TEST_H_

#ifdef __cplusplus
extern "C" {
#endif

#define Assert(expression) if (!!!(expression)) _AssertFailure(#expression, __FILE__, __LINE__)

void TestBegin(char* test_name);
void _AssertFailure(char* expression, char* file, int line);

#ifdef TEST_H_IMPL

#include <stdio.h>

#define Assert(expression) \
  if (!!!(expression)) _AssertFailure(#expression, __FILE__, __LINE__)

static void TestBegin(char* test_name) {
  printf("\nRunning Test");
  if (test_name != NULL) {
    printf(": [%s]", test_name);
  }
  printf("\n");
}

static void _AssertFailure(char* expression, char* file, int line) {
  printf("\t\033[91m[ERROR]\033[0m ");
  printf("(%s) Evaluated to False at %s:%d\n", expression, file, line);
}

#undef TEST_H_IMPL
#endif /* TEST_H_IMPL */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TEST_H_ */
