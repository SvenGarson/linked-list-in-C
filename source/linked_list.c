#include "..\include\linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Private helper functions */
linked_list_node_ts * create_node_for_key(const char * p_new_key)
{
	if (p_new_key == NULL)
	{
		return NULL;
	}

	const int actual_key_length = strlen(p_new_key);
	if (actual_key_length < 1)
	{
		printf("\nCould not creat new node because the key string is empty");
		return NULL;
	}

	/* Key is long enough - Allocate the node */
	linked_list_node_ts * p_new_node = malloc(sizeof(linked_list_node_ts));
	if (p_new_node == NULL)
	{
		printf("\nCould not allocate memory for new node with key '%s'", p_new_key);
		return NULL;
	}

	/* Allocated node successfully - Now allocate the node key */
	const int total_key_length = actual_key_length + 1;
	p_new_node->p_key = malloc(sizeof(char) * actual_key_length);
	if (p_new_node->p_key == NULL)
	{
		printf(
			"\nCould not allocate memory for new node key '%s' (%d)",
			p_new_key,
			actual_key_length
		);

		free(p_new_node);
		return NULL;
	}

	/* Initialize the node and return successfully */
	p_new_node->p_next = NULL;
	strncpy(p_new_node->p_key, p_new_key, total_key_length);
	return p_new_node;
}

/* Interface function definitions - Creation */
linked_list_instance_ts * linked_list_create(void)
{
	linked_list_instance_ts * p_new_lili = malloc(sizeof(linked_list_instance_ts));
	if (p_new_lili == NULL)
	{
		return NULL;
	}

	/* Initialize the linked list instance */
	p_new_lili->p_head = NULL;
	return p_new_lili;
}

/* Interface function definitions - Destroyal */
void linked_list_destroy(linked_list_instance_ts * p_lili)
{
	if (p_lili == NULL)
	{
		return;
	}

	/* TODO-GS: Deallocat all node memory allocations */

	/* Deallocate linked list instance */
	free(p_lili);
}

/* Interface function definitions - Debugging */
void linked_list_visualize(linked_list_instance_ts * p_lili, const char * p_tag)
{
	/* Print the contents of the linked list nodes from head to tail */
	if (p_lili == NULL || p_lili->p_head == NULL)
	{
		printf("\nNo data to display for linked list tagged '%s'", p_tag ? p_tag : "N/A");
		return;
	}

	printf("\nVisualizing nodes for linked list tagged '%s':", p_tag ? p_tag : "N/A");
	printf("\n\t%-10s | %-30s", "Index", " Key");
	printf("\n\t%-10s-+-%-30s", "----------", "--------------------");
	linked_list_node_ts * p_visual_node;
	int node_index = 1;
	for (p_visual_node = p_lili->p_head; p_visual_node != NULL; p_visual_node = p_visual_node->p_next)
	{
		printf("\n\t%-10d | %-30s", node_index++, p_visual_node->p_key);
	}
}

/* Interface function definitions - Insertion */
linked_list_bool_te linked_list_insert(linked_list_instance_ts * p_lili, const char * p_insertion_key)
{
	if (p_lili == NULL || p_insertion_key == NULL)
	{
		return LINKED_LIST_FALSE;
	}

	/* Append new node with key when the key does not yet exist in the linked list */
	linked_list_node_ts * p_search_node_parent = NULL;
	linked_list_node_ts * p_search_node = p_lili->p_head;
	while (p_search_node)
	{
		/* Check for collision */
		if (strcmp(p_search_node->p_key, p_insertion_key) == 0)
		{
			printf("\nFailed to insert key '%s' because it already exists", p_insertion_key);
			return LINKED_LIST_FALSE;
		}

		/* Go to the next node in the sequence */
		p_search_node_parent = p_search_node;
		p_search_node = p_search_node->p_next;
	}

	/* No collision occured - Append new node to the linked list */
	linked_list_node_ts * p_new_node = create_node_for_key(p_insertion_key);
	if (p_new_node == NULL)
	{
		return LINKED_LIST_FALSE;
	}

	/* Success */
	if (p_search_node_parent == NULL)
	{
		/* List currently empty */
		p_lili->p_head = p_new_node;
	}
	else
	{
		/* Append to some subsequent node */
		p_search_node_parent->p_next = p_new_node;
	}
	
	return LINKED_LIST_TRUE;
}