from treenode import TreeNode
import sys
sys.path.append('..')
import utility as ut

r"""
Given a binary tree, find the length of the longest path where each node in the path has the same value.
This path may or may not pass through the root.

Note: The length of path between two nodes is represented by the number of edges between them.

              5
             / \
            4   5
           / \   \
          1   1   5
Output: 2

              1
             / \
            4   5
           / \   \
          4   4   5
Output: 2
"""

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

def longestUnivaluePath(root: TreeNode) -> int:
	maxCnt = 0
	return traverseTree(root, root.val, -1, maxCnt)

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

if __name__ == "__main__":
	test_longestUnivaluePath()


