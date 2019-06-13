all: queue.o producer.o consumer.o main.o
	g++ bin/queue.o bin/producer.o bin/consumer.o bin/main.o -o a.out -pthread -lboost_system -lboost_thread -w && ./a.out

main.o: main.cpp
	g++ -c main.cpp -o bin/main.o 

consumer.o: consumer.cpp header/consumer.h header/queue.h
	g++ -c consumer.cpp -o bin/consumer.o

producer.o: producer.cpp header/producer.h header/queue.h
	g++ -c producer.cpp -o bin/producer.o

queue.o: queue.cpp header/queue.h
	g++ -c queue.cpp -o bin/queue.o
