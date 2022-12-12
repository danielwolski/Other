#include<iostream>
#include<string>

using namespace std;

struct komorka_stosu
{
    int wartosc;
    komorka_stosu* poprzednia;
};

void push(komorka_stosu** wierzch_stosu, int liczba)
{
    komorka_stosu* nowa = new komorka_stosu;
    nowa->wartosc = liczba;
    nowa->poprzednia = *wierzch_stosu;
    *wierzch_stosu = nowa;
}

int top(komorka_stosu** wierzch_stosu)
{
    komorka_stosu* temp = *wierzch_stosu;
    *wierzch_stosu = (*wierzch_stosu)->poprzednia;
    return temp->wartosc;
}


int main()
{
    int n;
    cin >> n;
    komorka_stosu* wierzch_stosu = NULL;

    for (int x = 0; x < n; x++)
    {
        string RPN;
        cin >> RPN;
        int a, b;

        for (int i = 0; i < RPN.size(); i++)
        {
            if (RPN[i] == 't')
                push(&wierzch_stosu, 1);

            if (RPN[i] == 'f')
                push(&wierzch_stosu, 0);

            if (RPN[i] == 'A')
            {
                a = top(&wierzch_stosu);
                b = top(&wierzch_stosu);
                push(&wierzch_stosu, a || b);
            }

            if (RPN[i] == 'K')
            {
                a = top(&wierzch_stosu);
                b = top(&wierzch_stosu);
                push(&wierzch_stosu, a && b);
            }

            if (RPN[i] == 'N')
            {
                a = top(&wierzch_stosu);
                push(&wierzch_stosu, !a);
            }
        }

        int result = top(&wierzch_stosu);

        if (result == 1)
            cout << "t" << endl;

        if (result == 0)
            cout << "f" << endl;
    }
}