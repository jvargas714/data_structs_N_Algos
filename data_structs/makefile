tester:
	g++ -c -std=c++11 -Wall logger.cpp
	g++ -std=c++11 -Wall -DLOGGING_ON tester.cpp logger.o -o tester

scrap:
	g++ -std=c++11 -Wall scrap.cpp -o scrap

bin_tree:
	g++ -c -std=c++11 -Wall logger.cpp
	g++ -std=c++11 -Wall -DLOGGING_ON bin_tree.cpp logger.o -o bin_tree

scrap_stack:
	g++ -c -std=c++11 -Wall logger.cpp
	g++ -std=c++11 -Wall scrap_stack.cpp -o scrap_stack

linked_list:
	g++ -c -std=c++11 -Wall linked_list.cpp
	g++ -std=c++11 -Wall data_structs.cpp linked_list.o -o data_structs

heap:
	g++ -c -std=c++11 -Wall heap.cpp
	g++ -std=c++11 -Wall test_heap.cpp heap.o -o test_heap
	
clean:
	rm -v *.o
