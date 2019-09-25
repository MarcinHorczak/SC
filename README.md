# SC - Scientific Computing Study Project

## Project in C++. FIFO Queues using threads and MPI


**Meeting.0: Introduction, organization**

Introduction, regulations, platform enrollment, configuration of working environment.


**Meeting.1: Basics of C++  threads**

1. Using a global function, function object, class method, and lambda function create 4 threads that display on the screen information about the thread and an additional text (being an argument passed when creating a thread).

2. Create a global function that prints 50 times (each time on a separate line) the text passed as a function’s argument. Create 20 threads using this function. Using the mutex, ensure that messages output by threads will be placed in separate lines.

3. Create a function that increments 10000000 times a certain global integer variable. Measure the time of its one-time execution. Create a vector of 10 threads with this function. Check the time (std::chrono) and the effect of these threads on the incremented global variable. Use the <atomic> and <mutex> to ensure the correct result of the threads. Compare the operation times of the <atomic>, <mutex>, and unsynchronized variants (for the executable compiled in the debug and release configuration).


**Meeting.2,3: The producer and consumers scheme**

1. Create a Queue class representing a FIFO (first in first out) queue of length limited to the value passed as a constructor parameter, whose elements are arrays of ARRSIZE (=100000) integers. As an element of the Queue, You may use std::array<> or allocate arrays dynamically and use a unique_ptr<> or regular pointer.

2. Create the Producer class, which produces tables of ARRSIZE random integers and inserts them into the queue described in point 1 (queue passed as the argument of the constructor).

3. Create a Consumer class that takes tables from the queue (the queue passed as constructor argument) and sorts them (sorts a single table, outputs its checksum, discards it, and then takes the next one).

Producer and Consumer should yield() if the Queue is full or empty, respectively. Ensure that the cooperating threads properly finish their jobs and destruct (no produced table may be discarded prior to being sorted, Queue may be destructed only if it is empty and all the consumers and producers attached to it are destructed). At the end, each consumer should report how many tables it sorted.

4 Create: 1 Queue thread, 1 Producer thread, and several Consumer threads. Check what is the dependence of the speed of retrieving tables from the queue by consumers depending on number of created Consumers; is it beneficial to create a number of threads greater than thread::hardware_concurrency() or greater than the number of physical cores in the CPU?

**Lab.4: Basics of MPI**

1. Installing and using MPI in VisualStudio

Download from: https://docs.microsoft.com/en-us/message-passing-interface/microsoft-mpi

msmpisetup.exe - MS MPI for Windows
msmpisdk.msi - MPI SDK for Visual Studio

Install both, then check if the following environment variables are set:

MSMPI_BENCHMARKS=C:\Program Files\Microsoft MPI\Benchmarks\
MSMPI_BIN=C:\Program Files\Microsoft MPI\Bin\
MSMPI_INC=C:\Program Files (x86)\Microsoft SDKs\MPI\Include\
MSMPI_LIB32=C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x86\
MSMPI_LIB64=C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64\

Run Visual Studio, create Visual C++ Win32 Console Application 
In project properties (assuming we compile in x64 mode), set (or add) to Project->Your_project Properties->Configuration properties:

->C/C++->General->Additional Include Directories-> 	$(MSMPI_INC);$(MSMPI_INC)\x64
->Linker->General->Additional Library Directories->	$(MSMPI_LIB64)
->Linker->All Options->Additional Dependencies->	msmpi.lib

Now input the example MPI application code, compile it.

#include "mpi.h"
#include "stdafx.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	cout << "Hello from process " << rank << " out of " << size << endl;

	MPI_Finalize();

	return 0;
}

Running MPI executable app (number_of_processes defaults to the number of CPU cores; a firewall may require setting permissions at a first run of MPI executable):

mpiexec [–n number_of_processes] executable_file.exe

You may add a command to VS (Tools->External Tools->Add): 

Title: 		RunMPI
Command: 	c:\Program Files\Microsoft MPI\Bin\mpiexec.exe
Arguments: 	$(TargetName).exe
Initial Dir.: 	$(BinDir)
Close on exit:	unchecked

And then add it to the toolbar.

2. Write a program, that tests:
- point-to-point routines MPI_Send() and MPI_Recv() (but use also MPI_ANY_SOURCE for  the latter)
- non-blocking routines MPI_Isend() and MPI_Irecv() (use also MPI_Wait() and MPI_Test())
- MPI_Barrier()

3. Write a program, that finds the number of prime numbers smaller or equal then a given number. The program should find 78498 primes up to 1000000, 664579 up to 10^7, and 5761455 up to 10^8. Use MPI_Reduce() to sum numbers of primes found by MPI processes. Checking if a (positive) number is prime may be done by testing if the reminder from its division by successive numbers is 0:

int is_prime(int nr)
{
	if (nr < 2)
		return 0;
	for (int i = 2; i <= sqrt(int(nr)); i++)
		if (nr%i == 0)
			return 0;
	return 1;
}


**Lab.5,6: The producer and consumers scheme using MPI**

Port the producer-consumers program created using threads to the MPI environment. You may use only the point-to-point routines (with MPI_Recv() receiving MPI_ANY_SOURCE) or other routines as well. However, first use only blocking routines, if the scheme works correctly try to increase parallelism by employing non-blocking routines.
Check what is the dependence of the speed of retrieving tables from the queue by consumers depending on number of created Consumer processes and compare these results to the results obtained for C++ threads.

 
Links on MPI
https://www.codingame.com/playgrounds/349/introduction-to-mpi/introduction-to-distributed-computing
http://mpitutorial.com/tutorials/
http://miclab.pl/core/index.php/MICLAB:MPI [PL]
http://jedrzej.ulasiewicz.staff.iiar.pwr.wroc.pl/Komputery-i-Syst-Rownolegle/wyklad/MPI22.pdf [PL]

