
#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#define SIZE 10
class Queue {
private:
    int* arr;
    int capacity;
    int front;
    int rear;
    int count;

public:
    Queue(int size = SIZE);
    ~Queue();

    void dequeue();
    void enqueue(int item);
    int peek();
    int size();
    bool isEmpty();
    bool isFull();
};

#endif // QUEUE_H
