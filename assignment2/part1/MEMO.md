Map: 
Our map is constructed by an array of linked Hashpair. Each
Pair keeps storaging key and value and tracking of the next 
Hashpair.

Queue:
Our queue is built based on a circular buffer, that is an 
array with keeping track of the start index, last index, as 
well as the size and capacity, the queue. Push will double 
the capacity if the size is larger than capacity. If the 
capacity is enough for elements, but the index will grow 
over the capacity, it will cycle back to the begin index 
and keep storing again(because the prev element has to be 
removed)

Array:
Keep storing the element by double the array if the size is 
larger than capacity, and created the array class for the
type of float, int, string, and boolean but all the methods 
are the same.

About tests:

Map repo:
Documentation quality: The tests have good commented and 
complicated enough to cover some cases and each method was
being tested.
Responsiveness: We dont have much questions about the test, 
since the documentation was very clear.
Test quality: The quality could be improved. The tests 
could be improved is where the test could print some output 
shows they worked instead of return booleans. And the tests 
were not able to show which line gets false in the middle.
They used passed && passed &&... and ends up returning a bool,
if true then it is passed.
Btw, We also have our own tests for this.

Array repo:
Documentation quality: very good quality and clear
Responsiveness: the quality was really good, so we dont have 
to communicate with them
Test quality: the quality was very high as well

Queue repo:
Documentation quality: Queue tests were in a good shape,
all methods were tested.
Responsiveness: We dont have much questions about the test, 
since the documentation was very clear.
Test quality: Very good quality.