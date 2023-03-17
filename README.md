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

- duplicate report
- empty string insert and delete

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

## Problems
- destroying the linked list more than once causes freing of a previously deallocated pointer
  the interface should work differently here?

  The thing is that the linked list instance must not be accessed after is has been freed