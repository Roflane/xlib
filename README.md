# xlib — custom STL implementation

Partial STL reimplementation written to have a
controlled, minimal alternative to the standard library.

**Stack:** C++

### Implemented
- `vector<T>`
- `string`
- `unordered_map<K, V>`
- `linked_list<T>`
- `shared_ptr<T>`, `unique_ptr<T>`, `weak_ptr<T>`
- Move semantics, perfect forwarding
- Concepts: `CTSmartPointer`, `CTPointer` for compile-time type distinction

### Known issues
Several known UB cases not yet resolved
