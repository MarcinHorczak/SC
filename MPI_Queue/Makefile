all: main.o
	mpiCC main.o -o a.out -lboost_mpi -lboost_serialization -w && mpiexec -n 5 ./a.out

main.o: main.cpp
	mpiCC -c main.cpp -o main.o 
