#include "DoubleStack.h"
#include <iostream>

using namespace std;

    DoubleStack::DoubleStack(int initialCapacity) : capacity(initialCapacity), size(0) {
        data = new double[capacity];
    }
    
    DoubleStack::~DoubleStack() {
        delete[] data;
    }

    bool DoubleStack::isEmpty() const {
        return size == 0;
    }

    int DoubleStack::getSize() const {
        return size;
    }

    void DoubleStack::push(double value) {
        if (size == capacity) {
            capacity *= 2;
            double* newData = new double[capacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }

        data[size++] = value;
    }

    double DoubleStack::pop() {
        if (isEmpty()) {
            //cout << "Stiva double este goala!" << endl;
            return 0.0;
        }

        return data[--size];
    }

    double DoubleStack::peek() const {
        if (isEmpty()) {
            cout << "Stiva double este goala!" << endl;
            return 0.0;
        }

        return data[size - 1];
    }