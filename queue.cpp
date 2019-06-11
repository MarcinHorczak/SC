#include "header/queue.h"
#include <queue>

using namespace std;

Queue::Queue() {}

Queue::Queue(int length) {
    _length = length;
}
        
void Queue::addToQueue(int *table) {
    if (mainQueue.size() <= _length) {
        mainQueue.push(table);
    }
}

bool Queue::isQueueEmpty() {
    if (mainQueue.empty())
        return true;
    else
        return false;
}

bool Queue::isQueueFull() {
    if (mainQueue.size() >= _length)
        return true;
    else
        return false;
}
