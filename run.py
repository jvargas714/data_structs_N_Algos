import time, random, os, sys
sys.path.extend(['python', 'hackerrank'])
import algos 
import utility as ut

if __name__ == '__main__':
	# x = list(ut.generate_array(20))
	
	k = 2

	print(f'Rotating Array size of {len(x)} to the Right by {k}')
	print (f'before:\n{x}')
	print(f'duplicates?? --> {algos.contains_duplicate(x)}')
	print(f'\nafter:\n{x}')

	# print(f'\n\nRotating Array to the Left by {k}')
	# print(f'before:\n{x}')
	# algos.rotate_array_l(x, k)
	# print(f'\nafter:\n{x}')

