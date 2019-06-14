#include <mutex>
#include <deque>
#include <boost/ptr_container/ptr_vector.hpp>

using namespace std;

struct Bufor {
    int* threads;
    bool isSorted;
};

class Consumer {
    public:
        Consumer(int arr_size, Queue *mainQueue, mutex *mtx);

        void consumeData();

        int getNumberOfSortedElements();
    private:
        int* sortFunction(int *table);
        
        Queue* queue;
        int _sortedElements = 0;
        int _arrsize;
        std::deque<Bufor> threads_vector;
        mutex* _mtx;
        int _working_threads = 0;
};
