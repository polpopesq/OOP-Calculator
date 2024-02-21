#pragma once
class CharStack {
private:
    char* data;
    int capacity;
    int size; 

public:
    CharStack(int initialCapacity = 10);
    ~CharStack();
    bool isEmpty() const;
    int getSize() const;
    void push(char value);
    char pop();
    char peek() const;
};