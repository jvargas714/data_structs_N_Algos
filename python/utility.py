import random as rd
import time
from leetcode.treenode import TreeNode

LINE_LIMIT = 25

def generate_array(n):
	'''
		generates an array of random numbers between -n .... n
	'''
	for i in range(n):
		yield rd.randint(0, n*100)

def arr_to_string(arr):
	'''
		displays array in a lined up grid
		* * * * *
		* * * * *
		* * * * *
	'''
	res = f'size: {len(arr)}\n'
	cnt = 0
	spc_cnt = len( str( len(arr) ) )
	for i in arr:
		spaces = spc_cnt-len(str(i)) + 1
		res += str(i) + ''.join( [' ' for x in range( spaces )] )
		cnt += 1
		if cnt == LINE_LIMIT:
			res += '\n'
			cnt = 0
	return res

def swap(arr, i, j):
	'''
		swaps element in index i with element in index j
	'''
	tmp = arr[i]
	arr[i] = arr[j]
	arr[j] = tmp

def time_execution(func_obj, args=None):
	'''
		times execution of provided function
		args would be a tuple of the arguments that would be used for the function
	'''
	try:
		if not args:
			t0 = time.clock()
			func_obj()
			t1 = time.clock()
		else:
			t0 = time.clock()
			func_obj(*args)
			t1 = time.clock()
	except Exception as e:
		print(f'Error executing function object.\n\ntype: \
			      	{exc_info()[0]}, \n\nvalue:{exc_info()[1]}')
	return str(f'Time of Execution: {round((t1-t0)*1000, 3)}msecs\n')

def generate_random_matrix(m, n, max_val):
    """
    Generates a matrix of size m x n of random size. Where m is the size of the row
    Args:
        m (int): num of rows
        n (int): num of cols
        max_val(int): max val of element in the matrix
    """
    matrix = []
    for i in range(n):
    	row = []
    	for j in range(m):
    		row.append(rd.randint(0, max_val))
    	matrix.append(row)
    return matrix

def logical_left_shift(arr, n):
	"""
	    A left shift of an array by n places, zeros are shifted in

	    Args:
	        arr (list): list to be shifted
	        n (int): number of shifts
    """
	print(arr)
	for x in range(n):
		for i in range(len(arr)-1):
			arr[i] = arr[i+1]
		arr[len(arr)-1] = 0
		print(arr)

def logical_right_shift(arr, n):
	"""
	    A right shift of an array by n places, zeros are shifted in

	    Args:
	        arr (list): list to be shifted
	        n (int): number of shifts
    """
	print(arr)
	for x in range(n):
		for i in range(len(arr)-1, 0, -1):
			arr[i] = arr[i-1 ]
		arr[0] = 0
		print(arr)

