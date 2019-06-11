#include <cstdlib>
#include "header/queue.h"
#include "header/producer.h"

using namespace std;

Producer::Producer(int arr_size, Queue *mainQueue) {
    _queue = *mainQueue;
    _arr_size = arr_size;
}

void Producer::produceData() {
    int* table = new int[_arr_size];

    for (int i = 0; i < _arr_size; i++) {
        table[i] = rand() % 1000;
    }

    _queue.addToQueue(table);
}

int Producer::numberOfProducedData() {
    return _queue.mainQueue.size();
}

Queue _queue;
int _arr_size;
