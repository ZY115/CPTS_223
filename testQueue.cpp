
#include "queue.h"
#include "testQueue.h"
#include <cassert>

void testQueueSize() {
    Queue q(3);

    // Test Case 1: Empty queue size
    assert(q.size() == 0);

    // Test Case 2: Enqueue elements
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    assert(q.size() == 3);

    // Test Case 3: Dequeue elements
    q.dequeue();
    assert(q.size() == 2);
}

void testQueueIsEmpty() {
    Queue q(3);

    // Test Case 1: Empty queue
    assert(q.isEmpty());

    // Test Case 2: Enqueue elements
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    assert(!q.isEmpty());

    // Test Case 3: Dequeue elements
    q.dequeue();
    assert(!q.isEmpty());
}

void testQueueIsFull() {
    Queue q(2);

    // Test Case 1: Empty queue
    assert(!q.isFull());

    // Test Case 2: Enqueue elements
    q.enqueue(1);
    q.enqueue(2);
    assert(q.isFull());

    // Test Case 3: Dequeue elements
    q.dequeue();
    assert(!q.isFull());
}

void testQueueDequeue() {
    Queue q(3);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    // Test Case 1: Dequeue the first element
    q.dequeue();
    assert(q.size() == 2);
    assert(q.peek() == 2);

    // Test Case 2: Dequeue the second element
    q.dequeue();
    assert(q.size() == 1);
    assert(q.peek() == 3);

    // Test Case 3: Dequeue the last element
    q.dequeue();
    assert(q.size() == 0);
    assert(q.isEmpty());
}

void testQueueEnqueue() {
    Queue q(3);

    // Test Case 1: Enqueue elements
    q.enqueue(1);
    assert(q.size() == 1);
    assert(q.peek() == 1);

    q.enqueue(2);
    assert(q.size() == 2);
    assert(q.peek() == 1);

    q.enqueue(3);
    assert(q.size() == 3);
    assert(q.peek() == 1);

    // Test Case 2: Attempt to enqueue when the queue is full (should not change the state)
    q.dequeue(); // Dequeue one element to free up space
    q.enqueue(4); // Now, enqueue should work
    assert(q.size() == 3);
    assert(q.peek() == 2);
}

void testQueuePeek() {
    Queue q(3);
    q.enqueue(1);
    q.enqueue(2);

    // Test Case 1: Peek at the front element
    assert(q.peek() == 1);

    q.dequeue();

    // Test Case 2: Peek after dequeuing
    assert(q.peek() == 2);
}

int main() {
    testQueueSize();
    testQueueIsEmpty();
    testQueueIsFull();
    testQueueDequeue();
    testQueueEnqueue();
    testQueuePeek();

    return 0;
}
