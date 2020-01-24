## Sorer
Sorer opens and parses a Schema-on-read text file, and after catagorizing the file then allows a usert to retrieve
both column types and the value in the schema at <column> <row>.

It works by using mmap to put the file into virtual memory. As the file
is Read-Only and the MAP_SHARED and MAP_NORESERVE flags are passed, it does not need the
physical memory to hold the file, the operating system will load and unload parts of the file
as needed. Furthermore it lazily looks up values by storing the index in the file
that each row starts on, and when a value is requested it parses that row on request.
This helps keep memory usage low, and since lines are unlikely to exceed a page of memory the 
performance hit of parsing is minimal.
