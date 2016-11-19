#CC = g++ -std=c++0x
CC = g++ -std=c++11

algos:
	$(CC) -Wall algos.cpp ../data_structs/heap.o -o algos

misc:
	$(CC) -c -Wall misc.cpp -o misc.o
	$(CC) -Wall misc_driver.cpp misc.o -o misc_driver

clean:
	rm -v *.o algos

