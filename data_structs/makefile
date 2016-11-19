#CC = g++ -std=c++0x
CC = g++ -std=c++11

tester:
	$(CC) -c -Wall logger.cpp
	$(CC) -Wall -DLOGGING_ON tester.cpp logger.o -o tester

scrap:
	$(CC) -Wall scrap.cpp -o scrap

bin_tree:
	$(CC) -c -Wall logger.cpp
	$(CC) -Wall -DLOGGING_ON bin_tree.cpp logger.o -o bin_tree

scrap_stack:
	$(CC) -c -Wall logger.cpp
	$(CC) -Wall scrap_stack.cpp -o scrap_stack

linked_list:
	$(CC) -c -Wall linked_list.cpp
	$(CC) -Wall data_structs.cpp linked_list.o -o data_structs

heap:
	$(CC) -c -Wall heap.cpp
	$(CC) -Wall test_heap.cpp heap.o -o test_heap
	
clean:
	rm -v *.o
