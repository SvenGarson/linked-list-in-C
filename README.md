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

**Test cases:**
- Allocation and de-allocation
- Fully de-populating the linked list
- Operations work with multiple linked lists in memory
- Creation of instance initialized head
- Null and nested null guards to functions (linked list instance and others)
- Reporting return values for all operations
- Head is re-assigned properly when lili is initialized and fully emptied
- Empty key string when adding fails creating a new node on insertion
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