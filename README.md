# mxc

The C programming language is one of the most versatile and extensible languages available for wide use, yet sometimes it seems lagging a little bit behind the times. It seems plausible for developers to constantly rehash a few functions which seem to be of essence to supporting any sort of program. These include functions which manipulate strings, functions which deal with dynamic-sized data types, and perhaps those which deal with associative arrays.

What this library is meant to function as is a set of abstractions which save the time of having to implement such features for experienced developers who may be moving into a new project, or even to ease in users of other programming languages who want to learn lower-level programming with C.

As of the moment, a gcc or clang-compatible compiler with support for C99 or later is required (as the program uses the void pointer arithmetic extension). Documentation of the four abstractions (vector_t, string_t, stack_t and map_t) and refactoring to C99 compability without extensions will be coming soon.
