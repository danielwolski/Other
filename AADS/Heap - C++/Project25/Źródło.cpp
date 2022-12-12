#include <iostream>
#include <string>

using namespace std;

#define SIZE 65536

void Heapify(int* heap, int i, int size, int min_or_max_heap)
{
    if (min_or_max_heap == 1)
    {
        int maxps;

        int L = i * 2 + 1;
        int R = i * 2 + 2;
        if (L < size && heap[L] > heap[i])
            maxps = L;
        else
            maxps = i;
        if (R < size && heap[R] > heap[maxps])
            maxps = R;
        if (maxps != i)
        {
            swap(heap[i], heap[maxps]);
            Heapify(heap, maxps, size, min_or_max_heap);
        }
    }
    else if (min_or_max_heap == 2)
    {
        int minps;

        int L = i * 2 + 1;
        int R = i * 2 + 2;
        if (L < size && heap[L] < heap[i])
            minps = L;
        else
            minps = i;
        if (R < size && heap[R] < heap[minps])
            minps = R;
        if (minps != i)
        {
            swap(heap[i], heap[minps]);
            Heapify(heap, minps, size, min_or_max_heap);
        }
    }
}

void Heapify_for_add(int* heap, int i, int size, int min_or_max_heap)
{
    if (min_or_max_heap == 1)
    {
        int father = (i - 1) / 2;

        if (heap[i] > heap[father])
        {
            swap(heap[i], heap[father]);
            Heapify_for_add(heap, father, size, min_or_max_heap);
        }
    }
    else if (min_or_max_heap == 2)
    {
        int father = (i - 1) / 2;

        if (heap[i] < heap[father])
        {
            swap(heap[i], heap[father]);
            Heapify_for_add(heap, father, size, min_or_max_heap);
        }
    }
}

void add(int* heap, int& size, int v, int min_or_max_heap)
{
    heap[size] = v;
    size++;

    Heapify_for_add(heap, size - 1, size, min_or_max_heap);
}

int remove(int* heap, int& size, int min_or_max_heap)
{
    int tmp = heap[0];
    heap[0] = heap[size - 1];
    size--;
    Heapify(heap, 0, size, min_or_max_heap);

    return tmp;
}

void r(int* heap, int* arr, int& size, int min_or_max_heap)
{
    for (int i = 0; i < size; i++)
        cin >> arr[i];

    for (int i = size; i >= 0; i--)
        Heapify(arr, i, size, min_or_max_heap);

    for (int i = 0; i < size; i++)
        heap[i] = arr[i];
}

void s(int* heap, int& size, int& min_or_max_heap)
{
    if (min_or_max_heap == 1)
        min_or_max_heap = 2;
    else if (min_or_max_heap == 2)
        min_or_max_heap = 1;

    for (int i = size; i >= 0; i--)
        Heapify(heap, i, size, min_or_max_heap);
}


int main()
{
    int heap[SIZE];

    string input;
    int heap_size = 0;
    int max_or_min = 1;//1 for max heap, 2 for min heap

    while (input != "q")
    {
        cin >> input;

        if (input == "+")
        {
            int v;
            cin >> v;
            add(heap, heap_size, v, max_or_min);
        }
        else if (input == "-")
        {
            if (heap_size > 0)
                cout << remove(heap, heap_size, max_or_min) << endl;
        }
        else if (input == "p")
        {
            for (int i = 0; i < heap_size; i++)
                cout << heap[i] << " ";
            cout << endl;
        }
        else if (input == "r")
        {
            int n;
            cin >> n;
            int* arr = new int[n];

            heap_size = n;
            r(heap, arr, heap_size, max_or_min);

            delete[] arr;
        }
        else if (input == "s")
        {
            s(heap, heap_size, max_or_min);
        }
    }

    return 0;
}