#include <stdio.h>
#include <string.h>
#include "..\include\linked_list.h"

/* Defines */
#define MAX_TEST_RESULTS (64)
#define MAX_TEST_RESULT_DESCRIPTION_LENGTH (60)

/* Datatypes */
typedef enum {
	TEST_FALSE = 0,
	TEST_TRUE  = 1
} test_bool_te;

typedef struct {
	char description[MAX_TEST_RESULT_DESCRIPTION_LENGTH];
	int success;
} test_result_with_description_ts;

typedef struct {
	int size;
	test_result_with_description_ts test_results[MAX_TEST_RESULTS];
} test_results_ts;

/* Helper function definitions */
test_results_ts test_results_create(void)
{
	test_results_ts new_test_results;
	new_test_results.size = 0;
	return new_test_results;
}

int test_results_add(test_results_ts * p_results, const char * p_description, int result)
{
	if (p_results->size >= MAX_TEST_RESULTS || p_description == NULL)
	{
		return TEST_FALSE;
	}

	const int total_description_length = strlen(p_description);
	if (total_description_length >= MAX_TEST_RESULT_DESCRIPTION_LENGTH)
	{
		printf("\nCould not add new test result because the description is too long");
		return TEST_FALSE;
	}

	/* Add the new test results */
	test_result_with_description_ts * const p_new_result = p_results->test_results + p_results->size++;
	p_new_result->success = result;
	strncpy(p_new_result->description, p_description, total_description_length);
	return TEST_TRUE;
}

void test_results_visualize(test_results_ts results)
{
	printf("\n\nShowing test result based on '%d' entries:", results.size);
	int all_tests_succeeded = TEST_TRUE;
	for (int result_index = 0; result_index < results.size; result_index++)
	{
		test_result_with_description_ts * p_current_results = results.test_results + result_index;
		if (!p_current_results->success) all_tests_succeeded = TEST_FALSE;
		printf(
			"\n\t[%-3d] %-60s %-s",
			result_index,
			p_current_results->description,
			p_current_results->success ? "Success" : "Failure"
		);
	}
	printf("\n\nFinal result: %s", all_tests_succeeded ? "All tests succeeded" : "Not all tests succeeded");
	printf("\n\n");
}

int main(void)
{
	/* Initialize testing resources */
	test_results_ts test_results = test_results_create(); 

	/* Creation and initialization */
	linked_list_instance_ts * p_lili = linked_list_create();
	test_results_add(&test_results, "Test that linked_list_create initializes pointer", p_lili != NULL);
	test_results_add(&test_results, "Test that linked_list_create initializes head to NULL", p_lili->p_head == NULL);
	test_results_add(&test_results, "Test that linked_list_create initializes size to zero", p_lili->size == 0);
	linked_list_destroy(p_lili);

	/* Destroyal */
	/* Missing test state setup */
	test_results_add(&test_results, "Test that linked_list_destroy sets head to NULL", p_lili->p_head == NULL);

	/* Execute test suites */
	test_results_visualize(test_results);

	/* Return to OS successfully */
	return 0;
}