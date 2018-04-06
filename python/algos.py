import utility as ut
import time
import argparse
import itertools
# import plot_mania as plt

# globals
DISPLAY_ARRS = False

def checkForDupLst(lstOfLst, lst):
	for lst_el in lstOfLst:
		if lst_el == lst:
			return True
	return False

def handle_args():
	parser = argparse.ArgumentParser(description='this program takes input from user to analyze different algorithms'\
									 'If no args are passed then the program iterates through just one time'\
									 'taking input from the user. User can specify algorithms to analyze')
	parser.add_argument('-p', '--plot', type=bool, default=False, 
						help='specifying plot will render a plot showing execution time vs n elements') 
	parser.add_argument('-d', '--display', type=bool, help='displays the end result of the array', default=False)
	parser.add_argument('-a', '--algorithms', type=list, default=['bubbleSort'],
						help='specify a list of algorithms to run during the analysis. Available algos ==> [bubbleSort]')
	return parser.parse_args()

def swap(arr, i, j):
	tmp = arr[i] 
	arr[i] = arr[j] 
	arr[j] = tmp 

def swap_cpy(arr, i, j):
	tmp = [el for el in arr]
	swap(tmp, i, j)
	return tmp

def bubble_sort(arr, rev=False):
	'''
		Worst Case: O(n^2)
		this sorting function is ok as the array is being manipulated using indices only and not ranged iterations 
	'''
	changed = True 
	while changed:  # number of possible passes would be len(arr)
		changed = False
		for j in range(len(arr)-1):
			if not rev and (arr[j] > arr[j+1]):
				ut.swap(arr, j, j+1)
				changed = True
				continue

			if rev and (arr[j] < arr[j+1]):
				ut.swap(arr, j, j+1)
				changed = True
			
def insertion_sort(arr, rev=False):
	'''
		Worst Case: O(n^2)
		take an element and insert it into the list where it belongs 
				j i
		[ * * * * * * ]
	''' 
	for i in range(1, len(arr)):
		j = i-1
		val_to_insert_j = arr[j]
		while ( j > 0 and val_to_insert_j > arr[i] ):
			ut.swap(arr, i, i-1)
			i-=1
			j-=1

def reverseInteger(n):
	"""
	Algorithm to reverse provided integer, n=12345678 result=87654321
	
	Args:
		n (Integer): integer value to be reversed 
	"""
	pwr = 10
	nums = [] 
	result = 0
	while n>0:  # n = 458. 8: 10     5 : 100     4 : 1000. [4 5 8]
		nums.append(n%pwr)
		n = int(n/10)
	pwr = pow(10, len(nums)) / 10 
	for num in nums:
		result += num*pwr
		pwr/=10
	return int(result)

def perms(arr, baseInd, result):
	'''can just use list(itertools.permutations(arr))'''
	if not checkForDupLst(result, arr):
		result.append(arr)
	subperms = [arr]
	if len(result) == fact(len(arr)) or baseInd == len(arr): 
		return
	for i in range(baseInd, len(arr)):
		if i == baseInd: continue 
		tmp = swap_cpy(arr, baseInd, i)
		subperms.append(tmp)
	baseInd+=1
	for lst in subperms:
		perm2(lst, baseInd, result)

def fact(n):
	result = 1
	for i in range(2, n+1): result*=i

def all_perms(elements):
	if len(elements) <=1:
		yield elements
	else:
		for perm in all_perms(elements[1:]):
			for i in range(len(elements)):
				# nb elements[0:1] works in both string and list contexts
				yield perm[:i] + elements[0:1] + perm[i:]

#----------------------------------------LeetCode------------------------------------------------
def removeDuplicates(nums):
	sz = len(nums)
	if not sz:
		return 0
	if sz == 1:
		return 1

	offset = 0 
	cnt = 0 
	i = offset+1
	while i<sz:
		if nums[offset] == nums[i]:
			cnt+=1
			i+=1
		else:
			del nums[offset:offset+cnt]
			sz-=cnt
			cnt=0
			offset+=1
			i=offset+1
	del nums[offset:offset+cnt]
	return len(nums)

def maxProfit(prices):
	profits = 0 
	ln = len(prices)
	if not ln:
		return 0
	elif ln == 2:
		return (prices[1]-prices[0]) if prices[1] > prices[0] else 0
	lastPrice = prices[0]
	for price in prices:
		if lastPrice < price:
			profits+= (price-lastPrice)
		lastPrice = price
	return profits

def _swap(nums, x, y, cnt):
	if cnt == (len(nums)-1):
		return
	


def rotateArrayR(nums, k):
	 _swap(nums, 0, k, 0)

def rotateArrayL(nums, k):
	pass
#----------------------------------------END-LEETCODE--------------------------------------------

if __name__ == '__main__':
	# args = handle_args()
	# n = 0
	# while n <= 0:
	# 	n = int( input('Enter arr size for sorting. Must be > 0\n') )
	# arr = list(ut.generate_array(n))
	# t0 = time.clock()
	# bubble_sort( arr )
	# t1 = time.clock()

	if DISPLAY_ARRS:
		print(f'result:\n{ut.arr_to_string(arr)}')
	# print(f'total time for a bubble sort of an array of size { n }: {(t1-t0)*1000}msecs')

	res = []
	lst = [1, 2, 3, 4, 5, 6, 8]
	perm(lst, 0, res)
	print(f'\n\nRESULT:')
	for permu in res:
		print(permu)
	print(f'RESULT size: {len(res)}\n')

