#!/Users/jayvargas/anaconda/bin/python
import utility as ut
import time
import argparse
import plot_mania as plt

# globals
DISPLAY_ARRS = False

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

