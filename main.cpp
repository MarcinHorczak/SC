#include "header/queue.h"
#include "header/producer.h"
#include <queue>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <mutex>
#include <boost/thread.hpp>

using namespace std;

// Should be 100000
int ARRSIZE = 10000;
int MAX_NUM_OF_EL = 30;
int NUMBER_OF_ELEMENTS = 50;
int NUMBER_OF_THREADS = 4;
mutex mtx;

class Consumer {
    public:
        Consumer(Queue& mainQueue): mainQueue(mainQueue) {}

        void consumeData() {
            mtx.lock();
            int *frontElement = mainQueue.mainQueue.front();
            sortFunction(frontElement);
            delete frontElement;
            mainQueue.mainQueue.pop();
            mtx.unlock();
        }

        int getNumberOfSortedElements() {
            return _sortedElements;
        }
    private:
        int* sortFunction(int *table) {
            int temp;
            for(int i = 0; i < ARRSIZE; i++) {
                for(int j = i+1; j < ARRSIZE; j++)
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

            cout << "Consumed: " << _sortedElements << endl;

            return table;
        }
        
        Queue &mainQueue;
        int _sortedElements = 0;
};

int main() {
    vector<boost::thread> consume_thread;
    srand(time(NULL));
    
    // cout << boost::thread::hardware_concurrency() << endl;
    // result: 4

    Queue queue(MAX_NUM_OF_EL);
    Producer producer(ARRSIZE, queue);
    Consumer consumer(queue);

    boost::thread producer_thread([&] {
        int i = 0;
        while (i < NUMBER_OF_ELEMENTS) {
            if (queue.isQueueFull()) {
                boost::this_thread::yield();
            } else {
                producer.produceData();
                cout << "Produced! Queue state: " << producer.numberOfProducedData() << endl;
                i++;
            }
        }
    });
    boost::thread consume_data([&] {
        int i = 0;
        while (i < NUMBER_OF_ELEMENTS) {
            if (queue.isQueueEmpty()) {
                boost::this_thread::yield();
            } else {
                consumer.consumeData();
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
