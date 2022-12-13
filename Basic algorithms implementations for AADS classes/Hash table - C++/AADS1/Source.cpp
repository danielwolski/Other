#include <iostream>
#include <string>

using namespace std;

#define ARRAY_SIZE 100

struct Node
{
    string a = "";
    string b = "";
    int sum = 0;

    Node* next = NULL;
};

int hash_function(string* a, string* b)
{
    int hash = 0;

    for (int i = 0; i < a->length() && i < b->length(); i++)
    {
        hash = int((*a)[i]) + int((*b)[i]);
    }

    return hash % ARRAY_SIZE;
}

int main()
{
    Node* table = new Node[ARRAY_SIZE];

    string input, a, b;
    int value;

    while (cin >> input)
    {
        if (input == "+")
        {
            cin >> a >> b >> value;

            Node* current = &table[hash_function(&a, &b)];

            if (current->a == "" && current->b == "")
            {
                current->sum += value;
                current->a = a;
                current->b = b;
            }
            else if (a == current->a && b == current->b)
            {
                current->sum += value;
            }
            else if (a != current->a || b != current->b)
            {
                Node* actual = current;
                Node* prev = NULL;

                int did_found = 0;
                while (actual != NULL)
                {
                    if (a == actual->a && b == actual->b)
                    {
                        actual->sum += value;
                        did_found = 1;
                        break;
                    }

                    prev = actual;
                    actual = actual->next;
                }

                if (did_found == 0)
                {
                    Node* new_node = new Node;
                    new_node->a = a;
                    new_node->b = b;
                    new_node->sum += value;

                    prev->next = new_node;
                }
            }
        }
        else if (input == "?")
        {
            cin >> a >> b;

            Node* current = &table[hash_function(&a, &b)];

            if (current->a == "" && current->b == "")
            {
                cout << current->sum << endl;
            }
            else if (a == current->a && b == current->b)
            {
                cout << current->sum << endl;
            }
            else if (a != current->a || b != current->b)
            {
                Node* actual = current;
                Node* prev = NULL;

                int did_cout = 0;
                while (actual != NULL)
                {
                    if (actual->a == a && actual->b == b)
                    {
                        cout << actual->sum << endl;
                        did_cout = 1;
                        break;
                    }
                    prev = actual;
                    actual = actual->next;
                }

                if (did_cout == 0)
                    cout << 0 << endl;
            }
        }
    }
}