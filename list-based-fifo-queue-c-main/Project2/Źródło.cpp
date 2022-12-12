#include <iostream>
#include <string>

using namespace std;


struct Node
{
    int value = 0;
    Node* next = NULL;

}  *End = NULL, * Beg = NULL, * Front = NULL, * Back = NULL;


int IN_QUEUE(Node** node, Node** back_ref, Node** front_ref, int count)//returns 1 if node is in queue, 0 if not
{
    if (count == 0 && *back_ref == NULL && *front_ref == NULL)//if queue is empty
        return 0;
    else if (*back_ref == *front_ref && *node != *back_ref)//if queue is of size one, and our node is not front || back
        return 0;
    else
    {
        //going through the queue
        Node* current = *front_ref;
        Node* next = NULL;
        Node* prev = NULL;

        while (prev != *back_ref)
        {
            if (*node == current)//if we spot our node = one of queue's node's = it means our node is in queue
                return 1;

            prev = current;
            next = current->next;
            current = next;
        }
    }
    return 0;//if went thorugh queue without spotting our node = our node isnt in queue
}

void ADD_END(Node** end_ref, Node** beg_ref, Node** back_ref, Node** front_ref, int value, int& size, int& count)
{
    Node* new_node = new Node();

    new_node->value = value;
    new_node->next = *end_ref;

    if (*end_ref == NULL)
        *beg_ref = new_node;//If its first node, then its also beg

    //Inserting at the end= obtaining new end
    *end_ref = new_node;

    (*beg_ref)->next = *end_ref;

    size++;
    if (IN_QUEUE(end_ref, back_ref, front_ref, count) == 1)//if our new node is in queue
        count++;//enlarge the count
}

void ADD_BEG(Node** end_ref, Node** beg_ref, Node** back_ref, Node** front_ref, int value, int& size, int& count)
{
    Node* new_node = new Node();

    new_node->value = value;

    if (*beg_ref == NULL)
    {
        *end_ref = new_node;//If its first node, then its end
    }
    else
    {
        //If linked list is not empty => next of current beg will be our new node
        (*beg_ref)->next = new_node;
    }

    //Inserting at the beg = obtaining new beg
    *beg_ref = new_node;

    (*beg_ref)->next = *end_ref;//connect end with beg to make a cycle

    size++;
    if (IN_QUEUE(beg_ref, back_ref, front_ref, count) == 1)//if our new node is in queue
        count++;//enlarge the count
}

void PRINT_BACKWARD(Node** end_ref)
{
    if (*end_ref == NULL)
        cout << "NULL";
    else
    {
        Node* current = *end_ref;
        Node* next = NULL;

        while (next != *end_ref)
        {
            cout << current->value << " ";

            next = current->next;
            current = next;
        }
    }
}

void PRINT_FORWARD(Node** end_ref, int size) {
    if (size == 0)
        cout << "NULL";
    else
    {
        int* arr = new int[size];//array to store nodes in reversed order
        int i = 0;

        Node* current = *end_ref;
        Node* next = NULL;

        while (next != *end_ref)
        {
            arr[i] = current->value;//save values of nodes into an int array
            i++;

            next = current->next;
            current = next;
        }

        for (i = size - 1; i >= 0; i--)
            cout << arr[i] << " ";//and then print them backwards (its caused by the fact of reversed ptr's in program)

        delete[] arr;
    }
}

void PRINT_QUEUE(Node** front_ref, Node** back_ref, int count)
{
    if (count == 0)
        cout << "NULL";
    else
    {
        //print values of all values from front to back ptr
        Node* current = *front_ref;
        Node* next = NULL;
        Node* prev = NULL;

        while (prev != *back_ref)
        {
            cout << current->value << " ";

            prev = current;
            next = current->next;
            current = next;
        }
    }
}

void DEL_END(Node** end_ref, Node** beg_ref, Node** back_ref, Node** front_ref, int& size, int& count)
{
    if (*end_ref == NULL)
        ;//dont do anything
    else
    {
        if (IN_QUEUE(end_ref, back_ref, front_ref, count))//if end was in queue
            count--;

        if (*end_ref == *back_ref)
            *back_ref = *beg_ref;

        if (*end_ref == *beg_ref)//if theres only one node, we are just NULL'ing everything
        {
            Node* temp = *beg_ref;//Node to be deleted

            *end_ref = NULL;
            *beg_ref = NULL;

            free(temp);
        }
        else
        {
            Node* temp = *end_ref;//Node to be deleted

            //Updade end
            *end_ref = (*end_ref)->next;

            free(temp);
        }
    }

    if (*end_ref != NULL)
        (*beg_ref)->next = *end_ref;

    if (size > 0)
        size--;
}

void DEL_BEG(Node** end_ref, Node** beg_ref, Node** back_ref, Node** front_ref, int& size, int& count)
{
    if (*beg_ref == NULL)
        ;//dont do anything
    else
    {
        if (IN_QUEUE(beg_ref, back_ref, front_ref, count))//if beg was in queue
            count--;

        if (*beg_ref == *back_ref)
        {
            Node* current = *front_ref;
            Node* prev = NULL;

            while (current != *back_ref)
            {
                prev = current;
                current = current->next;
            }

            *back_ref = prev;
        }

        if (*end_ref == *beg_ref)//if theres only one node, we are just NULL'ing everything
        {
            Node* temp = *end_ref;//node to be deleted

            *end_ref = NULL;
            *beg_ref = NULL;

            free(temp);
        }
        else
        {
            Node* current = *end_ref;
            Node* prev = NULL;
            Node* next;

            while (current != *beg_ref)
            {

                next = current->next;
                prev = current;//update adresses
                current = next;
            }

            Node* temp = *beg_ref;//node to be deleted

            *beg_ref = prev;
            prev->next = NULL;

            free(temp);
        }
    }

    if (*end_ref != NULL)
        (*beg_ref)->next = *end_ref;

    if (size > 0)
        size--;
}

void PUSH(Node** beg_ref, Node** end_ref, Node** front_ref, Node** back_ref, int value, int& size, int& count)
{
    if (count == 0 && size == 0)//if both list and queue are empty
    {
        ADD_BEG(beg_ref, end_ref, back_ref, front_ref, value, size, count);//add node
        *front_ref = *beg_ref;//set pointers
        *back_ref = *beg_ref;

        count++;
    }
    else if (size > count)
    {
        if (count > 0)//if queue has some elements
        {
            *back_ref = (*back_ref)->next;
            (*back_ref)->value = value;

            count++;
        }
        else if (count == 0)//if queue is empty
        {
            (*end_ref)->value = value;
            *back_ref = *end_ref;
            *front_ref = *end_ref;

            count++;
        }
    }
    else if (size == count)//we have to add node to list (and then add it to queue)
    {
        Node* new_node = new Node();
        new_node->value = value;

        (*back_ref)->next = new_node;
        new_node->next = *front_ref;

        *back_ref = new_node;

        //searching for proper beg ptr
        Node* current = (*end_ref)->next;
        Node* prev = NULL;
        while (current != *end_ref)
        {
            prev = current;
            current = current->next;
        }
        *beg_ref = prev;

        size++;
        count++;
    }
}

void POP(Node** front_ref, int& count)
{
    if (count == 0)
        cout << "NULL\n";
    else
    {
        cout << (*front_ref)->value << endl;//print popped node value
        *front_ref = (*front_ref)->next;//move front

        if (count > 0)
            count--;
    }
}

void GARBAGE_SOFT(Node** beg_ref, Node** back_ref, Node** front_ref, int size, int count)
{
    if (size == count)
        ;
    else
    {
        if (size == 1 && count == 0)//if queue is empty, and theres only one node in list
            (*beg_ref)->value = 0;
        else
        {
            Node* current = (*back_ref)->next;
            Node* next;

            //from node next to back to node prev front, set values of all nodes to zero
            while (current != *front_ref)
            {
                current->value = 0;

                next = current->next;
                current = next;
            }
        }
    }
}

void GARBAGE_HARD(Node** beg_ref, Node** end_ref, Node** front_ref, Node** back_ref, int& size, int& count)
{
    if (size == count)
        ;
    else
    {
        if (size == 1 && count == 0)
            DEL_BEG(beg_ref, end_ref, front_ref, back_ref, size, count);
        else
        {
            int n = size - count;//number of nodes that will be deleted
            Node* nodes_tbd = new Node[n];

            Node* current = (*back_ref)->next;
            Node* next;
            int i = 0;

            while (current != *front_ref)
            {
                nodes_tbd[i] = *current;//store the nodes to be deleted

                next = current->next;
                current = next;
                i++;
            }
            (*back_ref)->next = *front_ref;//update adress (of back->next to front) in order to exclude nodes to be deleted from list

            size = count;//set proper size

            delete[] nodes_tbd;//delete nodes
        }
    }
}

void MAINTAIN_INPUT(const string& text, int& size, int& count)
{
    int value;

    if (text == "ADD_BEG") {
        cin >> value;
        ADD_BEG(&End, &Beg, &Back, &Front, value, size, count);
    }
    else if (text == "ADD_END") {
        cin >> value;
        ADD_END(&End, &Beg, &Back, &Front, value, size, count);
    }
    else if (text == "DEL_BEG") {
        DEL_BEG(&End, &Beg, &Back, &Front, size, count);
    }
    else if (text == "DEL_END") {
        DEL_END(&End, &Beg, &Back, &Front, size, count);
    }
    else if (text == "PRINT_FORWARD") {
        PRINT_FORWARD(&End, size);
        cout << endl;
    }
    else if (text == "PRINT_BACKWARD") {
        PRINT_BACKWARD(&End);
        cout << endl;
    }
    else if (text == "PRINT_QUEUE") {
        PRINT_QUEUE(&Front, &Back, count);
        cout << endl;
    }
    else if (text == "SIZE") {
        cout << size;
        cout << endl;
    }
    else if (text == "COUNT") {
        cout << count;
        cout << endl;
    }
    else if (text == "PUSH") {
        cin >> value;
        PUSH(&Beg, &End, &Front, &Back, value, size, count);
    }
    else if (text == "GARBAGE_SOFT") {
        GARBAGE_SOFT(&Beg, &Back, &Front, size, count);
    }
    else if (text == "GARBAGE_HARD") {
        GARBAGE_HARD(&Beg, &End, &Front, &Back, size, count);
    }
    else if (text == "POP") {
        POP(&Front, count);
    }
}


int main()
{
    int size = 0;
    int count = 0;
    string text;
    cin >> text;
    MAINTAIN_INPUT(text, size, count);

    while (getline(cin, text))
    {
        cin >> text;
        MAINTAIN_INPUT(text, size, count);
    }

    return 0;
}