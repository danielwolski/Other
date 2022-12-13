#include <iostream>
#include <string>

using namespace std;

int compare(string x, string y)
{
    if (x.size() > y.size())
        return 0;
    else if (x.size() < y.size())
        return 1;
    else if (x.size() == y.size())
    {
        for (int i = 0; i < x.size(); i++)
        {
            if (x[i] > y[i])
                return 0;
            else if (x[i] < y[i])
                return 1;
        }
    }
    return 0;
}

void ShellSort(string A[], int n)
{
    int k = n / 2;
    while (k >= 1)
    {
        for (int i = k; i < n; i++)
        {
            string x = A[i];
            int j = i;
            while (j >= k && compare(x, A[j - k]) == 1)
            {
                A[j] = A[j - k];
                j = j - k;
            }
            A[j] = x;
        }
        k = k / 2;
    }
}

int main()
{
    int n;
    cin >> n;
    string* arr = new string[n];

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    ShellSort(arr, n);

    for (int i = 0; i < n; i++)
        cout << arr[i] << endl;

    return 0;
}