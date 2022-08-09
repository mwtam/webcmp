---
id: pxi555um6e5tvv5hlz48rdr
title: Kanban
desc: ''
updated: 1659686413457
created: 1659684610288
---

# Working

# Backlog
- [ ] Add tests under google test
    - [ ] BrowserCurl can construct without error
    - [ ] BrowserCurl's go returns how many bytes are loaded into page
    - [ ] When go a new url that it can't visit, the page is empty, the error code and message is set properly.

- [ ] Add error handling

# Done
- [x] Make sure the BrowserCurl does not leak
    - Done. Valgrind said no leak is possible.

- [x] Improve the interface of BrowserCurl::go
    - [x] I should return according to CURLcode, not the length of page. A simple bool should do.