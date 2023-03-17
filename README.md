# linked-list-in-C
A minimal implementation of a linked list in C to understand this datastructure and the C language better. The focus here was the execution of implementing the datastructure and and roughly testing as fast as possible.

The implementation could be DRYed up quite a bit to remove redundant bits of code into utility functions, but I chose to experiment with different, more or less idiomatic approaches of implementing things, rather than spending too much time on abstractions too early.

## Disclaimer
This is an exercise project and definitely not something you should use anywhere without modification as there may be subtle bugs for edge-cases that were not considered nor tested for.

## Problems
This section contains a list of problems or not-so-great things in terms of the implement and interface

- **The state of the interface datatypes is transparent**
  i.e. the user can access all the state exactly as the implementation can. The goal was not to develop a fully opaque library, so the interface was left open in terms of header-level implementation details
- **Destroying a linked list does not protect the user from accessing the deallocated linked list**
  When the linked list is destroyed, the pointer to the old linked list memory location persists in the user code. There should be some sort of abstraction to protect the user from invalid operation on a destroyed linked list


## Documentation
The following functions are available by including the `linked_list.h` header into the source file.

### Naming conventions

#### Prefixes

- `p_` represents a pointer of some sort

#### Suffixes

- `_te` stands for `typedef enum`
- `_ts` stands for `typedef struct`
- `_t` stands for some other, more general `typedef`

### Relevant data types

- `linked_list_bool_te`

  An integer type used by the implementation to represent:

  - Boolean true as `LINKED_LIST_TRUE`
  - Boolean false as `LINKED_LIST_FALSE`

  This integer value can be used in conditionals without explicitly comparing against the enum integers as the integer values match C's truthy and falsy model where:

  - `NULL` or `0` is falsy
  - any other value is truthy

- `linked_list_instance_ts`

  A struct that hold the reference to the linked list head on which all interface functions are based

### Interface functions

- **`linked_list_create`**

  - **Description**

    Allocates and initializes a new linked list instance

  - **Signature**

    `linked_list_instance_ts * linked_list_create(void)`

  - **Parameters**

    None

  - **Return value**

    - `NULL` when a linked list instance cannot be allocated
    - Instance of `linked_list_instance_ts` when the linked list was allocated successfully

- **`linked_list_destroy`**

  - **Description**

    Deallocates all nodes in the linked list and the linked list itself

  - **Signature**

    `void linked_list_destroy(linked_list_instance_ts * p_lili)`

  - **Parameters**

    1. `linked_list_instance_ts * p_lili`

       Pointer to the linked list to be destroyed

  - **Return value**

    None

- **`linked_list_visualize`**

  - **Description**

    Print the contents of the linked list to `stdout`

  - **Signature**

    `void linked_list_visualize(const linked_list_instance_ts * p_lili, const char * p_tag)`

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

    `linked_list_bool_te linked_list_insert(linked_list_instance_ts * p_lili, const char * p_insertion_key)`

  - **Parameters**

    1. `linked_list_instance_ts * p_lili`

       Pointer to the linked list to add a new node to

    2. `const char * p_insertion_key`

       Pointer to a null-terminated string that is to be inserted into the linked list node

  - **Return value**

    - `LINKED_LIST_TRUE` when a new node was inserted successfully for `p_tag`
    - `LINKED_LIST_FALSE` when the linked list already contains a node with the same string as `p_tag`

- **`linked_list_delete`**

  - **Description**

    Delete existing node from the linked list with the specified string value

  - **Signature**

    `linked_list_bool_te linked_list_delete(linked_list_instance_ts * p_lili, const char * p_deletion_key)`

  - **Parameters**

    ???

  - **Return value**

    - A
    - B
  
- **`TODO-GS`**

  - **Description**

    ???

  - **Signature**

    ???

  - **Parameters**

    ???

  - **Return value**

    - A
    - B
  
- **`TODO-GS`**

  - **Description**

    ???

  - **Signature**

    ???

  - **Parameters**

    ???

  - **Return value**

    - A
    - B
  
- **`TODO-GS`**

  - **Description**

    ???

  - **Signature**

    ???

  - **Parameters**

    ???

  - **Return value**

    - A
    - B

### Finalizing

- documentation
  + about this little project + focus on execution and functionality, not nice and very idiomatic code
  + interface
  + big picture
  + what data saved
  + problems (see below)
- check spelling in readme
- Add links to readme for navigation

## Problems
- destroying the linked list more than once causes freing of a previously deallocated pointer
  the interface should work differently here?

  The thing is that the linked list instance must not be accessed after is has been freed