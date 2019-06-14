#include <iostream>
#include <boost/ptr_container/ptr_deque.hpp>
#include <mutex>
#include "header/queue.h"
#include "header/consumer.h"

using namespace std;

Consumer::Consumer(int arr_size, Queue *mainQueue, mutex *mtx){
    queue = mainQueue;
    _arrsize = arr_size;
    _mtx = mtx;
}

void Consumer::consumeData() {
    _mtx -> lock();
    if (!queue -> isQueueEmpty()) {
        Bufor bufor;
        bufor.isSorted = false;
        if (queue -> mainQueue.size() > _working_threads) {
            bufor.threads = queue -> mainQueue.at(_working_threads);
            threads_vector.push_back(bufor);
            _working_threads++;
        }
    }
    _mtx -> unlock();

    for (int i = 0; i < threads_vector.size(); i++) {
        if (!threads_vector.at(i).isSorted) {
            _mtx -> lock();
            threads_vector.at(i).isSorted = true;
            _mtx -> unlock();
            sortFunction(threads_vector.at(i).threads);
            queue -> mainQueue.pop_front();
            threads_vector.pop_front();
            _working_threads--;
            cout << "Consumed! Queue state: " << _sortedElements << endl;
        }
    }
}

int Consumer::getNumberOfSortedElements() {
    return _sortedElements;
}

int* Consumer::sortFunction(int *table) {
    int temp;
    for(int i = 0; i < _arrsize; i++) {
        for(int j = i+1; j < _arrsize/2; j++)
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

