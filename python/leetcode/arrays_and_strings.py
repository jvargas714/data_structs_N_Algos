import sys, time
sys.path.extend(['python', 'leetcode'])
import sys, os
from typing import List

print("\nCWD: ", os.getcwd())
import utility as ut

# =============================================== HELPER FUNCTIONS =====================================================

def generatePascalTriangle(n):
	''' generates pascals triangle up to the nth row'''
	res = [[1], [1, 1]]
	if n == 0:
		return [[1]]
	elif n == 1:
		return res
	
	i = 1
	row = 1

	while row != n:
		tmp = [1]
		for i_a in range( len( res[i] ) - 1 ):
			i_b = i_a + 1
			tmp.append( res[i][i_a] + res[i][i_b] )
		i += 1
		row += 1
		tmp.append(1)
		res.append(tmp)
	return res

# use only one row at a time to save memory usage 
def generatePascalTriangleV2(n):
	''' generates pascals triangle up to the nth row'''
	if n == 0:
		return [1]
	elif n == 1:
		return [1, 1]
	row = 1
	prevRow = [1, 1]
	while row != n:
		tmp = [1]
		for i_a in range( len( prevRow ) - 1 ):
			i_b = i_a + 1
			tmp.append( prevRow[i_a] + prevRow[i_b] )
		row += 1
		tmp.append(1)
		prevRow = tmp
	return prevRow

# O(1) operation space and time 
def cellInDirection(matrix: List[List[int]], currentPt: tuple, dir: str) -> int:
	''' traverse matrix by one cell in the direction specified from provided point (row, col)
		values increase going right and down 
	'''

	col_limit = len(matrix[0]) # [ --> ]
	row_limit = len(matrix) 	# [ down ]
	if dir == 'up':
		new_row = currentPt[0] + 1
		if new_row >= row_limit:
			return -1
		else:
			return matrix[new_row][currentPt[1]]  # matrix[row][col]
	elif dir == 'down':
		new_row = currentPt[0] - 1
		if new_row < 0:
			return -1
		else:
			return matrix[new_row][currentPt[1]]
	elif dir == 'left':
		new_col = currentPt[1] - 1
		if new_col < 0:
			return -1
		else:
			return matrix[currentPt[0]][new_col]
	elif dir == 'right':
		new_col = currentPt[1] + 1
		if new_col >= col_limit:
			return -1
		else:
			return matrix[currentPt[0]][new_col]
	else:
		return -1

def calcDist(p1: tuple, p2: tuple):
	''' calculate distance between two points '''
	return abs(p1[0]-p2[0]) + abs(p1[1]-p2[1])
# =============================================== PROBLEMS =============================================================
# ----------------------------------------------- Problem #119 -------------------------------------------------------
'''
	Given a non-negative index k where k ≤ 33, return the kth index row of the Pascal's triangle.
	Note that the row index starts from 0.
'''
# Runtime: 20 ms, faster than 75.98%
# Memory Usage: 11.6 MB, less than 5.95%
def getRow(rowIndex):
	return generatePascalTriangle(rowIndex)[-1]

# Runtime: 20 ms, faster than 75.98%
# Memory Usage: 11.7 MB, less than 5.95%
def getRowV2(rowIndex):
	return generatePascalTriangleV2(rowIndex)

'''
Solution From Discussion 
say we get row = [1, 2, 1] from last iteration.
[0]+row gives us [0, 1, 2, 1] (appending 0 to the head); row+[0] gives us [1, 2, 1, 0].
Then we need to do the element-wise addition of the 2 lists.
zip() would give us element-wise zipped tuples: [(0, 1), (1, 2), (2, 1), (1, 0)], which is a iterator actually.
then we use the list comprehension to do the actual addition.
'''
# Runtime: 20 ms, faster than 76.52%
# Memory Usage: 11.8 MB, less than 5.95%
def getRowV3(rowIndex):
	row = [1]
	for _ in range(rowIndex):
		row = [x + y for x, y in zip([0]+row, row+[0])]
	return row

# fastest solution (not mine) 
# didnt make much of a difference in terms of execution speed 
def getRowV4(rowIndex):
	ans=[1 for i in range(rowIndex+1)]
	for i in range(1,(rowIndex)//2+1):
		ans[i]=ans[i-1]*(rowIndex+1-i)//i
		ans[rowIndex-i]=ans[i]
	return ans
	
# ----------------------------------------------- Problem #542 -------------------------------------------------------
'''
	01 Matrix
	Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.
	The distance between two adjacent cells is 1

	Note:
		The number of elements of the given matrix will not exceed 10,000.
		There are at least one 0 in the given matrix.
		The cells are adjacent in only four directions: up, down, left and right.

	Idea 1:
		1. first find zero pts 
		2. for each 1 pt find distance to each zero pt, take shortest distance
'''
# logic is good, just too slow. Time limit exceeded 
def updateMatrix(matrix: List[List[int]]) -> List[List[int]]:
	pts_0 = []
	pts_1 = []
	# init matrix with zeros O(n*m) where n = num of rows and m is the num of cols
	res = [ [0] * len(matrix[0]) for _ in range(len(matrix)) ]

	# collect zero pts and one pts O(n*m)
	for row_ind in range(len(matrix)):
		for col_ind in range(len(matrix[0])):
			if matrix[row_ind][col_ind] == 0:
				pts_0.append((row_ind, col_ind))
			else:
				pts_1.append((row_ind, col_ind))
	
	# determine distances for none zero pts 
	for pt in pts_1:
		min_dist = 150000  # impossible to reach this as there are only 10000 elements at most in the matrix 
		for zpt in pts_0:
			dst = calcDist(pt, zpt)
			if dst == 1:
				min_dist = 1
				break
			min_dist = min(dst, min_dist)
		res[pt[0]][pt[1]] = min_dist
	return res

'''
	Optimization attempt
	Approach:
		1. try to modify matrix in place instead
'''
def updateMatrixV2(matrix: List[List[int]]) -> List[List[int]]:
	pass

# =============================================== TEST FUNCTIONS =======================================================
	
def test_getRow(versionNum=1):
	expected = [1,25,300,2300,12650,53130,177100,480700,1081575,2042975,3268760,
					4457400,5200300,5200300,4457400,3268760,2042975,1081575,480700,177100,
					53130,12650,2300,300,25,1]
	row = 100
	if versionNum == 1:
		res = getRow(row)
		print(f'your result is {"CORRECT" if expected == res else "WRONG"}')
	elif versionNum == 2:
		res = getRowV2(row)
		print(f'your result is {"CORRECT" if expected == res else "WRONG"}')
	elif versionNum == 3:
		res = getRowV3(row)
		print(f'your result is {"CORRECT" if expected == res else "WRONG"}')
	elif versionNum == 4:
		res = getRowV4(row)
		print(f'your result is {"CORRECT" if expected == res else "WRONG"}')

def test_updateMatrix(versionNum=1):
	inMatrix = [[0,0,0],
				[0,1,0],
 				[1,1,1]]
	expected = [[0,0,0],
 				[0,1,0],
 				[1,2,1]]
	print(f'input matrix: {ut.matrixToString(inMatrix)}')
	if versionNum == 1:
		res = updateMatrix(inMatrix)
		print(f'\n\nresult: {res}, \nexpected: {expected},\nthis result is {"CORRECT" if res == expected else "WRONG"}')

# ====================================================MAIN =============================================================
if __name__ == '__main__':
	print ( ut.time_execution(test_updateMatrix, 1) )