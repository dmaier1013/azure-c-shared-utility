// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdint.h>
#include <stdlib.h>
#include "testrunnerswitcher.h"
#include "umockcall.h"

/* TODO: test malloc failures */
/* TODO: serialize tests */

/* Not tested requirements */
/* SRS_UMOCKCALL_01_002: [ If allocating memory for the umock call instance fails, umockcall_create shall return NULL. ] */

typedef struct test_mock_call_data_free_CALL_TAG
{
    void* umockcall_data;
} test_mock_call_data_free_CALL;

static test_mock_call_data_free_CALL* test_mock_call_data_free_calls;
static size_t test_mock_call_data_free_call_count;

typedef struct test_mock_call_data_are_equal_CALL_TAG
{
    void* left;
    void* right;
} test_mock_call_data_are_equal_CALL;

static test_mock_call_data_are_equal_CALL* test_mock_call_data_are_equal_calls;
static size_t test_mock_call_data_are_equal_call_count;
static int test_mock_call_data_are_equal_expected_result;

typedef struct test_mock_call_data_stringify_CALL_TAG
{
    void* umockcall_data;
} test_mock_call_data_stringify_CALL;

static test_mock_call_data_stringify_CALL* test_mock_call_data_stringify_calls;
static size_t test_mock_call_data_stringify_call_count;
static char* test_mock_call_data_stringify_expected_result = NULL;

void test_mock_call_data_free(void* umockcall_data)
{
    test_mock_call_data_free_CALL* new_calls = (test_mock_call_data_free_CALL*)realloc(test_mock_call_data_free_calls, sizeof(test_mock_call_data_free_CALL) * (test_mock_call_data_free_call_count + 1));
    if (new_calls != NULL)
    {
        test_mock_call_data_free_calls = new_calls;
        test_mock_call_data_free_calls[test_mock_call_data_free_call_count].umockcall_data = umockcall_data;
        test_mock_call_data_free_call_count ++;
    }
}

char* test_mock_call_data_stringify(void* umockcall_data)
{
    test_mock_call_data_stringify_CALL* new_calls = (test_mock_call_data_stringify_CALL*)realloc(test_mock_call_data_stringify_calls, sizeof(test_mock_call_data_stringify_CALL) * (test_mock_call_data_stringify_call_count + 1));
    if (new_calls != NULL)
    {
        test_mock_call_data_stringify_calls = new_calls;
        test_mock_call_data_stringify_calls[test_mock_call_data_stringify_call_count].umockcall_data = umockcall_data;
        test_mock_call_data_stringify_call_count++;
    }
    return test_mock_call_data_stringify_expected_result;
}

int test_mock_call_data_are_equal(void* left, void* right)
{
    test_mock_call_data_are_equal_CALL* new_calls = (test_mock_call_data_are_equal_CALL*)realloc(test_mock_call_data_are_equal_calls, sizeof(test_mock_call_data_are_equal_CALL) * (test_mock_call_data_are_equal_call_count + 1));
    if (new_calls != NULL)
    {
        test_mock_call_data_are_equal_calls = new_calls;
        test_mock_call_data_are_equal_calls[test_mock_call_data_are_equal_call_count].left = left;
        test_mock_call_data_are_equal_calls[test_mock_call_data_are_equal_call_count].right = right;
        test_mock_call_data_are_equal_call_count++;
    }
    return test_mock_call_data_are_equal_expected_result;
}

int another_test_mock_call_data_are_equal(void* left, void* right)
{
    (void)left, right;
    return 1;
}

BEGIN_TEST_SUITE(umockcall_unittests)

TEST_SUITE_INITIALIZE(suite_init)
{
}

TEST_SUITE_CLEANUP(suite_cleanup)
{
}

TEST_FUNCTION_INITIALIZE(test_function_init)
{
    test_mock_call_data_free_calls = NULL;
    test_mock_call_data_free_call_count = 0;

    test_mock_call_data_are_equal_calls = NULL;
    test_mock_call_data_are_equal_call_count = 0;
    test_mock_call_data_are_equal_expected_result = 1;

    test_mock_call_data_stringify_calls = NULL;
    test_mock_call_data_stringify_call_count = 0;
    test_mock_call_data_stringify_expected_result = NULL;
}

TEST_FUNCTION_CLEANUP(test_function_cleanup)
{
    free(test_mock_call_data_free_calls);
    test_mock_call_data_free_calls = NULL;
    test_mock_call_data_free_call_count = 0;

    free(test_mock_call_data_are_equal_calls);
    test_mock_call_data_are_equal_calls = NULL;
    test_mock_call_data_are_equal_call_count = 0;

    free(test_mock_call_data_stringify_calls);
    test_mock_call_data_stringify_calls = NULL;
    test_mock_call_data_stringify_call_count = 0;
}

/* umockcall_create */

/* Tests_SRS_UMOCKCALL_01_001: [ umockcall_create shall create a new instance of a umock call and on success it shall return a non-NULL handle to it. ] */
TEST_FUNCTION(umockcall_create_with_proper_args_succeeds)
{
    // arrange

    // act
    UMOCKCALL_HANDLE result = umockcall_create("test_function", (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);

    // assert
    ASSERT_IS_NOT_NULL(result);

    // cleanup
    umockcall_destroy(result);
}

/* Tests_SRS_UMOCKCALL_01_003: [ If any of the arguments are NULL, umockcall_create shall fail and return NULL. ] */
TEST_FUNCTION(umockcall_create_with_NULL_function_name_fails)
{
    // arrange

    // act
    UMOCKCALL_HANDLE result = umockcall_create(NULL, (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);

    // assert
    ASSERT_IS_NULL(result);
}

/* Tests_SRS_UMOCKCALL_01_003: [ If any of the arguments are NULL, umockcall_create shall fail and return NULL. ] */
TEST_FUNCTION(umockcall_create_with_NULL_call_data_fails)
{
    // arrange

    // act
    UMOCKCALL_HANDLE result = umockcall_create("test_function", NULL, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);

    // assert
    ASSERT_IS_NULL(result);
}

/* Tests_SRS_UMOCKCALL_01_003: [ If any of the arguments are NULL, umockcall_create shall fail and return NULL. ] */
TEST_FUNCTION(umockcall_create_with_NULL_call_data_free_function_fails)
{
    // arrange

    // act
    UMOCKCALL_HANDLE result = umockcall_create("test_function", (void*)0x4242, NULL, test_mock_call_data_stringify, test_mock_call_data_are_equal);

    // assert
    ASSERT_IS_NULL(result);
}

/* Tests_SRS_UMOCKCALL_01_003: [ If any of the arguments are NULL, umockcall_create shall fail and return NULL. ] */
TEST_FUNCTION(umockcall_create_with_NULL_call_data_stringify_function_fails)
{
    // arrange

    // act
    UMOCKCALL_HANDLE result = umockcall_create("test_function", (void*)0x4242, test_mock_call_data_free, NULL, test_mock_call_data_are_equal);

    // assert
    ASSERT_IS_NULL(result);
}

/* Tests_SRS_UMOCKCALL_01_003: [ If any of the arguments are NULL, umockcall_create shall fail and return NULL. ] */
TEST_FUNCTION(umockcall_create_with_NULL_call_data_are_equal_function_fails)
{
    // arrange

    // act
    UMOCKCALL_HANDLE result = umockcall_create("test_function", (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, NULL);

    // assert
    ASSERT_IS_NULL(result);
}

/* umockcall_destroy */

/* Tests_SRS_UMOCKCALL_01_004: [ umockcall_destroy shall free a previously allocated umock call instance. ] */
TEST_FUNCTION(umockcall_destroy_frees_call_data)
{
    // arrange
    UMOCKCALL_HANDLE call = umockcall_create("test_function", (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);

    // act
    umockcall_destroy(call);

    // assert
    ASSERT_ARE_EQUAL(size_t, 1, test_mock_call_data_free_call_count);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4242, test_mock_call_data_free_calls[0].umockcall_data);
}

/* Tests_SRS_UMOCKCALL_01_005: [ If the umockcall argument is NULL then umockcall_destroy shall do nothing. ]*/
TEST_FUNCTION(umockcall_destroy_with_NULL_argument_does_nothing)
{
    // arrange

    // act
    umockcall_destroy(NULL);

    // assert
    ASSERT_ARE_EQUAL(size_t, 0, test_mock_call_data_free_call_count);
}

/* umockcall_are_equal */

/* Tests_SRS_UMOCKCALL_01_006: [ umockcall_are_equal shall compare the two mock calls and return whether they are equal or not. ] */
/* Tests_SRS_UMOCKCALL_01_024: [ If both left and right pointers are equal, umockcall_are_equal shall return 1. ] */
TEST_FUNCTION(umockcall_are_equal_with_the_same_call_for_both_args_returns_1)
{
    // arrange
    UMOCKCALL_HANDLE call = umockcall_create("test_function", (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);

    // act
    int result = umockcall_are_equal(call, call);

    // assert
    ASSERT_ARE_EQUAL(int, 1, result);
    ASSERT_ARE_EQUAL(int, 0, test_mock_call_data_are_equal_call_count);

    // cleanup
    umockcall_destroy(call);
}

/* Tests_SRS_UMOCKCALL_01_006: [ umockcall_are_equal shall compare the two mock calls and return whether they are equal or not. ] */
/* Tests_SRS_UMOCKCALL_01_027: [ If the underlying umockcall_data_are_equal returns 1, then umockcall_are_equal shall return 1. ]*/
TEST_FUNCTION(umockcall_are_equal_with_2_equal_calls_returns_1)
{
    // arrange
    UMOCKCALL_HANDLE call1 = umockcall_create("test_function", (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);
    UMOCKCALL_HANDLE call2 = umockcall_create("test_function", (void*)0x4243, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);

    // act
    int result = umockcall_are_equal(call1, call2);

    // assert
    ASSERT_ARE_EQUAL(int, 1, result);
    ASSERT_ARE_EQUAL(int, 1, test_mock_call_data_are_equal_call_count);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4242, test_mock_call_data_are_equal_calls[0].left);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4243, test_mock_call_data_are_equal_calls[0].right);

    // cleanup
    umockcall_destroy(call1);
    umockcall_destroy(call2);
}

/* Tests_SRS_UMOCKCALL_01_024: [ If both left and right pointers are equal, umockcall_are_equal shall return 1. ] */
TEST_FUNCTION(when_left_and_right_are_NULL_umockcall_are_equal_returns_1)
{
    // arrange

    // act
    int result = umockcall_are_equal(NULL, NULL);

    // assert
    ASSERT_ARE_EQUAL(int, 1, result);
    ASSERT_ARE_EQUAL(int, 0, test_mock_call_data_are_equal_call_count);
}

/* Tests_SRS_UMOCKCALL_01_015: [ If only one of the left or right arguments are NULL, umockcall_are_equal shall return 0. ] */
TEST_FUNCTION(when_only_left_is_NULL_umockcall_are_equal_returns_0)
{
    // arrange
    UMOCKCALL_HANDLE call = umockcall_create("test_function", (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);

    // act
    int result = umockcall_are_equal(NULL, call);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(int, 0, test_mock_call_data_are_equal_call_count);

    // cleanup
    umockcall_destroy(call);
}

/* Tests_SRS_UMOCKCALL_01_015: [ If only one of the left or right arguments are NULL, umockcall_are_equal shall return 0. ] */
TEST_FUNCTION(when_only_right_is_NULL_umockcall_are_equal_returns_0)
{
    // arrange
    UMOCKCALL_HANDLE call = umockcall_create("test_function", (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);

    // act
    int result = umockcall_are_equal(call, NULL);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(int, 0, test_mock_call_data_are_equal_call_count);

    // cleanup
    umockcall_destroy(call);
}

/* Tests_SRS_UMOCKCALL_01_025: [ If the function name does not match for the 2 calls, umockcall_are_equal shall return 0. ]*/
TEST_FUNCTION(when_the_function_name_does_not_match_then_umockcall_are_equal_returns_0)
{
    // arrange
    UMOCKCALL_HANDLE call1 = umockcall_create("test_function_1", (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);
    UMOCKCALL_HANDLE call2 = umockcall_create("test_function_2", (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);

    test_mock_call_data_are_equal_expected_result = -1;

    // act
    int result = umockcall_are_equal(call1, call2);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(int, 0, test_mock_call_data_are_equal_call_count);

    // cleanup
    umockcall_destroy(call1);
    umockcall_destroy(call2);
}

/* Tests_SRS_UMOCKCALL_01_028: [ If the underlying umockcall_data_are_equal returns 0, then umockcall_are_equal shall return 0. ]*/
TEST_FUNCTION(when_the_underlying_are_equal_returns_0_umockcall_are_equal_returns_0)
{
    // arrange
    UMOCKCALL_HANDLE call1 = umockcall_create("test_function", (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);
    UMOCKCALL_HANDLE call2 = umockcall_create("test_function", (void*)0x4243, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);

    test_mock_call_data_are_equal_expected_result = 0;

    // act
    int result = umockcall_are_equal(call1, call2);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(int, 1, test_mock_call_data_are_equal_call_count);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4242, test_mock_call_data_are_equal_calls[0].left);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4243, test_mock_call_data_are_equal_calls[0].right);

    // cleanup
    umockcall_destroy(call1);
    umockcall_destroy(call2);
}

/* Tests_SRS_UMOCKCALL_01_029: [ If the underlying umockcall_data_are_equal fails (returns anything else than 0 or 1), then umockcall_are_equal shall fail and return -1. ] */
TEST_FUNCTION(when_the_underlying_are_equal_returns_minus_1_umockcall_are_equal_returns_minus_1)
{
    // arrange
    UMOCKCALL_HANDLE call1 = umockcall_create("test_function", (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);
    UMOCKCALL_HANDLE call2 = umockcall_create("test_function", (void*)0x4243, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);

    test_mock_call_data_are_equal_expected_result = -1;

    // act
    int result = umockcall_are_equal(call1, call2);

    // assert
    ASSERT_ARE_EQUAL(int, -1, result);
    ASSERT_ARE_EQUAL(int, 1, test_mock_call_data_are_equal_call_count);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4242, test_mock_call_data_are_equal_calls[0].left);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4243, test_mock_call_data_are_equal_calls[0].right);

    // cleanup
    umockcall_destroy(call1);
    umockcall_destroy(call2);
}

/* Tests_SRS_UMOCKCALL_01_029: [ If the underlying umockcall_data_are_equal fails (returns anything else than 0 or 1), then umockcall_are_equal shall fail and return -1. ] */
TEST_FUNCTION(when_the_underlying_are_equal_returns_2_umockcall_are_equal_returns_minus_1)
{
    // arrange
    UMOCKCALL_HANDLE call1 = umockcall_create("test_function", (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);
    UMOCKCALL_HANDLE call2 = umockcall_create("test_function", (void*)0x4243, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);

    test_mock_call_data_are_equal_expected_result = 2;

    // act
    int result = umockcall_are_equal(call1, call2);

    // assert
    ASSERT_ARE_EQUAL(int, -1, result);
    ASSERT_ARE_EQUAL(int, 1, test_mock_call_data_are_equal_call_count);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4242, test_mock_call_data_are_equal_calls[0].left);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4243, test_mock_call_data_are_equal_calls[0].right);

    // cleanup
    umockcall_destroy(call1);
    umockcall_destroy(call2);
}

/* Tests_SRS_UMOCKCALL_01_014: [ If the two calls have different are_equal functions that have been passed to umockcall_create then the calls shall be considered different and 0 shall be returned. ] */
TEST_FUNCTION(when_the_are_equal_function_pointers_are_different_umockcall_are_equal_returns_0)
{
    // arrange
    UMOCKCALL_HANDLE call1 = umockcall_create("test_function", (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);
    UMOCKCALL_HANDLE call2 = umockcall_create("test_function", (void*)0x4243, test_mock_call_data_free, test_mock_call_data_stringify, another_test_mock_call_data_are_equal);

    test_mock_call_data_are_equal_expected_result = 2;

    // act
    int result = umockcall_are_equal(call1, call2);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(int, 0, test_mock_call_data_are_equal_call_count);

    // cleanup
    umockcall_destroy(call1);
    umockcall_destroy(call2);
}

/* umockcall_stringify */

/* Tests_SRS_UMOCKCALL_01_016: [ umockcall_stringify shall return a string representation of the mock call in the form \[function_name(arguments)\]. ] */
/* Tests_SRS_UMOCKCALL_01_018: [ The returned string shall be a newly allocated string and it is to be freed by the caller. ]*/
/* Tests_SRS_UMOCKCALL_01_019: [ To obtain the arguments string, umockcall_stringify shall call the umockcall_data_stringify function passed to umockcall_create and pass to it the umock call data pointer (also given in umockcall_create). ]*/
TEST_FUNCTION(umockcall_stringify_calls_the_underlying_stringify_function_and_returns_the_strinfigied_call)
{
    // arrange
    UMOCKCALL_HANDLE call = umockcall_create("test_function", (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);

    test_mock_call_data_stringify_expected_result = (char*)malloc(1);
    test_mock_call_data_stringify_expected_result[0] = '\0';

    // act
    char* result = umockcall_stringify(call);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "[test_function()]", result);
    ASSERT_ARE_EQUAL(int, 1, test_mock_call_data_stringify_call_count);

    // cleanup
    free(result);
    umockcall_destroy(call);
}

/* Tests_SRS_UMOCKCALL_01_016: [ umockcall_stringify shall return a string representation of the mock call in the form \[function_name(arguments)\]. ] */
/* Tests_SRS_UMOCKCALL_01_018: [ The returned string shall be a newly allocated string and it is to be freed by the caller. ]*/
/* Tests_SRS_UMOCKCALL_01_019: [ To obtain the arguments string, umockcall_stringify shall call the umockcall_data_stringify function passed to umockcall_create and pass to it the umock call data pointer (also given in umockcall_create). ]*/
TEST_FUNCTION(umockcall_stringify_uses_the_stringified_args_as_obtained_from_the_underlying_stringify_function)
{
    // arrange
    UMOCKCALL_HANDLE call = umockcall_create("test_function", (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);

    test_mock_call_data_stringify_expected_result = (char*)malloc(strlen("45") + 1);
    (void)strcpy(test_mock_call_data_stringify_expected_result, "45");

    // act
    char* result = umockcall_stringify(call);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "[test_function(45)]", result);
    ASSERT_ARE_EQUAL(int, 1, test_mock_call_data_stringify_call_count);

    // cleanup
    free(result);
    umockcall_destroy(call);
}

/* Tests_SRS_UMOCKCALL_01_017: [ If the umockcall argument is NULL, umockcall_stringify shall return NULL. ] */
TEST_FUNCTION(umockcall_stringify_with_NULL_fails_and_returns_NULL)
{
    // arrange

    // act
    char* result = umockcall_stringify(NULL);

    // assert
    ASSERT_IS_NULL(result);
}

/* Tests_SRS_UMOCKCALL_01_020: [ If the underlying umockcall_data_stringify call fails, umockcall_stringify shall fail and return NULL. ]*/
TEST_FUNCTION(when_the_underlying_stringify_fails_then_umockcall_stringify_calls_fails)
{
    // arrange
    UMOCKCALL_HANDLE call = umockcall_create("test_function", (void*)0x4242, test_mock_call_data_free, test_mock_call_data_stringify, test_mock_call_data_are_equal);

    test_mock_call_data_stringify_expected_result = NULL;

    // act
    char* result = umockcall_stringify(call);

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(int, 1, test_mock_call_data_stringify_call_count);

    // cleanup
    umockcall_destroy(call);
}

END_TEST_SUITE(umockcall_unittests)