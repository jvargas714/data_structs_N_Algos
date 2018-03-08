INC=-I. -I../../data_structs
OBJS=../../data_structs/linked_list.o problems.o
GCC=g++
CC_FLAGS=-Wall -std=c++11 
all:
	$(GCC) $(CC_FLAGS) $(INC) -c problems.cpp -o problems.o 
	$(GCC) $(CC_FLAGS) $(INC) main.cpp $(OBJS) -o main
	
clean:
	rm -v *.o main
