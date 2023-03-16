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
  + Append if value was not yet added
- Deletion
  + Delete node for value
- Utility
  + Has entry with value
- Traversal (access each in the list)
  + Callback invoked for every single entry in the current order
- Sorting (in place?)
  + Sorting nodes in place using some sorting callback
- Debugging
  + Print the contens of the linked list to the console

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

### Documentation
- Light in-code documentation
- Interface documentation

### Presentation
- Clean README page with all information
- Problems and solutions?
- trade-off
- performance

### Finalizing
- Handle all todo
- Minimize and uniform debugging prints