#include <boost/mpi.hpp>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <deque>

using namespace std;

int ARRSIZE = 100000;
int MAX_NUM_OF_EL = 5;
int NUMBER_OF_ELEMENTS = 10;
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
    
    /////////////////////
    // 0 - QUEUE
    /////////////////////
    if (world.rank() == 0) {
        std::deque<int*> mainQueue;
        int* table = new int[ARRSIZE];
        bool* consumer_ready = new bool[world.size() - 2];
        bool end = false;
        int index;
        int iter = 0;
        int sortedElements = 0;
        int producedElements = 0;
        double t1, t2; 
        boost::mpi::request req[40];
        req[0] = world.irecv(boost::mpi::any_source, 20, index);

        for (int i = 0; i < world.size() - 2; i++) {
            consumer_ready[i] = false;
        }

        t1 = MPI_Wtime(); 
        while (!end || mainQueue.size() > 0) {
            if (mainQueue.size() < MAX_NUM_OF_EL && producedElements < NUMBER_OF_ELEMENTS) {
                world.recv(1, 10, table, ARRSIZE);
                world.irecv(1, 100, end);
                mainQueue.push_back(table);
                producedElements++;
            }

            if (!mainQueue.empty()) {
                if (req[iter].test()) {
                    consumer_ready[index] = true;
                    iter++;
                    req[iter] = world.irecv(boost::mpi::any_source, 20, index);
                }
                for (int i = 0; i < world.size() - 2; i++) {
                    if (consumer_ready[i]) {
                        consumer_ready[i] = false;
                        world.send(i + 2, 21, false);
                        world.send(i + 2, 30, mainQueue.front(), ARRSIZE);
                        mainQueue.pop_front();
                        sortedElements++;
                        cout << "Consumed element: " << sortedElements << " " << mainQueue.size() << endl;
                    }
                }
            }
        }

        t2 = MPI_Wtime(); 
        printf( "Elapsed time is %f\n", t2 - t1 );

        for (int i = 2; i < world.size(); i++) {
            world.irecv(i, 20, index);
            world.isend(i, 21, true);
        }

        cout << "QUEUE END " << endl;
    }

    /////////////////////
    // 1 - PRODUCER
    /////////////////////
    if (world.rank() == 1) {
        for (int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
            int table[ARRSIZE];

            for (int i = 0; i < ARRSIZE; i++) {
                table[i] = rand() % 1000;
            }
            cout << "Produced: " << i + 1 << endl;
            world.send(0, 10, table, ARRSIZE);
        }
        world.send(0, 100, true);
    }

    /////////////////////
    // 2+ - CONSUMERS
    /////////////////////
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

        cout << "CONSUMER END: " << world.rank() << endl;
    }

    return 0;
}
