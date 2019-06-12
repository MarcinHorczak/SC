#include "header/queue.h"
#include "header/producer.h"
#include "header/consumer.h"
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <boost/thread.hpp>

using namespace std;

// Should be 100000
int ARRSIZE = 10000;
int MAX_NUM_OF_EL = 10;
int NUMBER_OF_ELEMENTS = 20;
int NUMBER_OF_THREADS = 4;

int main() {
    vector<boost::thread> consume_thread;
    srand(time(NULL));
    
    // cout << boost::thread::hardware_concurrency() << endl;
    // result: 4

    Queue *queue = new Queue(MAX_NUM_OF_EL);
    Producer producer(ARRSIZE, queue);
    Consumer consumer(ARRSIZE, queue);

    boost::thread producer_thread([&] {
        int i = 0;
        while (i < NUMBER_OF_ELEMENTS) {
            if ((*queue).isQueueFull()) {
                //cout << "Full" << endl;
                boost::this_thread::yield();
            } else {
                producer.produceData();
                cout << "Produced! Queue state: " << producer.numberOfProducedData() << " " << (*queue).queueSize() << endl;
                i++;
            }
        }
    });
    boost::thread consume_data([&] {
        int i = 0;
        while (i < NUMBER_OF_ELEMENTS) {
            if ((*queue).isQueueEmpty()) {
                boost::this_thread::yield();
            } else {
                consumer.consumeData();
                cout << "Consumed! Queue state: " << consumer.getNumberOfSortedElements() << endl;
                i++;
            }
        }
    });

    // for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    //     consume_thread.push_back(boost::thread([&]() 
    //     {
    //         int i = 0;
    //         while (i < NUMBER_OF_ELEMENTS) {
    //             if (queue.isQueueEmpty()) {
    //                 boost::this_thread::yield();
    //             } else {
    //                 consumer.consumeData();
    //                 i++;
    //             }
    //         }
    //     }
    //     ));
    // }
    
    
    producer_thread.join();
    consume_data.join();
    // for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    //     consume_thread[i].join();
    // }

    cout << "Number of sorted elements: " << consumer.getNumberOfSortedElements() << endl;

    return 0;
}
