AI System that uses C++:
- TensorFlow

What C++ contributes to the system:
- TensorFlow mainly uses C++ for its back end and core runtime, while Python supports the front end
  -  Due to C++'s high performance and speed, C++ kernels are used mainly for math operations
  -  Since C++ more closely interacts with hardware, it allows for direct use of GPUs, CPUs, multithreading, and vector instructions
  -  C++'s portability is a major component as it allows it to run on servers, mobile devices, and embedded systems

Performance feature for program:
- Feature:
  -  In-memory account lookup with hash map
- Problem:
  -  Original Bank class stored accounts in a fixed array of 100, sorted with O(n²) insertion sort and found accounts with binary search (O(log n))
- Changes:
  - Bank class was modified by replacing "count", and "sortAccounts()" with "std::unordered_map<int, Account>"
  - findAccount() now does hash lookup
  - "MAX_ACCOUNTS" was removed since map has no fixed limit
  - Accounts now save in different order (harmless)
 - Improvements:
   - Lookups are O(1) on average, and load-time sort is gone
 - Tradeoffs:
   - Hash map uses more memory and speed difference is negligible but has more scalability
 - Tie-in:
   - Like TensorFlow, this change relies on C++'s control over memory and data structures to avoid wasted work

