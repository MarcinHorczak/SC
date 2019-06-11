#include <mutex>
#include "header/queue.h"
#include "header/consumer.h"

using namespace std;
std::mutex mtx;

Consumer::Consumer(int arr_size, Queue *mainQueue) {
    queue = *mainQueue;
    _arrsize = arr_size;
}

void Consumer::consumeData() {
    mtx.lock();
    int *frontElement = queue.mainQueue.front();
    sortFunction(frontElement);
    delete frontElement;
    queue.mainQueue.pop();
    mtx.unlock();
}

int Consumer::getNumberOfSortedElements() {
    return _sortedElements;
}

int* Consumer::sortFunction(int *table) {
    int temp;
    for(int i = 0; i < _arrsize; i++) {
        for(int j = i+1; j < _arrsize; j++)
        {
            if(table[j] < table[i])
            {
                temp = table[i];
                table[i] = table[j];
                table[j] = temp;
            }
        }
    }
        
    _sortedElements++;

    return table;
}
        
Queue queue;
int _sortedElements = 0;
int _arrsize;
