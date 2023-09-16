
#pragma once
#ifndef TESTQUEUE_H
#define TESTQUEUE_H


/*
Please note: All comments show the pre-fix state and results as required, with the aim of identifying the problem.
The current version of the code is fixed.

Passed test function:

testQueueSize(): the size of the queue is increased and decreased as expected during the test. Passed test.
testQueueIsEmpty(): the empty state of the queue changed as expected during the test. Passes the test.
testQueueIsFull(): the full state of the queue changes as expected during the test. Passes the test.

Failed test function:

testQueueDequeue(): although the size of the queue decreases as expected during the test, there may be a logic error somewhere as it does not remove elements from the queue as expected.
testQueueEnqueue(): there may be a logic error as it inserts the same element multiple times and may not properly check if the queue is full.
testQueuePeek(): this test function does not appear in your output, so its status cannot be determined.*/

/* Test ID: Empty queue check
Unit: queue::isEmpty ()
Description: Test to determine if queue::isEmpty () returns 1 if a queue object is empty

Test steps:
1. Construct an empty queue object
2. Invoke queue::isEmpty ()
3. Conditionally evaluate the value returned by queue::isEmpty ()

Test data: size = 0
Precondition: queue object is empty
Postcondition: queue object is still empty

Expected result: queue is empty; 1 is returned
*/

/* Test ID: Queue with elements check
Unit: queue::isEmpty ()
Description: Test to determine if queue::isEmpty () returns 0 if a queue object contains elements

Test steps:
1. Construct a queue object and enqueue elements
2. Invoke queue::isEmpty ()
3. Conditionally evaluate the value returned by queue::isEmpty ()

Test data: size > 0
Precondition: queue object contains elements
Postcondition: queue object is still not empty

Expected result: queue is not empty; 0 is returned
*/

/* Test ID: Full queue check
Unit: queue::isFull ()
Description: Test to determine if queue::isFull () returns true when the queue is full

Test steps:
1. Construct a queue object with limited capacity
2. Enqueue elements until the queue is full
3. Invoke queue::isFull ()
4. Conditionally evaluate the value returned by queue::isFull ()

Test data: size = capacity
Precondition: queue object is full
Postcondition: queue object is still full

Expected result: queue is full; true is returned
*/

/* Test ID: Not Full queue check
Unit: queue::isFull ()
Description: Test to determine if queue::isFull () returns false when the queue is not full

Test steps:
1. Construct a queue object with limited capacity
2. Enqueue fewer elements than the capacity
3. Invoke queue::isFull ()
4. Conditionally evaluate the value returned by queue::isFull ()

Test data: size < capacity
Precondition: queue object is not full
Postcondition: queue object is still not full

Expected result: queue is not full; false is returned
*/

/* Test ID: Dequeue from empty queue
Unit: queue::dequeue ()
Description: Test to determine if dequeueing from an empty queue handles underflow correctly

Test steps:
1. Construct an empty queue object
2. Invoke queue::dequeue ()
3. Check if underflow is handled correctly

Test data: size = 0
Precondition: queue object is empty
Postcondition: queue object is still empty

Expected result: Underflow is handled correctly
*/

/* Test ID: Dequeue from non-empty queue
Unit: queue::dequeue ()
Description: Test to determine if dequeueing from a non-empty queue removes elements correctly

Test steps:
1. Construct a queue object and enqueue elements
2. Invoke queue::dequeue ()
3. Check if the front element is removed

Test data: size > 0
Precondition: queue object is not empty
Postcondition: queue object has one less element

Expected result: Dequeue removes front element correctly
*/

/* Test ID: Peek on empty queue
Unit: queue::peek ()
Description: Test to determine if peeking into an empty queue handles underflow correctly

Test steps:
1. Construct an empty queue object
2. Invoke queue::peek ()
3. Check if underflow is handled correctly

Test data: size = 0
Precondition: queue object is empty
Postcondition: queue object is still empty

Expected result: Underflow is handled correctly
*/

/* Test ID: Peek on non-empty queue
Unit: queue::peek ()
Description: Test to determine if peeking into a non-empty queue returns the front element correctly

Test steps:
1. Construct a queue object and enqueue elements
2. Invoke queue::peek ()
3. Check if the front element is returned correctly

Test data: size > 0
Precondition: queue object is not empty
Postcondition: queue object is still not empty

Expected result: Peek returns front element correctly
*/

/* Test ID: Enqueue on full queue
Unit: queue::enqueue ()
Description: Test to determine if enqueuing into a full queue handles overflow correctly

Test steps:
1. Construct a queue object with limited capacity and enqueue elements until it's full
2. Invoke queue::enqueue ()
3. Check if overflow is handled correctly

Test data: size = capacity
Precondition: queue object is full
Postcondition: queue object is still full

Expected result: Overflow is handled correctly
*/

/* Test ID: Enqueue on non-full queue
Unit: queue::enqueue ()
Description: Test to determine if enqueuing into a non-full queue adds elements correctly

Test steps:
1. Construct a queue object with limited capacity and enqueue fewer elements than the capacity
2. Invoke queue::enqueue ()
3. Check if the element is added correctly

Test data: size < capacity
Precondition: queue object is not full
Postcondition: queue object has one more element

Expected result: Enqueue adds element correctly
*/


void testQueueSize();
void testQueueIsEmpty();
void testQueueIsFull();
void testQueueDequeue();
void testQueueEnqueue();
void testQueuePeek();

#endif 
