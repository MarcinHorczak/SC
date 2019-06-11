#include <cstdlib>
#include "header/queue.h"

using namespace std;

Producer::Producer(int arr_size, Queue mainQueue &): mainQueue(mainQueue) {
    _arr_size = arr_size;
}

void Producer::produceData() {
    int* table = new int[_arr_size];

    for (int i = 0; i < _arr_size; i++) {
        table[i] = rand() % 1000;
    }

    mainQueue.addToQueue(table);
}

int Producer::numberOfProducedData() {
    return mainQueue.mainQueue.size();
}

Queue mainQueue;
int _arr_size;