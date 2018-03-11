import random as rd
import time 

LINE_LIMIT = 25

def generate_array(n):
	'''
		generates an array of random numbers between -n .... n
	'''
	for i in range(n):
		yield rd.randint(0, i)

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
