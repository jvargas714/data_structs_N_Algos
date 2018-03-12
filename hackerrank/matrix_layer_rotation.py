#!python3 
import sys

def logical_left_shift(arr, ind_range, shiftin_val):
	"""
	    A left shift of an array by n places, zeros are shifted in 
	    
	    Args:
	        arr (list): list to be shifted
	        ind_range(tuple): low to high index range inclusive of indicies to be involved in the shift 
	        n (int): number of shifts 
    """
	print(f'left logical: {arr}, ind range: {list(range(ind_range[0], ind_range[1]))}, shiftinval:{shiftin_val}')
	for i in range(ind_range[0], ind_range[1]):
		arr[i] = arr[i+1]
	arr[ind_range[1]] = shiftin_val


def logical_right_shift(arr, ind_range, shiftin_val):
	"""
	    A right shift of an array by n places, zeros are shifted in 
	    
	    Args:
	        arr (list): list to be shifted
	        ind_range(tuple): low to high index range inclusive of indicies to be involved in the shift 
	        n (int): number of shifts 
    """
	print(f'right logical: {arr}, ind range({ind_range[0]}, {ind_range[1]}): {list(range(ind_range[0], ind_range[0]-1))}, shiftinval:{shiftin_val}')

	for i in range(ind_range[1], ind_range[0]-1, -1):
		arr[i] = arr[i-1]
	arr[ind_range[0]] = shiftin_val


def printMatrix(matrix):
    row_str = '' 
    for row in matrix:
    	for el in row:
    		row_str += str(el) + ' '
    	print(row_str)
    	row_str = '' 


def rotate_layer(mat, layer, num_rows):
	'''
		rotates the outer layer of the given matrix one time, 
		layer reps the top left val of the box 
		    1
		  -----
		2|    | 4
		 -----
		   3
		each face is represented as a number , the top left hand corner is represented by (layer, layer)	
	'''	
	max_row_ind = num_rows - layer - 1 
	max_col_ind = len(mat[0]) - layer - 1
	
	print(f'processing layer:{layer}')

	# save vals before shift of face 1 
	top_left_val = mat[layer][layer]
	to_be_top_right_val = mat[layer+1][max_col_ind] 
	bottom_left_val = mat[max_row_ind][layer]
	v = bottom_left_val
	bottom_right_val = mat[max_row_ind][max_col_ind]

	print('starting with: ')
	printMatrix(mat)
	print('\n\n')

	# rotate face 1 (logical left shift)
	logical_left_shift(mat[layer], (layer, len(mat[layer])-1), to_be_top_right_val)

	print('after logical left')
	printMatrix(mat)
	print('\n\n')

	# face 2 is a downward vertical shift 
	for i in range(max_row_ind, layer+1, -1):
		mat[i][layer] = mat[i-1][layer]
	mat[layer+1][layer] = top_left_val

	print('after face 2')
	printMatrix(mat)
	print('\n\n')

	# face 3 will have a logical right shift
	logical_right_shift(mat[max_row_ind], (layer+1, len(mat[max_row_ind])-1), bottom_left_val)

	print('after face 3')
	printMatrix(mat)
	print('\n\n')
	
	# face 4 shift is a upward vertical shift
	if (max_row_ind-2) >= 0:
		print('processing face 4')
		for i in range(layer, max_row_ind-1):
			print(f'mat[{i}][{max_col_ind}] = mat[{i+1}][{max_col_ind}] ==> {mat[i][max_col_ind]} = {mat[i+1][max_col_ind]}\n\n')
			mat[i][max_col_ind] = mat[i+1][max_col_ind]
	mat[max_row_ind-1][max_col_ind] = bottom_right_val
	
	# DEBUG 
	print('after face 4')
	printMatrix(mat)
	print('\n\n')


def matrixRotation(matrix, num_rows, cols, rot):
    rows = len(matrix)
    num_layers = int( (rows*cols)/(rows+cols) )

    for xx in range(rot):   ## this loop keeps track of how many times the entire matrix would be rotated 
	    for layer_num in range(num_layers):  ## this loop rotates all layers once 
	    	rotate_layer(matrix, layer_num, num_rows)
    printMatrix(matrix)

if __name__ == "__main__":
    m, n, r = input().strip().split(' ')
    m, n, r = [int(m), int(n), int(r)]
    matrix = []
    for matrix_i in range(m):
       matrix_t = [int(matrix_temp) for matrix_temp in input().strip().split(' ')]
       matrix.append(matrix_t) 
    matrixRotation(matrix, m, n, r)
