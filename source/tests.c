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
	linked_list_insert(p_lili, "Sausia");
	linked_list_insert(p_lili, "Rex III");

	linked_list_visualize(p_lili, "Meep");

	linked_list_destroy(p_lili);
	printf("\n\n===========================END==========================");

	/* Return to OS successfully */
	return 0;
}