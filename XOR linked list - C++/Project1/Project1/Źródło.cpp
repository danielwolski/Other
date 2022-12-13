#include <iostream>
#include <string>

using namespace std;


struct Node
{
    int value;
    Node* npx;
}*End = NULL, * Beg = NULL, * Act = NULL, * Prev = NULL, * Next = NULL;

struct Node_to_be_Deleted
{
    Node* before_tbD;
    Node* tbD;
    Node* after_tbD;
};

Node* XOR(Node* a, Node* b)
{
    return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b));
}

void ADD_BEG(Node** beg_ref, Node** end_ref, Node** act_ref, Node** prev_ref, int value)
{
    Node* new_node = new Node();

    new_node->value = value;
    //XOR will be just current beginning
    new_node->npx = *beg_ref;

    if (*beg_ref == NULL)
    {
        *end_ref = new_node;//If its first node, then its also end...
        *act_ref = new_node;//...and actual
    }
    else
    {
        //if linked list is not empty => npx of
        //current beg will be XOR(new node, node next to current beg)
        (*beg_ref)->npx = XOR(new_node, (*beg_ref)->npx);

        if (*prev_ref == NULL)//
            *prev_ref = new_node;
    }

    //Inserting at the beginning = obtaining new beg
    *beg_ref = new_node;
    //If actual was old beg, then new beg is its prev
    if (*act_ref == XOR((*beg_ref)->npx, NULL))
        *prev_ref = *beg_ref;
}

void ADD_END(Node** beg_ref, Node** end_ref, Node** act_ref, Node** next_ref, int value)
{
    Node* new_node = new Node();

    new_node->value = value;
    //XOR will be just current end
    new_node->npx = *end_ref;

    if (*end_ref == NULL)
    {
        *beg_ref = new_node;//If its first node, then its also beg...
        *act_ref = new_node;//...and actual
    }
    else
    {
        //If linked list is not empty => npx of
        //current end will be XOR(new node, node next to current end)
        (*end_ref)->npx = XOR(new_node, (*end_ref)->npx);

        if (*next_ref == NULL)
            *next_ref = new_node;
    }

    //Inserting at the end = obtaining new end
    *end_ref = new_node;
    //If actual was old end, then new end is its next
    if (*act_ref == XOR((*end_ref)->npx, NULL))
        *next_ref = *end_ref;
}

void PRINT_FORWARD(Node** beg_ref)
{
    if (*beg_ref == NULL)
        cout << "NULL\n";
    else
    {
        Node* current = *beg_ref;
        Node* prev = NULL;
        Node* next;

        while (current != NULL)
        {
            cout << current->value << " ";

            next = XOR(prev, current->npx);
            prev = current;//update adresses
            current = next;
        }
    }
}

void PRINT_BACKWARD(Node** end_ref)
{
    if (*end_ref == NULL)
        cout << "NULL\n";
    else
    {
        Node* current = *end_ref;
        Node* prev = NULL;
        Node* next;

        while (current != NULL)
        {
            cout << current->value << " ";

            next = XOR(prev, current->npx);
            prev = current;//update adresses
            current = next;
        }
    }
}

void ACTUAL(Node* act)
{
    if (act == NULL)
        cout << "NULL\n";
    else
        cout << act->value << endl;
}

void NEXT(Node** beg_ref, Node** act_ref, Node** prev_ref, Node** next_ref, int should_i_cout)
{
    if (*act_ref == NULL)
    {
        cout << "NULL\n";
    }
    else
    {
        if (*act_ref == *beg_ref)
        {
            *next_ref = XOR(NULL, (*act_ref)->npx);
        }

        if (*next_ref == NULL)//when actual is  at the end of the list
        {
            *next_ref = *beg_ref;
        }

        //Storing future act next prev
        Node* temp_prev = *act_ref;
        Node* temp_act = *next_ref;
        Node* temp_next = XOR(*act_ref, (*next_ref)->npx);

        //Assigning them
        *prev_ref = temp_prev;
        *act_ref = temp_act;
        *next_ref = temp_next;

        if (should_i_cout == 1)//Its because function is sometimes used in other functions (when we dont want to print anything)
            cout << (*act_ref)->value << endl;
    }

    //If new act is at the beg, then next is going to be node next to the beg
    if (*act_ref == *beg_ref && *beg_ref != NULL)
        *next_ref = XOR((*beg_ref)->npx, NULL);
}

void PREV(Node** end_ref, Node** act_ref, Node** prev_ref, Node** next_ref, int should_i_cout)
{
    if (*act_ref == NULL)
    {
        cout << "NULL\n";
    }
    else
    {
        if (*act_ref == *end_ref)
        {
            *prev_ref = XOR(NULL, (*act_ref)->npx);
        }

        if (*prev_ref == NULL)//if act is at the beginning of the list, then prev is the end of the list
        {
            *prev_ref = *end_ref;
        }

        //Storing future act next prev
        Node* temp_prev = XOR(*act_ref, (*prev_ref)->npx);
        Node* temp_act = *prev_ref;
        Node* temp_next = *act_ref;

        //Assigning them
        *prev_ref = temp_prev;
        *act_ref = temp_act;
        *next_ref = temp_next;

        if (should_i_cout == 1)//Its because function is sometimes used in other functions (when we dont want to print anything)
            cout << (*act_ref)->value << endl;
    }

    //If new act is at the beg, then next is going to be node next to the beg
    if (*act_ref == *end_ref && *end_ref != NULL)
        *prev_ref = XOR((*end_ref)->npx, NULL);
}

void DEL_BEG(Node** beg_ref, Node** end_ref, Node** act_ref, Node** prev_ref, Node** next_ref)
{
    if (*beg_ref == NULL)
        ;//dont do anything
    else
    {
        //maintainging exceptions
        if (*prev_ref == *beg_ref)
            *prev_ref = *end_ref;
        if (*next_ref == *beg_ref)
            *next_ref = XOR((*next_ref)->npx, NULL);
        if (*act_ref == *beg_ref)
        {
            *prev_ref = XOR((*end_ref)->npx, NULL);
            *act_ref = *end_ref;
            //and next stays the same
        }

        if (*beg_ref == *end_ref)//if theres only one node, we are just NULL'ing everything
        {
            *beg_ref = NULL;
            *end_ref = NULL;
            *act_ref = NULL;
            *prev_ref = NULL;
            *next_ref = NULL;
        }
        else
        {
            //Node to be deleted
            Node* temp = *beg_ref;

            //Updade beg
            *beg_ref = XOR(NULL, temp->npx);

            if (*beg_ref != NULL)
            {
                //Update beg node address
                (*beg_ref)->npx = XOR(NULL, XOR(temp, (*beg_ref)->npx));
            }
        }
    }
}

void DEL_END(Node** beg_ref, Node** end_ref, Node** act_ref, Node** prev_ref, Node** next_ref)
{
    if (*end_ref == NULL)
        ;//dont do anything
    else
    {
        if (*beg_ref == *end_ref)//if theres only one node, we are just NULL'ing everything
        {
            *beg_ref = NULL;
            *end_ref = NULL;
            *act_ref = NULL;
            *prev_ref = NULL;
            *next_ref = NULL;
        }
        else
        {
            //exceptions
            if (*prev_ref == *end_ref)
                *prev_ref = XOR((*end_ref)->npx, NULL);
            if (*next_ref == *end_ref)
                *next_ref = *beg_ref;
            if (*act_ref == *end_ref)
            {
                //prev stays the same
                *act_ref = XOR((*end_ref)->npx, NULL);
                *next_ref = *beg_ref;
            }

            //Node to be deleted
            Node* temp = *end_ref;

            //Update the head pointer
            *end_ref = XOR(NULL, temp->npx);

            if (*end_ref != NULL)
            {
                //Update end node address
                (*end_ref)->npx = XOR(NULL, XOR(temp, (*end_ref)->npx));
            }
        }
    }
}

void ADD_ACT(Node** beg_ref, Node** end_ref, Node** act_ref, Node** prev_ref, Node** next_ref, int value)
{
    if (*act_ref == NULL)
        ;
    else
    {
        if (*act_ref == *beg_ref)
        {
            ADD_BEG(beg_ref, end_ref, act_ref, prev_ref, value);
        }
        else
        {
            //Allocate memory for new node
            Node* new_node = new Node();
            new_node->value = value;

            Node* ex_prev = *prev_ref;

            //We are inserting between prev and act
            new_node->npx = XOR(*act_ref, *prev_ref);

            //Updating adresses
            ex_prev->npx = XOR(new_node, XOR((*prev_ref)->npx, *act_ref));//Old prev node
            *prev_ref = new_node;
            (*act_ref)->npx = XOR(*prev_ref, *next_ref);
        }
    }
}

void DEL_ACT(Node** beg_ref, Node** end_ref, Node** act_ref, Node** prev_ref, Node** next_ref)
{
    if (*act_ref == NULL)//If list is empty do nothing
        ;
    else
    {
        if (*act_ref == *beg_ref)//If actual is first node
            DEL_BEG(beg_ref, end_ref, act_ref, prev_ref, next_ref);
        else if (*act_ref == *end_ref)//If actual is last node
            DEL_END(beg_ref, end_ref, act_ref, prev_ref, next_ref);
        else
        {
            PREV(&End, &Act, &Prev, &Next, 0);//Move actual to previous

            //Update adresses = exclude ex actual node
            (*act_ref)->npx = XOR(*prev_ref, XOR(*act_ref, (*next_ref)->npx));
            *next_ref = XOR((*next_ref)->npx, *act_ref);
        }
    }
}

void DEL_VAL(Node** beg_ref, Node** end_ref, Node** act_ref, int value)
{
    int counter = 0;

    //Loop that is going to count values to delete
    if (*beg_ref != NULL)
    {
        Node* curr = *beg_ref;
        Node* prev = NULL;
        Node* next;
        while (curr != NULL)
        {
            if (curr->value == value)
            {
                counter++;
            }
            next = XOR(prev, curr->npx);
            prev = curr;
            curr = next;
        }
    }

    //Storing nodes to be deleted and later deleting them
    if (*beg_ref != NULL)
    {
        Node_to_be_Deleted* Nodes_tbD = new Node_to_be_Deleted[counter];
        Node* curr = *beg_ref;
        Node* prev = NULL;
        Node* next = NULL;

        //We are making array of Nodes that we will want to delete -
        //we are also storing their previous and next nodes
        int current_counter = 0;
        while (curr != NULL)
        {
            next = XOR(prev, curr->npx);

            if (curr->value == value)
            {
                Nodes_tbD[current_counter].before_tbD = prev;
                Nodes_tbD[current_counter].tbD = curr;
                Nodes_tbD[current_counter].after_tbD = next;
                current_counter++;
            }
            prev = curr;
            curr = next;
        }

        //Deleting that nodes
        for (int i = 0; i < counter; i++)
        {
            if (Nodes_tbD[i].tbD == *beg_ref)
            {
                DEL_BEG(&Beg, &End, &Act, &Prev, &Next);
            }
            else if (Nodes_tbD[i].tbD == *act_ref)
            {
                DEL_ACT(&Beg, &End, &Act, &Prev, &Next);
            }
            else if (Nodes_tbD[i].tbD == *end_ref)
            {
                DEL_END(&Beg, &End, &Act, &Prev, &Next);
            }
            else//if its "normal" (not beg, end, act) node
            {
                //Create temporary nodes (mainly for clarity)
                Node* tmp_prev_prev = XOR(Nodes_tbD[i].before_tbD->npx, Nodes_tbD[i].tbD);
                Node* tmp_prev = Nodes_tbD[i].before_tbD;
                Node* tmp_next = Nodes_tbD[i].after_tbD;
                Node* tmp_next_next = XOR(Nodes_tbD[i].after_tbD->npx, Nodes_tbD[i].tbD);

                //Update adresses that leads to excluding node to be deleted:
                tmp_prev->npx = XOR(tmp_prev_prev, tmp_next);
                tmp_next->npx = XOR(tmp_prev, tmp_next_next);
            }
        }
        delete[] Nodes_tbD;
    }
}

void MAINTAIN_INPUT(const string& text)
{
    int value;

    if (text == "ACTUAL")
    {
        ACTUAL(Act);
    }
    else if (text == "NEXT")
    {
        NEXT(&Beg, &Act, &Prev, &Next, 1);
    }
    else if (text == "PREV")
    {
        PREV(&End, &Act, &Prev, &Next, 1);
    }
    else if (text == "ADD_BEG")
    {
        cin >> value;
        ADD_BEG(&Beg, &End, &Act, &Prev, value);
    }
    else if (text == "ADD_END")
    {
        cin >> value;
        ADD_END(&Beg, &End, &Act, &Next, value);
    }
    else if (text == "ADD_ACT")
    {
        cin >> value;
        ADD_ACT(&Beg, &End, &Act, &Prev, &Next, value);
    }
    else if (text == "DEL_BEG")
    {
        DEL_BEG(&Beg, &End, &Act, &Prev, &Next);
    }
    else if (text == "DEL_END")
    {
        DEL_END(&Beg, &End, &Act, &Prev, &Next);
    }
    else if (text == "DEL_VAL")
    {
        cin >> value;
        DEL_VAL(&Beg, &End, &Act, value);
    }
    else if (text == "DEL_ACT")
    {
        DEL_ACT(&Beg, &End, &Act, &Prev, &Next);
    }
    else if (text == "PRINT_FORWARD")
    {
        PRINT_FORWARD(&Beg);
        cout << endl;
    }
    else if (text == "PRINT_BACKWARD")
    {
        PRINT_BACKWARD(&End);
        cout << endl;
    }
}

int main()
{
    string text;
    cin >> text;
    MAINTAIN_INPUT(text);

    while (getline(cin, text))
    {
        cin >> text;
        MAINTAIN_INPUT(text);
    }
    return 0;
}