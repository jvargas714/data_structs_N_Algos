import sys, os
from collections.abc import Iterable
print(f'CWD: {os.getcwd()}')
import heapq
from typing import List

# ==================================================== Heaps ===========================================================
'''
    Heaps are binary trees for which every parent node has a value less than or equal to any of its children. 
    This implementation uses arrays for which heap[k] <= heap[2*k+1] and heap[k] <= heap[2*k+2] for all k, 
    counting elements from zero. For the sake of comparison, non-existing elements are considered to be infinite. 
    The interesting property of a heap is that its smallest element is always the root, heap[0].

    The API below differs from textbook heap algorithms in two aspects: (a) We use zero-based indexing. 
    This makes the relationship between the index for a node and the indexes for its children slightly 
    less obvious, but is more suitable since Python uses zero-based indexing. (b) 
    Our pop method returns the smallest item, not the largest (called a “min heap” 
    in textbooks; a “max heap” is more common in texts because of its suitability for in-place sorting).

    These two make it possible to view the heap as a regular Python list without surprises: 
    heap[0] is the smallest item, and heap.sort() maintains the heap invariant!

    # a heap can be created from a populated list using the heapify() function << Transform list x into a heap, in-place, in linear time.
    # min heap example 
    heap = heapq.heapify([1, 2, 3, 4, 5, 6, 7, 8])

    # heap can also be initialized simply by an empty list  [] 
    h = []
    heapq.heappush(h, 55) # push on to heap 
    heapq.heappush(heap, 99)
    heapq.heappop(heap)
    x = heapq.heappushpop(heap, 100)    # push item to heap and pops smallest element off (more efficient)
    print("x: ", x)

    # example how to perform a heap sort 
    # 
    def heapsort(iterable):
        h = []
        for value in iterable:
            heapq.heappush(h, value)
        return [heapq.heappop(h) for i in range(len(h))]


    # heapq.nlargest Return a list with the n largest elements from the dataset defined by iterable. key, if provided, 
    # specifies a function of one argument that is used to extract a comparison key from each element in 
    # iterable (for example, key=str.lower). Equivalent to: sorted(iterable, key=key, reverse=True)[:n].
    n = 3
    nlargestlst = heapq.nlargest(n, h, key=None)
    nsmallestlst = heapq.nsmallest(n, h, key=None)

    #--------------------------------------------------------- Queue -------------------------------------------------------------
    REF : https://docs.python.org/3/library/queue.html 

    - can use a deque from collections module 
    - can also use queue from queue module 
    - barebones simple queue in module queue is called SimpleQueue 

    Queue:
        - The queue module implements multi-producer, multi-consumer queues. This is useful for multithreaded applications 
        - this queue class implements all required locking semantics, depending on availability of threading mechanisms on the system
        - can do LIFO (stacklike) FIFO(queuelike) or a priority queue(uses heapq module, acts as a min heap)
        - In addition, the module implements a “simple” FIFO queue type, SimpleQueue, whose specific implementation 
            provides additional guarantees in exchange for the smaller functionality.
        - Classes 
            * class queue.Queue(maxsize=0)
            * class queue.LifoQueue(maxsize=0)
            * class queue.PriorityQueue(maxsize=0)
            * class queue.SimpleQueue   
                ** unbounded FIFO queue, lacks advanced functionality such as task tracking 
        - exception 
            * queue.Empty 
                ** Exception raised when non-blocking get() (or get_nowait()) is called on a Queue object which is empty.
            * queue.Full
                ** Exception raised when non-blocking put() (or put_nowait()) is called on a Queue object which is full. 
        - Object functions 
            * Queue.put(item, block=True, timeout=None)
            * Queue.full()
            * Queue.empty()
            * Queue.qsize()
            * Queue.get(block=True, timeout=None)
                ** Remove and return an item from the queue
            * Queue.get_nowait()
            * Queue.task_done()
                ** Indicate that a formerly enqueued task is complete. Used by queue consumer threads. For each get() used to fetch a task, a 
                    subsequent call to task_done() tells the queue that the processing on the task is complete
            * Queue.join()
                Blocks until all items in the queue have been gotten and processed.
    # ==================================================== COLLECTIONS ===========================================================
    import collections as col

    # namedtuple()	factory function for creating tuple subclasses with named fields

    # deque	list-like container with fast appends and pops on either end

    # ChainMap	dict-like class for creating a single view of multiple mappings

    # Counter	dict subclass for counting hashable objects

    # OrderedDict	dict subclass that remembers the order entries were added

    # defaultdict	dict subclass that calls a factory function to supply missing values

    # UserDict	wrapper around dictionary objects for easier dict subclassing

    # UserList	wrapper around list objects for easier list subclassing

    # UserString	wrapper around string objects for easier string subclassing
'''

# ==================================================== Scheduler ==========================================================================
'''
REF:  https://docs.python.org/3/library/sched.html
'''
# ==================================================== Personal Implementations ===========================================================
# FILO
class stack(object):
    # O(n)
    def __init__(self, iterable=None):
        self._data = []
        if iterable:
            for el in iterable:
                self._data.append(el)
    
    def get_size(self):
        ''' get size of stack O(1) '''
        return len(self._data)
    
    def pop(self):
        ''' return and remove item at top of stack O(1) '''
        if self._data:
            return self._data.pop()
        else:
            raise IndexError('no items left to pop of stack')
    
    def push(self, val):
        ''' add to stack O(1)'''
        self._data.append(val)
    
    def peek(self, val):
        ''' val at top of stack O(1) '''
        return self._data[len(self._data)]
    
    def clear(self):
        ''' remove all items from stack O(n) '''
        self._data.clear()
    
    def extend(self, iterable):
        ''' append supplied to stack O(k) '''
        self._data.extend(iterable)

    def __add__(self, stk):
        ''' addition operator extends underlying _data O(k) where k is len of input stk '''
        assert isinstance(stk, stack), 'input type must be stack'
        return stack(self._data + stk._data)

    def __sub__(self, stk):
        ''' addition operator extends underlying _data O(k) where k is len of input stk ''' 
        raise TypeError('unsupported operand')
    
    def __iter__(self):
        ''' returns an iterator object. '''
        return self

    def __next__(self):
        ''' iterating through class pops off the stack '''
        if not self._data:
            raise StopIteration
        return self.pop()
    
    def __eq__(self, stk):
        return self._data == stk._data

    def __ne__(self, stk):
        return self._data != stk._data
    
    def __lt__(self, stk):
        return self._data < stk._data
    
    def __gt__(self, stk):
        return self._data > stk._data
    
    def __le__(self, stk):
        return self._data <= stk._data
    
    def __ge__(self, stk):
        return self._data >= stk._data

    def __len__(self):
        return len(self._data)

    def __repr__(self):
        ''' to string for _data struct '''
        nl = '\n'
        return f'size: {len(self._data)} {nl}data: {self._data}'
    
    def __str__(self):
        nl = '\n'
        return f'size: {len(self._data)} {nl}data: {self._data} --> top of stack' 

# probably dont need, deque should cover our queue needs 
# FIFO
class queue(Iterable):
    def __init__(self, data=None):
        self._data = []
        if data:
            self._data.extend(data)
    
    def front(self):
        ''' check front of queue '''
        return 0
        

if __name__ == "__main__":
    print ('hello')
    data = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    stk = stack(data)
    print(f'{stk}')
    stk.push(10)
    stk.push(11)
    print(f' pop operation: {stk.pop()}')
    print(f' pop operation: {stk.pop()}')
    print(f' pop operation: {stk.pop()}')
    print(f' pop operation: {stk.pop()}')
    print(f'stk: {stk}')

    print('iterating though')
    for el in stk:
        print(f'el: {el}')
    print(f'stk: {stk}')

    stk.extend(data)
    stk2 = stack([10, 11, 12, 13, 14, 15, 16, 17])
    stk = stk + stk2
    print(f'After adding operation ==> {stk}')

