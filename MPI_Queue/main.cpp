#include <boost/mpi.hpp>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <deque>

using namespace std;

int ARRSIZE = 100000;
int MAX_NUM_OF_EL = 10;
int NUMBER_OF_ELEMENTS = 20;
int NUMBER_OF_THREADS = 4;

void sortFunction(int *table) {
    int temp;
    for(int i = 0; i < ARRSIZE; i++) {
        for(int j = i+1; j < ARRSIZE/5; j++)
        {
            if(table[j] < table[i])
            {
                temp = table[i];
                table[i] = table[j];
                table[j] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    boost::mpi::environment env{argc, argv};
    boost::mpi::communicator world;
    
    // 0 - QUEUE
    if (world.rank() == 0) {
        std::deque<int*> mainQueue;
        int* table = new int[ARRSIZE];
        bool* consumer_ready = new bool[world.size() - 2];
        bool end = false;

        for (int i = 0; i < world.size() - 2; i++) {
            consumer_ready[i] = false;
        }

        while (!end || mainQueue.size() != 0) {
            if (mainQueue.size() < MAX_NUM_OF_EL) {
                world.recv(1, 10, table, ARRSIZE);
                world.irecv(1, 100, end);
                mainQueue.push_back(table);
            }
            if (!mainQueue.empty()) {
                int index;
                world.recv(boost::mpi::any_source, 20, index);
                world.send(index + 2, 21, false);
                consumer_ready[index] = true;

                for (int i = 0; i < world.size() - 2; i++) {
                    if (consumer_ready[i]) {
                        consumer_ready[i] = false;
                        world.send(i + 2, 30, mainQueue.front(), ARRSIZE);
                        mainQueue.pop_front();
                        cout << "Consumed element: " << mainQueue.size() << endl;
                    }
                }
            }
        }
        int index;

        for (int i = 0; i < world.size() - 2; i++) {
            world.recv(i + 2, 20, index);
            world.send(i + 2, 21, true);
        }
    }

    // 1 - PRODUCER
    if (world.rank() == 1) {
        for (int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
            int table[ARRSIZE];

            for (int i = 0; i < ARRSIZE; i++) {
                table[i] = rand() % 1000;
            }
            world.send(0, 10, table, ARRSIZE);
            cout << "Produced: " << i + 1 << endl;
        }
        world.send(0, 100, true);
    }

    // 2+ - CONSUMERS
    if (world.rank() >= 2) {
        int* table = new int[ARRSIZE];
        bool finish = false;
        
        while (!finish) {
            world.send(0, 20, world.rank() - 2);
            world.recv(0, 21, finish);
            if (!finish) {
                world.recv(0, 30, table, ARRSIZE);
                sortFunction(table);
            }
        }
    }

    return 0;
}
