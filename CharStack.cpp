#include "CharStack.h"
#include <iostream>

using namespace std;

CharStack::CharStack(int initialCapacity) : capacity(initialCapacity), size(0) 
{
    data = new char[capacity];
}

CharStack::~CharStack() 
{
    delete[] data;
}

bool CharStack::isEmpty() const 
{
    return size == 0;
}

int CharStack::getSize() const 
{
    return size;
}

void CharStack::push(char value) 
{
    if (size == capacity) {
        capacity *= 2;
        char* newData = new char[capacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

    data[size++] = value;
}

char CharStack::pop() 
{
    if (isEmpty()) {
        cout << "Stiva char este goala!" << endl;
        return '\0';
    }

    return data[--size];
}

char CharStack::peek() const 
{
    if (isEmpty()) {
        cout << "Stiva char este goala!" << endl;
        return '\0'; 
    }

    return data[size - 1];
}