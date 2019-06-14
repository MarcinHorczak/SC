#include <mutex>

using namespace std;

class Producer {
    public:
        Producer(int arr_size, int number_of_elements, Queue *mainQueue, mutex *mtx);
        void produceData();
        int numberOfProducedData();
        bool finish();

    private:
        Queue *_queue;
        int _arr_size;
        int _number_of_produced_data = 0;
        int _number_of_elements;
        mutex *_mtx;
};
