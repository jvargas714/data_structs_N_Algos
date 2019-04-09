from treenode import TreeNode
import sys
sys.path.append('..')
import utility as ut

# ----------------------------------------------- Helper Functions ----------------------------------------------------
def logNode(node: TreeNode):
	print(f"\nvisting node: {node.val}")

def traverseTree(node: TreeNode, currVal, cnt, maxCnt):
	if not node:
		print("maxCnt: ", maxCnt)
		return cnt
	logNode(node)
	if currVal != node.val:
		currVal = node.val
		print(f'cnt: {cnt}, maxCnt: {maxCnt}')
		maxCnt = max(cnt, maxCnt)
		cnt = 0
	else:
		print(f"incrementing cnt to : {cnt+1}, maxCnt: {maxCnt}")
		cnt += 1

	maxCnt = max(cnt, maxCnt)
	cnt = traverseTree(node.left, currVal, cnt, maxCnt)
	print(f'in between function calls maxCnt: {maxCnt}')
	maxCnt = max(cnt, maxCnt)
	cnt = traverseTree(node.right, currVal, cnt, maxCnt)
	return max(cnt, maxCnt)

summation = 0
def sumLeft( lnode, rnode):
	global summation
	print(f'sum val: {summation}')
	# check if left is a leaf 
	if lnode and not (lnode.left or lnode.right):
		summation += lnode.val
		print(f'sum: {summation}')
	
	# traverse down the left side 
	if lnode:
		sumLeft(lnode.left, lnode.right)
	
	# traverse down the right side 
	if rnode:
		sumLeft(rnode.left, rnode.right)
	print(f'returning sum: {summation}')

# original solution 
def sumLeftV3(lnode, rnode, vals):
	# check if left is a leaf 
	if lnode and not (lnode.left or lnode.right):
		vals.append(lnode.val)
	
	# traverse down the left side 
	if lnode:
		sumLeftV3(lnode.left, lnode.right, vals)
	
	# traverse down the right side 
	if rnode:
		sumLeftV3(rnode.left, rnode.right, vals)

# ====================================================== Problems ======================================================
# ------------------------------------------------------ problem 404 ---------------------------------------------------
'''
	find sum of all left leaves in a given binary tree
'''

# time: 56ms 11.07%, mem: 14.1 MB
def sumOfLeftLeaves(root: TreeNode) -> int:
	if not root:
		return 0
	sumLeft(root.left, root.right)
	return summation

# time: 24ms mem: 12.4 MB less than 6.98% 
# from discussion 
def sumOfLeftLeavesV2(root):
		if not root: return 0
		# if left side is a leaf then add to result of right side of root
		if root.left and not root.left.left and not root.left.right:
			return root.left.val + sumOfLeftLeavesV2(root.right)

		# sum up both sides of root (only left leafs)
		return sumOfLeftLeaves(root.left) + sumOfLeftLeaves(root.right)

# Runtime: 40 ms, faster than 79.39%
# Memory Usage: 13.9 MB, less than 5.32% 
def sumOfLeftLeavesV3(root: TreeNode) -> int:
	if not root:
		return 0
	vals = []
	sumLeftV3(root.left, root.right, vals)
	return sum(vals)
	
# -----------------------------------------------------problem 687------------------------------------------------------
"""
	find length of longest path where each node in a path has the same value.
"""
# problem 687, 
def longestUnivaluePath(root: TreeNode) -> int:
	maxCnt = 0
	return traverseTree(root, root.val, -1, maxCnt)



# ------------------------------------------------- test functions -----------------------------------------------------
def test_longestUnivaluePath():
	treeOne = r'''
			  1
			 / \
			4   5
		   / \   \
		  4   4   5'''
	print(f'first tree: {treeOne}')
	root = TreeNode(1)
	root.left = TreeNode(4)
	root.right = TreeNode(5)
	root.left.left = TreeNode(4)
	root.left.right = TreeNode(4)
	root.right.right = TreeNode(5)
	print(f'result: ==> {longestUnivaluePath(root)}, expected 2')
	print('---------------------------------------------------------------')
	treeTwo = r'''
			  5
			 / \
			4   5
		   / \   \
		  1   1   5
	'''
	print(f'second tree: {treeTwo}')
	root = TreeNode(5)
	root.left = TreeNode(4)
	root.right = TreeNode(5)
	root.left.left = TreeNode(1)
	root.left.right = TreeNode(1)
	root.right.right = TreeNode(5)
	print(f'result: ==> {longestUnivaluePath(root)}, expected: 2')
	print('---------------------------------------------------------------')

def test_sumOfLeftLeaves():
		r'''
				3
			   / \
			  9  20
				/ \
			   15 7		
   '''
		root = TreeNode(3)
		root.left = TreeNode(9)
		root.right = TreeNode(20)
		root.right.left = TreeNode(15)
		root.right.right = TreeNode(7)
		expected = 24
		res = sumOfLeftLeaves(root)
		print(f"\n\nresult ==> {res} \nexpected ==> {24}\n")
		print(f'answer is {"CORRECT!!" if expected == res else "WRONG!!"}')


if __name__ == "__main__":
	test_sumOfLeftLeaves()


