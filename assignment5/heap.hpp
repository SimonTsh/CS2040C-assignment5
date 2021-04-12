#pragma once
#include <math.h>

#include <iostream>
using namespace std;

#ifndef HEAPHPP
#define HEAPHPP

template <class T>
void Heap<T>::_bubbleUp(int index) {
    if (index) {
        int p = (index - 1) / 2;
        if (_heap[index] > _heap[p]) { // can change min heap or max heap
            swapItem(index, p);
            _bubbleUp(p);
        }
    }
}

template <class T>
void Heap<T>::_bubbleDown(int index) {
    int largest_index = index;
    int l_index = 2 * index + 1;
    int r_index = 2 * index + 2;
    // check if left node is larger than current node
    if ((l_index <= _n) && (_heap[l_index] > _heap[largest_index]))
        largest_index = l_index;

    // check if right node is larger than both current and left nodes
    if ((r_index <= _n) && (_heap[r_index] > _heap[largest_index]))
        largest_index = r_index;

    // perform swap for bubbling down
    if (largest_index != index) {
        swapItem(index, largest_index);
        _bubbleDown(largest_index);
    }
}

template <class T>
void Heap<T>::insert(T item) {
    _n++;
    _heap[_n - 1] = item; // insert item at the ned of heap array
    _bubbleUp(_n - 1);
}

template <class T>
T Heap<T>::extractMax() {
    T max = _heap[0];
    _heap[0] = _heap[_n - 1];
    _n--;
    _bubbleDown(0);
    return max;
}


template <class T>
void Heap<T>::printHeapArray() {
	for (int i = 0; i < _n; i++)
		cout << _heap[i] << " ";
	cout << endl;
}

template <class T>
int Heap<T>::_lookFor(T x){ // not a very good implementation, but just use this for now.
    int i;
    for(i=0;i<_n;i++)
        if (_heap[i] == x)
            return i;
    
    return -1;
}

template <class T>
void Heap<T>::decreaseKey(T from, T to)
{
    int idx = _lookFor(from);
    _heap[idx] = to;
    _bubbleDown(idx);
}

template <class T>
void Heap<T>::increaseKey(T from, T to)
{
    int idx = _lookFor(from);
    _heap[idx] = to;
    _bubbleUp(idx);
}

template <class T>
void Heap<T>::deleteItem(T x)
{
    int idx = _lookFor(x);
    int p = (idx - 1) / 2;
    swapItem(idx, _n - 1);
    _n--;

    if (_n > 0) {
        if (_heap[idx] > _heap[p])
            _bubbleUp(idx);
        else
            _bubbleDown(idx);
    }
}

template <class T>
void Heap<T>::swapItem(int idx1, int idx2)
{
    T temp = _heap[idx1];
    _heap[idx1] = _heap[idx2];
    _heap[idx2] = temp;
}

template <class T>
void Heap<T>::printTree() {
    int parity = 0;
	if (_n == 0)
		return;
	int space = pow(2,1 + (int) log2f(_n)),i;
	int nLevel = (int) log2f(_n)+1;
	int index = 0,endIndex;
    int tempIndex;
	
	for (int l = 0; l < nLevel; l++)
	{
		index = 1;
        parity = 0;
		for (i = 0; i < l; i++)
			index *= 2;
		endIndex = index * 2 - 1;
		index--;
        tempIndex = index;
        while (index < _n && index < endIndex) {
            for (i = 0; i < space-1; i++)
                cout << " ";
            if(index==0)
                cout << "|";
            else if (parity)
                cout << "\\";
            else
                cout << "/";
            parity = !parity;
            for (i = 0; i < space; i++)
                cout << " ";
			index++;
		}
        cout << endl;
        index=tempIndex;
		while (index < _n && index < endIndex) {
			for (i = 0; i < (space-1-((int) log10(_heap[index]))); i++)
				cout << " ";
			cout << _heap[index];
			for (i = 0; i < space; i++)
				cout << " ";
			index++;
		}
		
		cout << endl;
		space /= 2;
	}

}






#endif
