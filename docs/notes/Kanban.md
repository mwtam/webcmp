---
id: pxi555um6e5tvv5hlz48rdr
title: Kanban
desc: ''
updated: 1661749218169
created: 1659684610288
---

## Working

## Backlog

- [ ] Make an effective workflow to add and test new entries

- [ ] Visit sites in multi-threads

## Done

- [x] Make sure the BrowserCurl does not leak
  - Done. Valgrind said no leak is possible.

- [x] Improve the interface of BrowserCurl::go
  - [x] I should return according to CURLcode, not the length of page. A simple bool should do.

- [x] Add tests under google test
  - [x] BrowserCurl can construct without error
  - [x] BrowserCurl's go returns how many bytes are loaded into page
  - [x] When go a new url that it can't visit, the page is empty, the error code and message is set properly.

- [x] Read sites to visit (in json?)
- [x] Remember the last state
- [x] Make the result vector a string presentation (for compare to a file later)
  - Do the reverse: make the string into a vector of string_view
- [x] Diff the current state vs memory

- [x] Report the results
  - CHANGED (need the title and URL)
  - UNCHANGED (omit printing?)
  - NEW_TITLE
  - FAILED (need error message)

- [x] Add error handling to BrowserCurl
