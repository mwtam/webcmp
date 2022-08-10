---
id: pxi555um6e5tvv5hlz48rdr
title: Kanban
desc: ''
updated: 1660126669210
created: 1659684610288
---

# Working

# Backlog
- [ ] Make the result vector a string presentation (for compare to a file later)
- [ ] Remember the last state
- [ ] Diff the current state vs memory

- [ ] Read sites to visit (in json?)

- [ ] Add error handling to BrowserCurl
- [ ] Report the results
    - CHANGED (need the title and URL)
    - UNCHANGED (omit printing?)
    - NEW_TITLE
    - FAILED (need error message)

- [ ] Make an effective workflow to add and test new entries

- [ ] Visit sites in multi-threads

# Done
- [x] Make sure the BrowserCurl does not leak
    - Done. Valgrind said no leak is possible.

- [x] Improve the interface of BrowserCurl::go
    - [x] I should return according to CURLcode, not the length of page. A simple bool should do.

- [x] Add tests under google test
    - [x] BrowserCurl can construct without error
    - [x] BrowserCurl's go returns how many bytes are loaded into page
    - [x] When go a new url that it can't visit, the page is empty, the error code and message is set properly.
