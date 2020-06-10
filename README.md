# graph_search
Searching for subgraphs in graphs in C++

# Building
`graph_search` is a header-only library, and it does not need to be compiled. However, you can compile tests and examples using the following instructions.
To build the program yourself, first make sure you have the following tools installed:
- C++ compiler (tested with GCC 9.2)
- CMake
- Python
- [Conan package manager](https://conan.io/)

1. Add the [bincrafters repository](https://bintray.com/bincrafters/public-conan) to conan.
1. Compile and export into conan cache the following projects in order:
    - [skarupke hash maps](https://github.com/andreasxp/flat_hash_map) (this is a dependency, not a first-party lib)
    - [type_traits](https://github.com/andreasxp/type_traits)
    - [random](https://github.com/andreasxp/random)
    - [dataprism](https://github.com/andreasxp/dataprism)
    - [manual_ptr](https://github.com/andreasxp/manual_ptr)
    - [graph](https://github.com/andreasxp/graph)
1. Compile graph_search examples.

To compile and export the projects you can use the conan commands from the directory root. Conan also has support for building tests and examples for all projects.
```
conan install . -if build -b outdated -o tests=True -o examples=True
conan build . -bf build
conan create . andreasxp/stable
```
In these commands, `-o tests=True` and `-o examples=True` can be omitted for the projects you don't want tests for.
