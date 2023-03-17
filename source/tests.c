#include <stdio.h>
#include <string.h>
#include "..\include\linked_list.h"

/* Defines */
#define MAX_TEST_RESULTS (64)
#define MAX_TEST_RESULT_DESCRIPTION_LENGTH (80)

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

	const int total_description_length = strlen(p_description) + 1;
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
			"\n\t[%-3d] %-80s %-s",
			result_index + 1,
			p_current_results->description,
			p_current_results->success ? "Success" : "Failure"
		);
	}
	printf("\n\nFinal result: %s", all_tests_succeeded ? "All tests succeeded" : "Not all tests succeeded");
	printf("\n\n");
}

test_bool_te test_that_linked_list_has_all_entries(const linked_list_instance_ts * p_lili, const char * expected_keys[], int expected_entries)
{
	/* When no entries given, the linked list must also be empty */
	if (expected_entries == 0 && linked_list_size(p_lili) == 0)
		return TEST_TRUE;

	/* Number of entries must match */
	if (linked_list_size(p_lili) != expected_entries)
		return TEST_FALSE;

	/* Check if every expected key is in the node list */
	for (int expected_index = 0; expected_index < expected_entries; expected_index++)
	{
		const char * p_current_expected_key = expected_keys[expected_index];
		int matching_occurrences = 0;

		/* Check every linked list node */
		linked_list_node_ts * p_node = NULL;
		for (p_node = p_lili->p_head; p_node; p_node = p_node->p_next)
		{
			if (strcmp(p_current_expected_key, p_node->p_key) == 0)
			{
				matching_occurrences++;
			}
		}

		if (matching_occurrences != 1)
			return TEST_FALSE;
	}

	/* All entries were found */
	return TEST_TRUE;
}

test_bool_te test_that_linked_list_has_all_entries_in_order(const linked_list_instance_ts * p_lili, const char * expected_keys[], int expected_entries)
{
	if (expected_entries != linked_list_size(p_lili))
		return TEST_FALSE;

	linked_list_node_ts * p_node = p_lili->p_head;
	for (int expected_index = 0; expected_index < expected_entries; expected_index++)
	{
		/* Fail on any mismatch */
		if (p_node == NULL || strcmp(p_node->p_key, expected_keys[expected_index]) != 0)
		{
			/* Found a mismatch in terms of the key in the order given */
			return TEST_FALSE;
		}

		/* To the next node for every matching entry */
		p_node = p_node->p_next;
	}

	/* All entries matched in order and number of entries */
	return TEST_TRUE;
}

/* Test entry point */
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

	/* Linked list tracks size properly - Insert; Delete & Clear*/
	p_lili = linked_list_create();
	linked_list_insert(p_lili, "Dog");
	test_results_add(&test_results, "Test that linked list tracks size when adding the first entry", linked_list_size(p_lili) == 1);

	linked_list_insert(p_lili, "Cat");
	linked_list_insert(p_lili, "Horse");
	linked_list_insert(p_lili, "Spider");
	test_results_add(&test_results, "Test that linked list tracks size when adding subsequent entries", linked_list_size(p_lili) == 4);

	linked_list_delete(p_lili, "Cat");
	test_results_add(&test_results, "Test that linked list tracks size when deleting subsequent entries", linked_list_size(p_lili) == 3);

	linked_list_delete(p_lili, "Horse");
	linked_list_delete(p_lili, "Spider");
	linked_list_delete(p_lili, "Dog");
	test_results_add(&test_results, "Test that linked list tracks size when deleting all entries manually", linked_list_size(p_lili) == 0);

	linked_list_insert(p_lili, "Iron Man");
	linked_list_insert(p_lili, "Waterdude");
	linked_list_insert(p_lili, "Antboy");
	test_results_add(&test_results, "Test that linked list tracks size when adding entries after manual clearing", linked_list_size(p_lili) == 3);	

	linked_list_clear(p_lili);
	test_results_add(&test_results, "Test that linked list tracks size when cleared", linked_list_size(p_lili) == 0);	
	linked_list_destroy(p_lili);

	/* Linked list tracks entries properly */
	p_lili = linked_list_create();

	test_results_add(
		&test_results,
		"Test that linked list is empty when created",
		test_that_linked_list_has_all_entries(p_lili, NULL, 0)
	);	

	linked_list_insert(p_lili, "Head");
	const char * expected_lili_keys_a[] = { "Head" };
	test_results_add(
		&test_results,
		"Test that linked list tracks entries when first added",
		test_that_linked_list_has_all_entries(p_lili, expected_lili_keys_a, sizeof(expected_lili_keys_a) / sizeof(char *))
	);	

	linked_list_insert(p_lili, "Feet");
	linked_list_insert(p_lili, "Arms");
	linked_list_insert(p_lili, "Hands");
	const char * expected_lili_keys_b[] = { "Head", "Feet", "Arms", "Hands"};
	test_results_add(
		&test_results,
		"Test that linked list tracks entries when subsequent added",
		test_that_linked_list_has_all_entries(p_lili, expected_lili_keys_b, sizeof(expected_lili_keys_b) / sizeof(char *))
	);	

	linked_list_delete(p_lili, "Feet");
	linked_list_delete(p_lili, "Arms");
	linked_list_delete(p_lili, "Hands");
	const char * expected_lili_keys_c[] = { "Head" };
	test_results_add(
		&test_results,
		"Test that linked list tracks entries when subsequent deleted",
		test_that_linked_list_has_all_entries(p_lili, expected_lili_keys_c, sizeof(expected_lili_keys_c) / sizeof(char *))
	);	

	linked_list_delete(p_lili, "Head");
	test_results_add(
		&test_results,
		"Test that linked list tracks entries when first added",
		test_that_linked_list_has_all_entries(p_lili, NULL, 0)
	);	

	linked_list_insert(p_lili, "Ring");
	linked_list_insert(p_lili, "Paper");
	linked_list_insert(p_lili, "Heavy Stone");
	const char * expected_lili_keys_d[] = { "Ring", "Paper", "Heavy Stone"};
	test_results_add(
		&test_results,
		"Test that linked list tracks entries when re-populating after manual clearing",
		test_that_linked_list_has_all_entries(p_lili, expected_lili_keys_d, sizeof(expected_lili_keys_d) / sizeof(char *))
	);

	linked_list_clear(p_lili);
	test_results_add(
		&test_results,
		"Test that linked list is empty after clearing",
		test_that_linked_list_has_all_entries(p_lili, NULL, 0)
	);	

	linked_list_destroy(p_lili);

	/* Linked list interface success and failure */
	p_lili = linked_list_create();

	linked_list_insert(p_lili, "Homer Simpson");
	test_results_add( &test_results, "Test that inserting a duplicate key returns failure", !linked_list_insert(p_lili, "Homer Simpson"));
	const char * expected_lili_keys_e[] = { "Homer Simpson" };
	test_results_add(
		&test_results,
		"Test that inserting a duplicate key does not actually add an entry",
		test_that_linked_list_has_all_entries(p_lili, expected_lili_keys_e, sizeof(expected_lili_keys_e) / sizeof(char *))
	);

	linked_list_clear(p_lili);
	linked_list_insert(p_lili, "Maggy");
	linked_list_insert(p_lili, "Bart");
	linked_list_insert(p_lili, "Lisa");
	test_results_add( &test_results, "Test that deleting a non-existen key returns failure", !linked_list_delete(p_lili, "Homer"));
	const char * expected_lili_keys_f[] = { "Maggy", "Lisa", "Bart" };
	test_results_add(
		&test_results,
		"Test that deleting a non-existent key does not remove any nodes",
		test_that_linked_list_has_all_entries(p_lili, expected_lili_keys_f, sizeof(expected_lili_keys_f) / sizeof(char *))
	);

	linked_list_destroy(p_lili);

	/* Linked list reports whether it contains a key properly */
	p_lili = linked_list_create();

	linked_list_insert(p_lili, "Green");
	linked_list_insert(p_lili, "Magenta");
	linked_list_insert(p_lili, "Blue");
	linked_list_insert(p_lili, "Orange");
	test_results_add( &test_results, "Test that linked list reports non-existant key when list is not empty", !linked_list_has_key(p_lili, "Golden"));
	test_results_add( &test_results, "Test that linked list reports existant key", linked_list_has_key(p_lili, "Magenta"));
	linked_list_clear(p_lili);
	test_results_add( &test_results, "Test that linked list reports non-existant key when list is indeed empty", !linked_list_has_key(p_lili, "Black"));

	linked_list_destroy(p_lili);

	/* Linked list contains nodes in the entered order */
	p_lili = linked_list_create();

	linked_list_insert(p_lili, "A");
	linked_list_insert(p_lili, "Z");
	linked_list_insert(p_lili, "F");
	linked_list_insert(p_lili, "G");
	linked_list_insert(p_lili, "V");
	linked_list_insert(p_lili, "B");

	const char * expected_lili_keys_g[] = { "A", "Z", "F", "G", "V", "B" };
	test_results_add(
		&test_results,
		"Test that non-empty linked list contains nodes in the inserted order",
		test_that_linked_list_has_all_entries_in_order(p_lili, expected_lili_keys_g, sizeof(expected_lili_keys_g) / sizeof(char *))
	);

	linked_list_destroy(p_lili);

	/* Execute test suites */
	test_results_visualize(test_results);

	/* Return to OS successfully */
	return 0;
}