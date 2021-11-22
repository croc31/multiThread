
all: matrizes processos sequencial thread

matrizes: matrizes.cpp
	g++ matrizes.cpp -o matrizes -Wall

processos: processos.cpp
	g++ processos.cpp -o processos -Wall

thread: thread.cpp
	g++ thread.cpp -o thread -Wall -pthread

sequencial: sequencial.cpp
	g++ sequencial.cpp -o sequencial -Wall

clean:
	rm-rf *.o *~ atv4