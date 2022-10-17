---
id: rea60o3ljop7kknuq0hlnds
title: Note
desc: ''
updated: 1663725701747
created: 1660035735411
---

# 2022-08-09

I tried to get a vector of string view to keep the regex's match results. However, the first and last of the results are invalidated in subsequence call to regex::search. I was expecting the first are last are pointing to the input string. It seems not the case. Apparently they are pointing to some internal memory.

## At night

Figured out where the bug was. I passed in a "string", but the function expects a std::string. So it made one, which no longer live after return and hence the string_view's are all dead by the time of return. Now string_view works well.

# 2022-09-21

Build on Mac. Need to build googletest like this:

- Edit CMakeLists.txt to add
  - set(CMAKE_CXX_STANDARD 20)
  - set(CMAKE_VERBOSE_MAKEFILE ON)
- Run cmake with
  - CC=/usr/local/bin/gcc-12 CXX=/usr/local/bin/g++-12 cmake ../

The second step is essential. Otherwise googletest will build with clang by default and it will not link to my projects which is using Homebrew's GCC.
