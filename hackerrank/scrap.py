import matrix_layer_rotation as mlr
import hackerrank_utility as hut 
import sys 
sys.path.append('../python')
import utility as ut

if __name__ == '__main__':
	# mat = ut.generate_random_matrix(5, 5, 100)
	mat = [
		[10, 11, 12, 13, 14],
		[15, 16, 17, 18, 19],
		[20, 21, 22, 23, 24],
		[25, 26, 27, 28, 29],
		[30, 31, 32, 33, 34]
	]
	
	# TODO :: fails this case 4 x 4 
	mat2 = [
		[1, 2, 3, 4],
		[5, 6, 7, 8],
		[9, 10, 11, 12],
		[13, 14, 15, 16]
	]
	mlr.printMatrix(mat2)
	# print(f'\nrow2 col3==>{mat[2][3]}\n')
	print('\n\n')
	# mlr.rotate_layer(mat, 0, 5)
	mlr.matrixRotation(mat2, 4, 4, 1)


	print('testing other functions !!\n\n')
	arr = [25, 31, 55, 77]
	print(f'before shift==> {arr}')
	mlr.logical_right_shift(arr, (1, 2), 99)
	print(f'after shift==>{arr}')


