import utility as ut
import time
import argparse
import plotMania as plt

def handleArgs():
	parser = argparse.ArgumentParser(description='this program takes input from user to analyze different algorithms'\
	                                 'If no args are passed then the program iterates through just one time'\
	                                 'taking input from the user. User can specify algorithms to analyze')
	parser.add_argument('-p', '--plot', type=bool, default=False
	                    help='specifying plot will render a plot showing execution time vs n elements') 
	parser.add_argument('-d', '--display', type=bool, help='displays the end result of the array', default=False)
	parser.add_argument('-a', '--algorithms', type=list, default=['bubbleSort']
	                    help='specify a list of algorithms to run during the analysis. Available algos ==> [bubbleSort]')
	return parser.parse_args()

def bubbleSort(arr, rev=False):
	'''
		this sorting function is ok as the array is being manipulated using indices only and not ranged iterations 
	'''
	changed = True 
	while changed:  # number of possible passes would be len(arr)
		changed = False
		for j in range(len(arr)-1):
			if not rev and (arr[j] > arr[j+1]):
				ut.swap(arr, j, j+1)
				changed = True

if __name__ == '__main__':
	n = 0
	while n <= 0:
		n = int( input('Enter arr size for sorting. Must be > 0\n') )

	arr = ut.generateArr(n)
	t0 = time.clock()
	bubbleSort(arr)
	t1 = time.clock()

	if DISPLAY_ARRS:
		print(f' result: {ut.arr2Str(arr)}')
	print(f'total time for a bubble sort of an array of size { len(arr) }: {(t1-t0)*1000}msecs')

