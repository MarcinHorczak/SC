class Consumer {
    public:
        Consumer(int arr_size, Queue *mainQueue);

        void consumeData();

        int getNumberOfSortedElements();
    private:
        int* sortFunction(int *table);
        
        Queue* queue;
        int _sortedElements;
        int _arrsize;
};
