#include <queue>

class Queue {
    public:
        Queue();
        Queue(int length);
        void addToQueue(int *table);
        bool isQueueEmpty();
        bool isQueueFull();

        std::queue<int*> mainQueue;
        int _length;
};
