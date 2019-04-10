import sys, time
sys.path.append('..')
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
	
	i = 1
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


# =============================================== PROBLEMS =============================================================
# ----------------------------------------------- Problem #   q-------------------------------------------------------
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

# =============================================== TEST FUNCTIONS =======================================================
	
def test_getRow(versionNum=1):
	expected = [1,25,300,2300,12650,53130,177100,480700,1081575,2042975,3268760,
					4457400,5200300,5200300,4457400,3268760,2042975,1081575,480700,177100,
					53130,12650,2300,300,25,1]
	row = 25
	if versionNum == 1:
		res = getRow(row)
		print(f'your result is {"CORRECT" if expected == res else "WRONG"}')
	elif versionNum == 2:
		res = getRowV2(row)
		print(f'your result is {"CORRECT" if expected == res else "WRONG"}')


# ====================================================MAIN =============================================================
if __name__ == '__main__':
	print('version 1: ', end=' ')
	print(
	ut.time_execution( test_getRow, 2)
	)

	print('version 2: ', end=' ')
	print(
		ut.time_execution( test_getRow, 2)
	)

