import sys
sys.path.append('..')
import utility as ut

# =============================================== HELPER FUNCTIONS =====================================================
def generatePascalTriangle(n):
	''' generates pascals triangle up to the nth row'''
	res = [[1], [1, 1]]
	if n == 0:
		return [[1]]
	elif n == 1:
		return [[1], [1, 1]]
	i = 2
	tmp = [1]
	for i_a in range(len(res[-1])-1):
		i_b = i_a + 1
		tmp.append(res[i_a] + res[i_b])
	tmp.append(1)
	res.append(tmp)

# =============================================== PROBLEMS =============================================================
# ----------------------------------------------- Problem #  119-------------------------------------------------------
'''
	Given a non-negative index k where k ≤ 33, return the kth index row of the Pascal's triangle.
	Note that the row index starts from 0.
'''
def getRow(rowIndex):
        """
        :type rowIndex: int
        :rtype: List[int]
        """
        return generatePascalTriangle(rowIndex)[-1]
# =============================================== TEST FUNCTIONS =======================================================
	




if __name__ == '__main__':
	nums = [1,3,2,2,5,2,3,7]
	expected = 5
	print(f"result: {findLHS(nums)}, expected: {expected}")

