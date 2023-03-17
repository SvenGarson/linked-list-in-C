# linked-list-in-C
A minimal implementation of a singly-linked list in C to understand this data structure and the C language better. The focus here was the execution of implementing the data structure and roughly testing it as fast as possible.

The implementation could be DRYed up quite a bit to remove redundant bits of code into utility functions, but I chose to experiment with different, more or less idiomatic approaches of implementing things, rather than spending too much time on abstractions.

## Disclaimer
This is an exercise project and definitely not something you should use anywhere without modification as there may be subtle bugs for edge-cases that were not considered nor tested for.

This project was build on Windows using `Mingw32` and the `gcc` compiler.

## Problems
This section contains a list of problems or not-so-great things in terms of the implement and interface

- **The state of the interface data types is transparent**
  i.e. the user can access all the state exactly as the implementation can. The goal was not to develop a fully opaque library, so the interface was left open in terms of header-level implementation details
- **Destroying a linked list does not protect the user from accessing the deallocated linked list**
  When the linked list is destroyed, the pointer to the old linked list memory location persists in the user code. There should be some sort of abstraction to protect the user from invalid operation on a destroyed linked list.
  
  A simple solution would be to require the pointer to the linked list instance so the instance can be deallocated and set to null without involving other user-code

## Running the tests

The tests do not fully cover all the edge-cases, and can be executed by compiling and executing the `tests.c` source file in the `source` directory as the entry point. The `Makefile` contains the following targets:

- `compile` to compile the source code
- `compile_and_run_tests` to both compile and execute the tests


## Documentation
The following functions are available by including the `linked_list.h` header into the source file found in the `include` directory.

### Naming conventions

#### Prefixes

- `p_` represents a pointer of some sort

#### Suffixes

- `_te` stands for `typedef enum`
- `_ts` stands for `typedef struct`
- `_t` stands for some other, more general `typedef`

### Relevant data types

- `linked_list_bool_te`

  A typedef, enum integer type used by the implementation to represent:

  - Boolean true as `LINKED_LIST_TRUE`
  - Boolean false as `LINKED_LIST_FALSE`

  This integer value can be used in conditionals without explicitly comparing against the enum integers as the integer values match C's truthy and falsy model where:

  - `NULL` or `0` is falsy
  - any other value is truthy

- `linked_list_instance_ts`

  A struct that hold the reference to the linked list head and node count, which all interface functions are based on
  
- `linked_list_traversal_callback_t`

  A typedef pointer to a function which:

  - Has parameters

    - `int node_index`

      The index of the node being traversed, starting at `1`

    - `const char * const p_traversed_key`

      Pointer to the null-terminated key string of the node being traversed

  - Returns `void`

### Interface functions

- **`linked_list_create`**

  - **Description**

    Allocates and initializes a new linked list instance

  - **Signature**

    ```c
    linked_list_instance_ts * linked_list_create(void)
    ```

  - **Parameters**

    None

  - **Return value**

    - `NULL` when a linked list instance cannot be allocated
    - Pointer to a new instance of `linked_list_instance_ts` when the linked list was allocated successfully

- **`linked_list_destroy`**

  - **Description**

    Deallocates all nodes in the linked list and the linked list itself

  - **Signature**

    ```c
    void linked_list_destroy(linked_list_instance_ts * p_lili)
    ```

  - **Parameters**

    1. `linked_list_instance_ts * p_lili`

       Pointer to the linked list to be destroyed

  - **Return value**

    None

- **`linked_list_visualize`**

  - **Description**

    Print the contents of the linked list to `stdout`

  - **Signature**

    ```c
    void linked_list_visualize(const linked_list_instance_ts * p_lili, const char * p_tag)
    ```

  - **Parameters**

    1. `const linked_list_instance_ts * p_lili`

       Pointer to the linked list to be visualized in `stdout`

    2. `const char * p_tag`

       Pointer to a null-terminated string that is to describe the output in `stdout` before printing the linked list contents

  - **Return value**

    None

- **`linked_list_insert`**

  - **Description**

    Insert new node into the linked list with the specified string value

  - **Signature**

    ```c
    linked_list_bool_te linked_list_insert(
        linked_list_instance_ts * p_lili,
        const char * p_insertion_key
    )
    ```

  - **Parameters**

    1. `linked_list_instance_ts * p_lili`

       Pointer to the linked list to add a new node to

    2. `const char * p_insertion_key`

       Pointer to a null-terminated string that is to be inserted into the new linked list node

  - **Return value**

    - `LINKED_LIST_TRUE` when a new node was inserted successfully for `p_insertion_key`
    - `LINKED_LIST_FALSE` when the linked list already contains a node with the corresponding `p_insertion_key`

- **`linked_list_delete`**

  - **Description**

    Delete existing node with the specified string value from the linked list

  - **Signature**

    ```c
    linked_list_bool_te linked_list_delete(
        linked_list_instance_ts * p_lili,
        const char * p_deletion_key
    )
    ```
  
  - **Parameters**
  
    1. `linked_list_instance_ts * p_lili`
  
       Pointer to the linked list to delete node from
  
    2. `const char * p_deletion_key`
  
       Pointer to a null-terminated string that is to be deleted from the linked list
  
  - **Return value**
  
    - `LINKED_LIST_TRUE` when an existing node with the corresponding string `p_deletion_key` was successfully deleted
    - `LINKED_LIST_FALSE` when the linked list does not contain a node with the string `p_deletion_key`
  
- **`linked_list_has_key`**

  - **Description**

    Query whether the linked list contains a node with the given key

  - **Signature**

    ```c
    linked_list_bool_te linked_list_has_key(
        linked_list_instance_ts * p_lili,
        const char * p_search_key
    )
    ```
  
  - **Parameters**
  
    1. `linked_list_instance_ts * p_lili`
  
       Pointer to the linked list to check the existence of the provided key in
  
    2. `const char * p_search_key`
  
       Pointer to a null-terminated string the linked list is checked for
  
  - **Return value**
  
    - `LINKED_LIST_TRUE` when an existing node contains the corresponding `p_search_key` 
    - `LINKED_LIST_FALSE` when the linked list does not contain a node with the corresponding `p_search_key`
  
- **`linked_list_size`**

  - **Description**

    Return the number of entries currently associated to the linked list

  - **Signature**

    ```c
    int linked_list_size(const linked_list_instance_ts * p_lili)
    ```

  - **Parameters**

    1. `const linked_list_instance_ts * p_lili`

       Pointer to the linked list to query the size from
  
  - **Return value**
  
    - Non-negative `int` that represents the number of nodes associated to the linked list
  
- **`linked_list_traverse_in_order`**

  - **Description**

    Traverse all keys and invoke a callback for every linked list node from the linked list head to the end in the order stored

  - **Signature**

    ```c
    void linked_list_traverse_in_order(
        const linked_list_instance_ts * p_lili,
        linked_list_traversal_callback_t p_traversal_callback
    )
    ```
  
  - **Parameters**
  
    1. `const linked_list_instance_ts * p_lili`
  
       Pointer to the linked list to traverse through
  
    2. `linked_list_traversal_callback_t p_traversal_callback`
  
       Pointer to the callback to invoke for every node stored in the linked list
  
  - **Return value**
  
    None
  
- **`linked_list_reverse_in_place`**

  - **Description**

    Reverse the order of the linked list nodes in place

  - **Signature**

    ```c
    void linked_list_reverse_in_place(linked_list_instance_ts * p_lili)
    ```

  - **Parameters**

    1. `linked_list_instance_ts * p_lili`

       Pointer to the linked list to reverse the nodes in
  
  - **Return value**
  
    None
