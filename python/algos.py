import utility as ut
import time
import argparse
import itertools
import copy
# import plot_mania as plt

# globals
DISPLAY_ARRS = False

def check_dupl_list(lstOfLst, lst):
	"""
		quick function to check if a list exists in a list of lists
		
		Args:
		    lstOfLst (list of lists): list of lists 
		    lst (list): single list of integers 
		
		Returns:
		    bool: true of list exists in lstOfLst 
	"""
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

def reverse_integer(n):
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
	if not check_dupl_list(result, arr):
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
def remove_duplicates(nums):
	"""
		inplace algorithm to remove duplicates from an input array.
		This approach starts with a pointer to the first index called 
		offset and another pointer on the next index. We count the number
		of common values. Once we find a different element we delete the 
		range of numbers and increment the offset as well as the index 
		next to offset index and repeat till we reach the end of the list.
		Note that the size of the list changes as well, decrements by the 
		number of elements deleted. 
		
		Args:
		    nums (list): list of numbers that are in order. List input is in order. smallest to 
		    	largest. 
		
		Returns:
		    int: size of modified list 
	"""
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

def max_profit(prices):
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

def rotate_array_r(nums, k):
	"""
		problem 189
		algorithm to inplace modify an input list rotating it to the right by k spots. 
		Worst Case O(kn): where n is length of input list 
		Memory: O(1)
		Args:
		    nums (list): list of elements 
		    k (int): number of spots to rotate by 
	"""
	# no need to rotate more than n times 
	sz = len(nums)
	if k > sz:
		k = k%sz
	for n in range(k):
		end_el = nums[-1] 
		for i in range(sz-1, -1, -1):
			nums[i] = nums[i-1]
		nums[0] = end_el

def rotate_array_l(nums, k):
	"""
		problem 189
		algorithm to inplace modify an input list rotating it to the left by k spots. 
		Worst Case O(kn): where n is length of input list 
		Memory: O(1)
		Args:
		    nums (list): list of elements 
		    k (int): number of spots to rotate by 
	"""
	# no need to rotate more than n times 
	if k > sz:
		k = k%sz
	for n in range(k):
		tmp = nums[0]
		for i in range(0, len(nums)-1):
			nums[i] = nums[i+1]
		nums[-1] = tmp

def rotate_array_r_v2(nums, k):
	"""
		problem 189
		this version is faster than v1 but uses O(n) more memory 
		
		Args:
		    nums (list): Description
		    k (int): number of rotations to make 
	"""
	sz = len(nums)
	k = k%sz
	tmp = nums[:]
	for i in range(0, sz):
		ii = i + k
		if ii >= sz:
			ii-=sz
		nums[ii] = tmp[i]

def contains_duplicate(nums):
	'''
		problem 217 
	'''
	if not len(nums):
		return False
	nums.sort()
	tmp = nums[0]
	for el in nums[1:]:
		if tmp == el:
			return True
		else:
			tmp = el
	return False

def single_number(nums):
	'''
		problem 136
		Given an array of integers, every element appears twice except for one. Find that single one
	'''
	sz = len(nums)
	if sz < 3:
		return 
	nums.sort()
	if nums[0]  != nums[1]:
		return nums[0]
	for i in range(0, sz-1, 2):
		if nums[i] != nums[i+1]:
			return nums[i]
	return nums[-1]

def intersection_of_arrays(nums1, nums2):
	"""
		Given two arrays, write a function to compute their intersection.
		Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].
    """
	result = [] 
	tmp_map = {} 
	len1 = len(nums1)
	len2 = len(nums2)
	(tmp, tmp2) = (nums1, nums2) if len1 > len2 else (nums2, nums1)
	# build value map showing number times an element appears 
	for el in tmp:
		if el not in tmp_map:
			tmp_map[el] = 1
		else:
			tmp_map[el] += 1
	# build intersection 
	for el in tmp2:
		if el in tmp_map:
			result.append(el)
			tmp_map[el]-=1
			if tmp_map[el] == 0:
				del tmp_map[el]
	return result




#----------------------------------------END-LEETCODE--------------------------------------------

if __name__ == '__main__':
	args = handle_args()
	n = 0
	while n <= 0:
		n = int( input('Enter arr size for sorting. Must be > 0\n') )
	arr = list(ut.generate_array(n))
	t0 = time.clock()
	bubble_sort( arr )
	t1 = time.clock()

	if DISPLAY_ARRS:
		print(f'result:\n{ut.arr_to_string(arr)}')
	print(f'total time for a bubble sort of an array of size { n }: {(t1-t0)*1000}msecs')

	print('\n\nfinding permutations of an array.\n\n')
	res = []
	lst = [1, 2, 3, 4, 5, 6, 8]
	perm(lst, 0, res)
	print(f'\n\nRESULT:')
	for permu in res:
		print(permu)
	print(f'RESULT size: {len(res)}\n')

