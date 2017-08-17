include $(SRC_ROOT)/config.vars

OBJS=obj.o
FIB=fib
ALGOS=algos



all: algos misc hacker tester
	echo "all targets built....";

algos: heap
	$(CC) $(CC_FLAGS) algos.cpp ../data_structs/heap.o -o algos

misc:
	$(CC) -c -Wall misc.cpp -o misc.o
	$(CC) -Wall misc_driver.cpp misc.o -o misc_driver

hacker:
	$(CC) -Wall hackerrank.cpp ../data_structs/heap.o -o hacker

heap:
	# TODO :: GCC Command to build heap.o 

tester:
	$(CC) -Wall tester.cpp -o tester

clean:
	rm -v *.o algos hacker misc_driver