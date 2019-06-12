#include <queue>

class Queue {
    public:
        Queue();
        Queue(int length);
        void addToQueue(int *table);
        int queueSize();
        bool isQueueEmpty();
        bool isQueueFull();


        std::queue<int*> mainQueue;
        int _length;
};
