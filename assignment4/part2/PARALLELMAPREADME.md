# Example Uses of `pmap()`
Multi-threaded mapping over the dataframe can be very useful in situations where it can be multi-threaded.
However, for it to be useful, it cannot depend on sequential access or writing to a location. Two examples
are included howerver, for some non-sequential uses where it can lead to significant speed-up.
Summing numbers does not depend on sequential access, and can see a substantial speed-up. Replacing
in place also does not require sequential access (or locks) and so can see a substantial speed-up.
The main use is for either modifying the array in place (eg: make all numbers positive), or to 
sum or store the data within the DataFrame. However for situations like printing to StdOut, it cannot
be used as that requires sequential writing to the buffer.

# Design
The design behind `pmap()` is simple. Since multi-threaded operations cannot depend on sequential access,
it can make the assumption that each Rower can cover a different part of the dataframe. First it
decides how many threads to use (if the dataframe is too small it instead runs it as a single threaded operation),
up to a maximum of 8 threads. This number is fairly arbirtary, and depends on computer. In this case, it was
tested on a 4-core intel laptop with 8 virtual cores, so 8 threads was picked as a safe maximum thread value.
More testing is needed to truly choose this value. It then generates a rower for each thread using `clone()`.
Next it divies up the dataframe in about equal amounts per thread, and launches a new thread to parse
that number of rows in the database (using `_pmap_helper()`). Following that, it joins the threads, combines the rowers, and then 
cleans up the memory it allocated. It attempts to not use too many threads for too small a database, while still
seeing a speed-up. More testing it needed to determine the true number of threads that should be used, and the amount of rows
that each thread should cover at a minimum to see a substantial speed increase.

# How our Examples Demonstrate the Speed-Up
Both are examples show how depending on database size, the bigger the database the more threading 
is beneficial. To this point the database size increases over time in our benchmarks. For the first
one it just sums the values, which does not require locks. This shows how in bigger dataframes
the speed-up becomes very large, as it can do its thing and combine the results at the end.
This is one example of a speed-up, parsing data in parallel. Another example is to modify in place.
Therefore I wrote a Rower to delete all strings in the dataframe, which also does not require 
sequential access, as it is modifying in place. This again shows a different approach to 
non-sequential operations that can lead to a large speed-up. As a note, this is a valid test
as deleteing memory does not depend on size - therefore even different strings in each test
result in the same approximate amount of time needed, regardless of their size, as long as the
number of them is equal. This is another useful operation that can see a large speed increase
by multi-threading. Our benchmarks store the number of times that the multi-threaded performs 
better and vice-versa, and then display the final amount at the end. As you will see,
on average, and espicially as the database grows, the multi-threaded does outperform the
single threaded performance.

# Issues we Encountered
We did not encounter any major issues implementing pmap, as I have written and debugged multi-threaded
programs before, including in C. Furthermore, the design hinted that all race conditions should be
handled by the Rowers, not by pmap. Therefore I did not have to worry about lock contention. The biggest
issue I faced was not being able to override `join_delete()`, which upon speaking to Proffessor Vitek,
I learned was a bug and was allowed. After that the design functioned well.
