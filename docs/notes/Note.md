---
id: rea60o3ljop7kknuq0hlnds
title: Note
desc: ''
updated: 1660054843278
created: 1660035735411
---

# 2022-08-09

I tried to get a vector of string view to keep the regex's match results. However, the first and last of the results are invalidated in subsequence call to regex::search. I was expecting the first are last are pointing to the input string. It seems not the case. Apparently they are pointing to some internal memory.

## At night

Figured out where the bug was. I passed in a "string", but the function expects a std::string. So it made one, which no longer live after return and hence the string_view's are all dead by the time of return. Now string_view works well.