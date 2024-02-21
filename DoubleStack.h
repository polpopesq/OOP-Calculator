#pragma once

class DoubleStack {
private:
    double* data;
    int capacity;
    int size;

public:
    DoubleStack(int initialCapacity = 10);
    ~DoubleStack();
    bool isEmpty() const;
    int getSize() const;
    void push(double value);
    double pop();
    double peek() const;
};