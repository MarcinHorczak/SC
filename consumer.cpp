#include <mutex>
#include <iostream>
#include <boost/ptr_container/ptr_deque.hpp>
#include "header/queue.h"
#include "header/consumer.h"

using namespace std;
std::mutex mtx;

Consumer::Consumer(int arr_size, Queue *mainQueue){
    queue = mainQueue;
    _arrsize = arr_size;
}

void Consumer::consumeData() {
    mtx.lock();
    // int *p = queue -> mainQueue;
    // threads_vector.push_back(p);
    // std::cout << "TEST" << queue -> mainQueue.size() << std::endl;
    if (!queue -> isQueueEmpty()) {
        int *frontElement = queue -> mainQueue.front();
        sortFunction(frontElement);
        free(frontElement);
        queue -> mainQueue.pop_front();
    }
    mtx.unlock();
}

int Consumer::getNumberOfSortedElements() {
    return _sortedElements;
}

int* Consumer::sortFunction(int *table) {
    int temp;
    for(int i = 0; i < _arrsize; i++) {
        for(int j = i+1; j < _arrsize/10; j++)
        {
            // if(table[j] < table[i])
            // {
            //     temp = table[i];
            //     table[i] = table[j];
            //     table[j] = temp;
            // }
        }
    }
        
    _sortedElements++;

    return table;
}

