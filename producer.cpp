#include <cstdlib>
#include "header/queue.h"
#include "header/producer.h"

using namespace std;

Producer::Producer(int arr_size, int number_of_elements, Queue *mainQueue) {
    _queue = mainQueue;
    _arr_size = arr_size;
    _number_of_elements = number_of_elements;
}

void Producer::produceData() {
    int* table = new int[_arr_size];

    for (int i = 0; i < _arr_size; i++) {
        table[i] = rand() % 1000;
    }

    _queue -> addToQueue(table);
    _number_of_produced_data++;
    _number_of_elements--;
}

bool Producer::finish() {
    if (_number_of_elements == 0) 
        return true;
    else
        return false;
}

int Producer::numberOfProducedData() {
    return _number_of_produced_data;
}
