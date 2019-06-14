#include <cstdlib>
#include <mutex>
#include <iostream>
#include "header/queue.h"
#include "header/producer.h"

using namespace std;

Producer::Producer(int arr_size, int number_of_elements, Queue *mainQueue, mutex *mtx) {
    _queue = mainQueue;
    _arr_size = arr_size;
    _number_of_elements = number_of_elements;
    _mtx = mtx;
}

void Producer::produceData() {
    int* table = new int[_arr_size];

    for (int i = 0; i < _arr_size; i++) {
        table[i] = rand() % 1000;
    }
    _mtx -> lock();
    _queue -> addToQueue(table);
    _mtx -> unlock();
    _number_of_produced_data++;
    _number_of_elements--;
    
    cout << "Produced: " << _number_of_produced_data << endl;
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
