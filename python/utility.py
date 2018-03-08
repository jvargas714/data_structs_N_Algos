import random as rd

LINE_LIMIT = 25

def generateArr(n):
	'''
		generates an array of random numbers between -n .... n
	'''
	return [ rd.randint(-i, i) for i in range(n) ]

def arr2Str(arr):
	res = f'size: {len(arr)}\n' 
	cnt = 0
	for i in arr: 
		res += str(i) + ' '
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
