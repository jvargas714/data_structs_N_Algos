
def swap(arr, i, j):
	tmp = arr[i] 
	arr[i] = arr[j] 
	arr[j] = tmp 

def findAbsPerm(n, k):
    """
	    Finds the absolute permuation netween 1...1 inclusive 
	    absolute permutation is defined as a permutation of [1...k]
	    in which every element in [1...k] when the absolute difference between 
	    the position of the element (use 1 based indexing) i = k 
	    (pos_i - i) == k for every element. Note that lexographically smaller 
	    means if we have [2, 1, 4, 6] and [2, 3, 4, 7] the first list is lexo 
	    smaller because 2, 1 would come before 2, 3 if they were placed in 
	    lexo order, kind of like alphabetical order 

	    Returns: list : permutation that fits the description above
    """
    if k == 0:
        return list(range(1, n+1))
    # need to somehow generate permuations and check them 

def perm(arr, basePos, result):
	'''
		[1, 2, 3, 4, 5]
		function that finds all permutations of a given list
	'''
	print(f'basePos: {basePos}')
	tmp = []
	if basePos >= len(arr):
		print('Index Error basePos out of range')
		return
	for i in range(0, len(arr)-1):
		swap(arr, i, basePos)
		print(arr)
		result.append([el for el in arr])
		basePos+=1
		if basePos >= len(arr): return 
		perm(arr, basePos, result)

res = []
lst = [1, 2, 3, 4]
perm(lst, 1, res)
print(f'RESULT size: {len(res)}')
for permu in res:
	print(permu)


