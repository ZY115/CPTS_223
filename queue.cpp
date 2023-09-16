
#include "queue.h"
#include <iostream>
#include <limits>

Queue::Queue(int size) {
    arr = new int[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
}

Queue::~Queue() {
    delete[] arr;
}

void Queue::dequeue() {
    if (isEmpty()) {
        std::cout << "Underflow\nProgram Terminated\n";
        return;
    }

    std::cout << "Removing " << arr[front] << '\n';

    front = (front + 1) % capacity;
    count--;
}

void Queue::enqueue(int item) {
    if (isFull()) {
        std::cout << "Overflow\nProgram Terminated\n";
        return;
    }

    std::cout << "Inserting " << item << '\n';

    rear = (rear + 1) % capacity;
    arr[rear] = item;
    count++;
}

int Queue::peek() {
    if (isEmpty()) {
        std::cout << "Underflow\nProgram Terminated\n";
        return std::numeric_limits<int>::min();
    }
    return arr[front];
}

int Queue::size() {
    return count;
}

bool Queue::isEmpty() {
    return (size() == 0);
}

bool Queue::isFull() {
    return (size() == capacity);
}
