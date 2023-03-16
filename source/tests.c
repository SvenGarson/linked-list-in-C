#include <stdio.h>
#include "..\include\linked_list.h"

int main(void)
{
	printf("\n\n==========================BEGIN==========================");
	/* Test the linked list interface */
	linked_list_instance_ts * p_lili = linked_list_create();

	/* Checking */
	printf(
		"\nInitialization: %s",
		(p_lili != NULL && p_lili->p_head == NULL) ? "Success" : "Failure"
	);

	linked_list_insert(p_lili, "Wolfiecomballa");
	linked_list_insert(p_lili, "Sausia");
	linked_list_insert(p_lili, "Rex");
	linked_list_insert(p_lili, "Rex III");

	linked_list_visualize(p_lili, "Before deletion");

	linked_list_delete(p_lili, "Milky");
	linked_list_delete(p_lili, "way");
	linked_list_delete(p_lili, "Rex III");
	linked_list_delete(p_lili, "Rudolf I");

	linked_list_visualize(p_lili, "After deletion");

	linked_list_delete(p_lili, "Wolfiecomballa");
	linked_list_delete(p_lili, "Sausia");
	linked_list_delete(p_lili, "Rex");
	linked_list_visualize(p_lili, "After manual clearing");

	linked_list_insert(p_lili, "Angus");
	linked_list_insert(p_lili, "Bazzinga");
	linked_list_insert(p_lili, "Ken");
	linked_list_visualize(p_lili, "New entries");

	linked_list_clear(p_lili);
	linked_list_visualize(p_lili, "After interface clearing");

	linked_list_insert(p_lili, "Amanita");
	linked_list_insert(p_lili, "Puff");
	linked_list_insert(p_lili, "Muscarius");
	linked_list_visualize(p_lili, "New entries for searching");

	const char * search_keys[] = { "Amani", "Puff", "Muscarius", "Amanita", "Lollita"};
	putchar('\n');
	for (int srch_index = 0; srch_index < (int)(sizeof(search_keys) / sizeof(char *)); srch_index++)
	{
		const char * p_search_key = search_keys[srch_index];
		linked_list_bool_te found = linked_list_has_key(p_lili, p_search_key);
		printf("\nSearch key: %-30s Found: %s", p_search_key, found ? "True" : "False");
	}

	linked_list_destroy(p_lili);
	printf("\n\n===========================END==========================");

	/* Return to OS successfully */
	return 0;
}