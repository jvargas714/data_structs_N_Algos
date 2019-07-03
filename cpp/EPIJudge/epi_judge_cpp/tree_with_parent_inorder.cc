#include <vector>
#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::vector;

/*
 * Descr:
 *      implement inorder traversal with using constant space. You can assume every
 *      node has a parent.
 *      Inorder: L Rt R
 *             *
 *          /  |
 *        *    *
 *      / |   /|
 *     *  *    *
 * Approach:
 *      1. start by pointing at the root
 *      2. while loop logic
 *          2a. if the current node's parent is the same as prev then we know we are digging deeper in to the tree
 *              2aa. we try to go to the next left child to continue the traversal
 *              2ab. if there isnt a left child to go to then we record the current node we are on
 *              2ac. after saving that node we try to go to the right node, else go to the parent
 *          2b. else if the prev node was the curr nodes left child then we know that we moved up last iteration
 *              2ba. add the current node to the result vector
 *              2bb. try to go right if it exists otherwise move up to the parent
 *          2c. both children have been visited, we just need to move up a level
 *          3. prev becomes the current and curr becomes next for the next iteration
 *          4. return result
 * Time:
 *  Average running time:    5 us
 *	Median running time:     2 us
 *
 * Complexity:
 *  runtime: O(n)
 *  space: O(1)
 *
 */
vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
	vector<int> result;
	BinaryTreeNode<int> *prev = nullptr, *curr = tree.get();
	while (curr != nullptr) {
		BinaryTreeNode<int>* next;
		if (curr->parent == prev) { // came down a level from prev
			if (curr->left != nullptr) {  // go left
				next = curr->left.get();
			} else {
				result.emplace_back(curr->data);
				// we now go right if right exists otherwise go up a level
				next = curr->right != nullptr ? curr->right.get() : curr->parent;
			}
		} else if (curr->left.get() == prev) {  // this condition is when arrived here from the left child, moved up a level
			result.emplace_back(curr->data);
			// check for right, if not move up a level
			next = curr->right != nullptr ? curr->right.get() : curr->parent;
		} else {  // done with both children so move up
			next = curr->parent;
		}
		prev = curr;
		curr = next;
	}
	return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_with_parent_inorder.cc",
                         "tree_with_parent_inorder.tsv", &InorderTraversal,
                         DefaultComparator{}, param_names);
}
