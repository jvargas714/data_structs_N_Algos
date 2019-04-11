import heapq

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
'''
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
