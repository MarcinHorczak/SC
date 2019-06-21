#include "header/queue.h"
#include "header/producer.h"
#include "header/consumer.h"
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <mutex>
#include <boost/thread.hpp>

using namespace std;

// Should be 100000
int ARRSIZE = 100000;
int MAX_NUM_OF_EL = 10;
int NUMBER_OF_ELEMENTS = 20;
int NUMBER_OF_THREADS = 4;
std::mutex *mtx = new mutex();

int main() {
    vector<boost::thread> consume_thread;
    srand(time(NULL));
    
    // cout << boost::thread::hardware_concurrency() << endl;

    Queue *queue = new Queue(MAX_NUM_OF_EL);
    Producer producer(ARRSIZE, NUMBER_OF_ELEMENTS, queue, mtx);
    Consumer consumer(ARRSIZE, queue, mtx);

    auto start = chrono::system_clock::now();

    boost::thread producer_thread([&] {
        int i = 0;
        while (i < NUMBER_OF_ELEMENTS) {
            if (queue -> isQueueFull()) {
                boost::this_thread::yield();
            } else {
                producer.produceData();
                i++;
            }
        }
    });

    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        consume_thread.push_back(
            boost::thread([&]() 
                {
                    while (!producer.finish() || !queue -> isQueueEmpty()) {
                        if (queue -> isQueueEmpty() && !producer.finish()) {
                            boost::this_thread::yield();
                        } else {
                            consumer.consumeData();
                        }
                    }
                }
            )
        );
    }
    
    
    producer_thread.join();
    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        consume_thread[i].join();
    }

    free(queue);

    cout << "Number of sorted elements: " << consumer.getNumberOfSortedElements() << endl;

    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time: " << elapsed.count() << endl;

    delete(queue);
    return 0;
}
