# linked-list-in-C
 A full implementation of a simply linked list with interface in C

## Project rquirements
### Data stored
This implementation will use a linked list to store string instances through string pointers to not waste any memory, but is therefore based on dynamic memory allocation.

**Data stored per node:**
- `String`: Pointer to some string that acts as `data` for a particular node
- `Next`: Pointer to the next linked list node

### Interface
- Creation
  + [OK] Create an instance
- Destroyal
  + [OK] Destroy linked list and deallocate all memory used for nodes and the instance itself
- Insertion
  + [OK] Append if value was not yet added
- Deletion
  + [OK] Delete node for value
  + [OK] Clear all nodes
- Utility
  + [OK] Has entry with value
  + [OK] Number of current nodes int lili
- Traversal (access each in the list)
  + [OK] Callback invoked for every single entry in the current order
- Sorting (in place?)
  + [OK] Sorting nodes in place using some sorting callback
- Debugging
  + [OK] Print the contens of the linked list to the console

### Testing
The interface is to be testes thoroughly in terms of all operations and edge-cases.

**Test suite:**
- general
  + destroying linked list clears all nodes and sets head to zero
  + creating; adding; deleting; clearing and destroying sets the size properly
  + insert in empty list adds single entry i.e. inits the lili
  + insert in non-empty list adds accordingly (multiple)
  + delete from empty list has not effect and head stays null
  + delete from single size list resets head to null
  + delete multiple from bigger list removed accordingly
  + clear removes all entries and sets the size to zero
  + traverse in order gets the right number and order of nodes, none for empty lili's
  + has key is false when key not in list
  + has key true when key in list
  + reverse empty list has no effect
  + reverse single entry list has no effect
  + reverse many entried list reversed the list accordingly
  + operations work between different linked list instances
- guards
  + all functions argument guards on multiple levels + no side-effects
- notification
  + all return valuse work as expected
- dataset
  + failure when inserting a non-existent key
  + failure when deleting a non-existen key
  + failure when insertin a key with empty string+

**Test cases:**
- Cannot insert duplicates based on key

### Documentation
- Light in-code documentation
- Interface documentation

### Presentation
- Clean README page with all information
- Problems and solutions?
- trade-off
- performance

### Finalizing
- Abstract and DRY without loosing too much time
- Handle all todo
- Minimize and uniform debugging prints