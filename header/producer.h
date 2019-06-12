class Producer {
    public:
        Producer(int arr_size, int number_of_elements, Queue *mainQueue);
        void produceData();
        int numberOfProducedData();
        bool finish();

    private:
        Queue *_queue;
        int _arr_size;
        int _number_of_produced_data = 0;
        int _number_of_elements;
};
