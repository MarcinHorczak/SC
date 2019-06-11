all: queue.o producer.o main.o
	g++ bin/queue.o bin/producer.o bin/main.o -o a.out -pthread -lboost_system -lboost_thread && ./a.out

main.o: main.cpp
	g++ -c main.cpp -o bin/main.o 

producer.o: producer.cpp header/producer.h header/queue.h
	g++ -c producer.cpp -o bin/producer.o

queue.o: queue.cpp header/queue.h
	g++ -c queue.cpp -o bin/queue.o
