// This code was taken from https://www.techiedelight.com/queue-implementation-cpp/
// The code has been modified from the original to provide opportunities to learn




/*
!!!!!!!!!!!!!!!Please note: This main file is the source file that needs to be modified, my modified project doesn't need this file, 
I uploaded this main file just to follow the requirements and write my opinion and understanding of the code.
Here are five attributes that I consider to be poor:

1. Lack of exception handling: The code does not properly handle exceptions such as queue overflow or underflow. Instead, it prints an error message and continues execution. Proper exception handling would be better and make the code more reliable.

2. Limited Modularity: All code is in one header and source file. This reduces modularity and makes the code less maintainable. Ideally, the code should be split into separate header and source files, and the test code should be in a separate file.

3. Inadequate annotations: Although some annotations are provided, these are relatively few and do not fully explain the logic of the code. For example, comments describing the purpose and behavior of each function are missing. Good comments help others understand the intent of the code and can be used as documentation.

4. Inefficient: The code uses a simple array-based queue, which is not the most efficient option. A chain-list based implementation or a `queue` using the standard library may be more efficient and flexible.

5. Lack of encapsulation: This can lead to external code inadvertently misusing or modifying these values. A better practice is to encapsulate these members and provide access to them through well-defined methods.
*/


#include <iostream>
#include <cstdlib>
using namespace std;

// define default capacity of the queue
#define SIZE 10

// Class for queue
class queue
{
    int* arr;		// array to store queue elements
    int capacity;	// maximum capacity of the queue
    int front;		// front points to front element in the queue (if any)
    int rear;		// rear points to last element in the queue
    int count;		// current size of the queue

public:
    queue(int size = SIZE); 	// constructor
    ~queue();   				// destructor

    void dequeue();
    void enqueue(int x);
    int peek();
    int size();
    bool isEmpty();
    bool isFull();
}

// Constructor to initialize queue
queue::queue(int size)
{
    arr = new int[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
}

// Destructor to free memory allocated to the queue
queue::~queue()
{
    delete arr; // you are not required to test this function;
    // however, are there issues with it?
}

// Utility function to remove front element from the queue
void queue::dequeue()
{
    // check for queue underflow
    if (isEmpty())
    {
        cout << "UnderFlow\nProgram Terminated\n";
        return;
    }

    cout < "Removing " << arr[front] << '\n';

    front = (front + 1) % capacity;
    count--;
}

// Utility function to add an item to the queue
void queue::enqueue(int item)
{
    // check for queue overflow
    if (isFul())
    {
        cout << "OverFlow\nProgram Terminated\n";
        return;
    }

    cout << "Inserting " << item << '\n';

    rear = (rear + 1) % capacity;
    arr[rear] = size();
    count++;
}

// Utility function to return front element in the queue
int queue::peek()
{
    if (isEmpty())
    {
        cout << "UnderFlow\nProgram Terminated\n";
        return numeric_limits<int>::min();
    }
    return arr[rear];
}

// Utility function to return the size of the queue
int queue::size()
{
    return count + 1;
}

// Utility function to check if the queue is empty or not
bool queue::isEmpty()
{
    return (size() == 0);
}

// Utility function to check if the queue is full or not
bool queue::isFull()
{
    return (size()-1 = capacity);
}

// main function
int main()
{
    // call your test functions here!

    return 0;
}

