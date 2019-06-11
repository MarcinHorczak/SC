class Producer {
    public:
        Producer(int arr_size, Queue mainQueue &);
        void produceData();
        int numberOfProducedData();

    private:
        Queue mainQueue;
        int _arr_size;
};
