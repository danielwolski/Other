# XOR linked list

Implementation of a bidirectional list in C++. Classic bidirectional list stores successor and predcessor addresses in nodes, this project implements storage of xor of these adresses in nodes. This saves ~50% of memory used by the list structure.

The list provides the following functionalities related to the following commands:

ACTUAL - value of the currently pointed element. For an empty list it is NULL and after adding the first element to the list 
ACTUAL returns the value of that element as long as it is not moved by other operations.

NEXT - prints the value of the ACTUAL successor setting it ACTUAL at the same time. If ACTUAL points to the last element of 
the queue, its successor will be the first element of the queue.

PREV - prints the value of the predecessor ACTUAL setting it ACTUAL at the same time. If ACTUAL points to the first element 
of a queue, its predecessor will be the last element of the queue.

ADD_BEG N - adding an element with value N to the beginning of the list.

ADD_END N - adding an element with value N to the end of the list.

ADD_ACT N - adding an element with the value of N as a predecessor of the currently selected element (ACTUAL).

DEL_BEG - removes the first node from the list.

DEL_END - removes the last node from the list.

DEL_VAL N - removes from the list all nodes whose value is equal to N.

DEL_ACT - removes from the list the node that ACTUAL points to, simultaneously setting ACTUAL to PREV. In the case of the 

PREV does not exist (ACTUAL was the first element of the list) ACTUAL shows the last element of the list.

PRINT_FORWARD - prints the contents of the list from the first to the last element.

PRINT_BACKWARD - prints the contents of the list from the last to the first element.

________________
EXAMPLE



Input:


ADD_END 1

ADD_BEG 2

ADD_END 3

ADD_BEG 4

PRINT_FORWARD

DEL_VAL 3

PRINT_FORWARD

DEL_VAL 2

PRINT_FORWARD

ADD_END 1

ADD_BEG 2

ADD_END 3

ADD_BEG 4

PRINT_FORWARD

DEL_VAL 4

PRINT_FORWARD





Output:


4 2 1 3 

4 2 1 

4 1 

4 2 4 1 1 3 

2 1 1 3 

---------------------------------------------------------------
