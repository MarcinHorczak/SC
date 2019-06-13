#include <deque>

class Queue {
    public:
        Queue();
        Queue(int length);
        void addToQueue(int *table);
        int queueSize();
        bool isQueueEmpty();
        bool isQueueFull();
        std::deque<int*> mainQueue;
        int _length;
};
