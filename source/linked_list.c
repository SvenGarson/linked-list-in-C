#include "..\include\linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Private helper functions */
static linked_list_node_ts * create_node_for_key(const char * p_new_key)
{
	if (p_new_key == NULL)
	{
		return NULL;
	}

	const int actual_key_length = strlen(p_new_key);
	if (actual_key_length < 1)
	{
		return NULL;
	}

	/* Key is long enough - Allocate the node */
	linked_list_node_ts * p_new_node = malloc(sizeof(linked_list_node_ts));
	if (p_new_node == NULL)
	{
		return NULL;
	}

	/* Allocated node successfully - Now allocate the node key */
	const int total_key_length = actual_key_length + 1;
	p_new_node->p_key = malloc(sizeof(char) * actual_key_length);
	if (p_new_node->p_key == NULL)
	{
		free(p_new_node);
		return NULL;
	}

	/* Initialize the node and return successfully */
	p_new_node->p_next = NULL;
	strncpy(p_new_node->p_key, p_new_key, total_key_length);
	return p_new_node;
}

static void delete_node(linked_list_node_ts * p_node_to_delete)
{
	if (p_node_to_delete == NULL)
		return;

	free(p_node_to_delete->p_key);
	free(p_node_to_delete);
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
	p_new_lili->size = 0;
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

	/* Clear all nodes */
	linked_list_clear(p_lili);

	/* Deallocate linked list instance - Do not use instance after destroyal */
	free(p_lili);
}

/* Interface function definitions - Debugging */
void linked_list_visualize(const linked_list_instance_ts * p_lili, const char * p_tag)
{
	/* Print the contents of the linked list nodes from head to tail */
	if (p_lili == NULL || p_lili->p_head == NULL)
	{
		printf("\n\nNo data to display for linked list tagged '%s' head: %p size: %d", p_tag ? p_tag : "N/A", p_lili->p_head, p_lili->size);
		return;
	}

	printf("\n\nVisualizing nodes for linked list tagged '%s' head: %p size: %d", p_tag ? p_tag : "N/A", p_lili->p_head ,p_lili->size);
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
linked_list_bool_te linked_list_insert(
	linked_list_instance_ts * p_lili,
	const char * p_insertion_key
)
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
	p_lili->size++;
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

/* Interface function definitions - Deletion */
linked_list_bool_te linked_list_delete(
	linked_list_instance_ts * p_lili,
	const char * p_deletion_key
)
{
	if (p_lili == NULL || p_deletion_key == NULL)
	{
		return LINKED_LIST_FALSE;
	}

	/* Delete the node when it exists by key string */
	linked_list_node_ts * p_search_node_parent = NULL;
	linked_list_node_ts * p_search_node = p_lili->p_head;
	while (p_search_node)
	{
		if (strcmp(p_search_node->p_key, p_deletion_key) == 0)
		{
			/* Found a matching node to delete - Delete it and do the housekeeping */
			if (p_search_node_parent == NULL)
			{
				p_lili->p_head = p_search_node->p_next;
			}
			else
			{
				p_search_node_parent->p_next = p_search_node->p_next;
			}

			p_lili->size--;
			delete_node(p_search_node);
			return LINKED_LIST_TRUE;
		}

		/* Go to the next node in the sequence */
		p_search_node_parent = p_search_node;
		p_search_node = p_search_node->p_next;
	}

	/* No node deleted */
	return LINKED_LIST_FALSE;
}

void linked_list_clear(linked_list_instance_ts * p_lili)
{
	if (p_lili == NULL || p_lili->p_head == NULL)
	{
		return;
	}

	/* Deallocate all nodes in sequence */
	linked_list_node_ts * p_deletion_node = p_lili->p_head;
	while (p_deletion_node != NULL)
	{
		linked_list_node_ts * p_next_deletion_node = p_deletion_node->p_next;
		delete_node(p_deletion_node);
		p_deletion_node = p_next_deletion_node;
	}

	p_lili->size = 0;
	p_lili->p_head = NULL;
}

/* Interface function definitions - Utility */
linked_list_bool_te linked_list_has_key(
	linked_list_instance_ts * p_lili,
	const char * p_search_key
)
{
	if (p_lili == NULL || p_lili->p_head == NULL)
	{
		return LINKED_LIST_FALSE;
	}

	/* Determines whether the provided key was previously added to the linked list */
	linked_list_node_ts * p_search_node;
	for (p_search_node = p_lili->p_head; p_search_node; p_search_node = p_search_node->p_next)
	{
		if (strcmp(p_search_node->p_key, p_search_key) == 0)
		{
			return LINKED_LIST_TRUE;
		}
	}

	/* No node with the provided key was found */
	return LINKED_LIST_FALSE;
}

int linked_list_size(const linked_list_instance_ts * p_lili)
{
	/* Count when adding and deleting nodes in the linked list struct */
	return (p_lili != NULL) ? p_lili->size : 0;
}

/* Interface function definitions - Traversal */
void linked_list_traverse_in_order(
	const linked_list_instance_ts * p_lili,
	linked_list_traversal_callback_t p_traversal_callback
)
{
	if (p_lili == NULL || p_lili->p_head == NULL)
	{
		return;
	}

	/* Invoke the callback for every linked list node in sequence */
	const linked_list_node_ts * p_traversed_node;
	int node_index = 1;
	for (p_traversed_node = p_lili->p_head; p_traversed_node; p_traversed_node = p_traversed_node->p_next)
	{
		p_traversal_callback(node_index++, p_traversed_node->p_key);
	}
}

/* Interface function definitions - Sorting */
void linked_list_reverse_in_place(linked_list_instance_ts * p_lili)
{
	if (p_lili == NULL || p_lili->p_head == NULL)
	{
		return;
	}

	/* Reverse the linked list entries in place */
	linked_list_node_ts * p_previous_node = NULL;
	linked_list_node_ts * p_current_node = p_lili->p_head;
	while (p_current_node)
	{
		linked_list_node_ts * const p_next_node = p_current_node->p_next;

		p_lili->p_head = p_current_node;
		p_current_node->p_next = p_previous_node;

		p_previous_node = p_current_node;
		p_current_node = p_next_node;
	}
}