#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* Datatypes */
typedef enum {
	LINKED_LIST_FALSE = 0,
	LINKED_LIST_TRUE  = 1
} linked_list_bool_te;

typedef struct linked_list_node {
	char * p_key;
	struct linked_list_node * p_next;
} linked_list_node_ts;

typedef struct {
	int size;
	linked_list_node_ts * p_head;
} linked_list_instance_ts;

typedef void (* linked_list_traversal_callback_t)(
	int node_index,
	const char * const p_traversed_key
);

/* Interface function prototypes - Creation */
linked_list_instance_ts * linked_list_create(void);

/* Interface function prototypes - Destroyal */
void linked_list_destroy(linked_list_instance_ts * p_lili);

/* Interface function prototypes - Debugging */
void linked_list_visualize(const linked_list_instance_ts * p_lili, const char * p_tag);

/* Interface function prototypes - Insertion */
linked_list_bool_te linked_list_insert(
	linked_list_instance_ts * p_lili,
	const char * p_insertion_key
);

/* Interface function prototypes - Deletion */
linked_list_bool_te linked_list_delete(
	linked_list_instance_ts * p_lili,
	const char * p_deletion_key
);
void linked_list_clear(linked_list_instance_ts * p_lili);

/* Interface function prototypes - Utility */
linked_list_bool_te linked_list_has_key(
	linked_list_instance_ts * p_lili,
	const char * p_search_key
);
int linked_list_size(const linked_list_instance_ts * p_lili);

/* Interface function prototypes - Traversal */
void linked_list_traverse_in_order(
	const linked_list_instance_ts * p_lili,
	linked_list_traversal_callback_t p_traversal_callback
);

/* Interface function prototypes - Sorting */
void linked_list_reverse_in_place(linked_list_instance_ts * p_lili);

#endif