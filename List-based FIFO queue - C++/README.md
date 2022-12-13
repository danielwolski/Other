# List based FIFO queue - C++


Implementation of FIFO queue - it is an extension of XOR linked list.

In addition to the functions of the XOR list (ADD_BEG, ADD_END, DEL_BEG, DEL_END, PRINT_FORWARD, PRINT_BACKWARD) from the XOR linked list the list implements:

SIZE - number of list elements.
The queue is a data structure that uses list and provides functions corresponding to the following commands:


PUSH N - add element N to the end of the queue.

POP - remove the first element from the queue.

PRINT_QUEUE - print the queue from the first element to the lastly added.

COUNT - the number of elements in queue ≤ SIZE.

GARBAGE_SOFT - change the values of all elements of the list that do not belong to the queue to 0.

GARBAGE_HARD - remove all elements from the list that does not belong to the queue.
____________________________
EXAMPLE

Input

PUSH 1

PRINT_FORWARD

PRINT_QUEUE

SIZE

COUNT

PUSH 2

PRINT_FORWARD

PRINT_QUEUE

SIZE

COUNT

PUSH 3

PRINT_FORWARD

PRINT_QUEUE

SIZE

COUNT

POP

PRINT_FORWARD

PRINT_QUEUE

SIZE

COUNT

PUSH 4

PRINT_FORWARD

PRINT_QUEUE

SIZE

COUNT

POP

PRINT_FORWARD

PRINT_QUEUE

SIZE

COUNT

POP

PRINT_FORWARD

PRINT_QUEUE

SIZE

COUNT

POP

PRINT_FORWARD

PRINT_QUEUE

SIZE

COUNT

POP

PRINT_FORWARD

PRINT_QUEUE

SIZE

COUNT
_____________
Output


1 

1

1

1

2 1 

1 2 

2

2

3 2 1 

1 2 3 

3

3

1

3 2 1 

2 3 

3

2

3 2 4 

2 3 4 

3

3

2

3 2 4 

3 4 

3

2

3

3 2 4 

4 

3

1

4

3 2 4 

NULL

3

0

NULL

3 2 4 

NULL

3

0
