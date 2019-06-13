#include <boost/ptr_container/ptr_vector.hpp>

class Consumer {
    public:
        Consumer(int arr_size, Queue *mainQueue);

        void consumeData();

        int getNumberOfSortedElements();
    private:
        int* sortFunction(int *table);
        
        Queue* queue;
        int _sortedElements = 0;
        int _arrsize;
        boost::ptr_vector<int> threads_vector;
};
