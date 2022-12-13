# List based FIFO queue - C++


The task is to implement FIFO queue using doubly or singly linked list. It is an extension of XOR linked list
In addition to the functions of the XOR list (ADD_BEG, ADD_END, DEL_BEG, DEL_END, PRINT_FORWARD, PRINT_BACKWARD) from the XOR linked list the list implements:

SIZE - liczba elementów listy.
The queue is a data structure that uses list and provides functions corresponding to the following commands:


PUSH N - add element N to the end of the queue.

POP - remove the first element from the queue.

PRINT_QUEUE - print the queue from the first element to the lastly added.

COUNT - the number of elements in queue ≤ SIZE.

GARBAGE_SOFT - change the values of all elements of the list that do not belong to the queue to 0.

GARBAGE_HARD - remove all elements from the list that does not belong to the queue.
