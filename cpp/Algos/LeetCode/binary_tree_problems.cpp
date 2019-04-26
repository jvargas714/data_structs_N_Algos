#include "binary_tree_problems.h"
#include "utility.h"
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <set>

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%helper functions%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
static TreeNode* _insertData(int l, int r, std::vector<int>& data) {
	if ( l>r )
		return nullptr;
	int midpt = (l+r)/2;
	auto root = new TreeNode(data[midpt]);
	root->left = _insertData(l, midpt-1, data);
	root->right = _insertData(midpt+1, r, data);
	return root;
}

static void _dive(TreeNode* node, TreeNode* root, int& deep, int& deepest) {
	if (!node||node->val==INT32_MIN) {
		std::cout << "deep: " << deep << " deepest: " << deepest << std::endl;
		if (deep > deepest)
			deepest = deep;
		return;
	}
	deep++;
	_dive(node->left, root, deep, deepest);
	if (node == root)
		deep = 1;
	_dive(node->right, root, deep, deepest);
}

/*
	Descr:
        - the set makes the function return if there isn't any elements in it

 */
static double calcEquation_dfs(const std::string& start,
	const std::string& end,
	std::unordered_map<std::string, std::vector<std::string>>& pairs,
	std::unordered_map<std::string, std::vector<double>>& values,
	std::set<std::string> alreadyVisited,
	double value) {
	if (alreadyVisited.find(start)==alreadyVisited.end()) return 0.0;
	if (pairs.find(start)==pairs.end()) return 0.0;
	if (start==end) return value;
	alreadyVisited.insert(start);
	std::vector<std::string> strVect = pairs.find(start)->second;
	std::vector<double> valVect = values.find(start)->second;
	double tmp = 0.0;
	for (int i = 0; i < strVect.size(); i++) {
		tmp = calcEquation_dfs(strVect[i], end, pairs, values, alreadyVisited, value * valVect[i]);
		if (tmp != 0.0) break;
	}
	alreadyVisited.erase(start);
	return tmp;
}

// finds longest univalued leg in a binary tree
void helper_findUnivaluedPath(TreeNode* root, int currentVal, int& cnt, int& longest) {
    if (!root) return;
    LOG << "current node: " << root->val << ", currentVal: "
    << currentVal << ", cnt: " << cnt << ", longest: " << longest << END;
    if (currentVal == root->val) {
        LOG << "incrementing cnt to " << (cnt+1) << END;
        cnt++;
    } else {
        LOG << "current val changing to " << root->val << END;
        currentVal = root->val;
        cnt = 0;
    }
    if (cnt > longest) longest = cnt;
    helper_findUnivaluedPath(root->left, currentVal, cnt, longest);
    helper_findUnivaluedPath(root->right, currentVal, cnt, longest);
}

void inorderTravel(TreeNode* root, std::vector<int>& res) {
    if (!root) return;
    inorderTravel(root->left, res);
    res.push_back(root->val);
    inorderTravel(root->right, res);
}

int inorderTravel(TreeNode* root) {
    if (!root) return INT32_MAX;

}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%END helper functions%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

int maxDepth(TreeNode* root) {
	if (!root) return 0;
	TreeNode* tmp = root;
	int maxDepth = 0;
	int deep = 0;
	_dive(tmp, root, deep, maxDepth);
	return maxDepth;
}

int maxDepthV2(TreeNode* root) {
	if (!root) return 0;
	else {
		// traverse down left side and then right side first
		int lheight = maxDepthV2(root->left);
		int rheight = maxDepthV2(root->right);

		// return larger of the sides depth
		if (lheight>rheight) return (lheight+1);
		else return (rheight+1);
	}
}

int maxDepthV3(TreeNode *root) {
	if(root == nullptr)
		return 0;

	int res = 0;
	std::queue<TreeNode *> q;
	q.push(root);
	while(!q.empty()) {
		++res;
		for(int i = 0, n = (int)q.size(); i < n; ++i) {
			TreeNode *p = q.front();
			q.pop();
			if(p->left != nullptr)
				q.push(p->left);

			if(p->right != nullptr)
				q.push(p->right);
		}
	}
	return res;
}


bool _bstCheck(TreeNode* root, TreeNode* _min = nullptr, TreeNode* _max = nullptr) {
	if (!root) return true;

	if (_min && root->val <= _min->val) return false;
	if (_max && root->val >= _max->val) return false;
	return _bstCheck(root->left, _min, root) &
	       _bstCheck(root->right, root, _max);
}

bool isValidBST(TreeNode* root) {
	if (!root) return true;
	return _bstCheck(root);
}

bool _checkSymmetric(TreeNode* lft, TreeNode* rht) {
	if (!lft && !rht) return true;

	if ((lft&&rht) && (lft->val==rht->val) ) {
		return _checkSymmetric(lft->left, lft->right) &&
		       _checkSymmetric(rht->right, rht->left);
	} else {
		return false;
	}
}


//      1
//    /  \
//   2    2
//  / \  / \
// 3  4 4  3
// [1,2,2,null,3,null,3]
// [2,3,3,4,5,5,4,null,null,8,9,9,8]
bool isSymmetric(TreeNode* root) {
	if (!root) return true;
	return _checkSymmetric(root->left, root->right);
}

// provided level will be index of the vector
void _collectGivenLevel(TreeNode* root, int level, std::vector<int>& data) {
	if (!root)
		return;
	if (level == 0) {
		data.push_back(root->val);
	}
	else if (level > 0) {
		_collectGivenLevel(root->left, level-1, data);
		_collectGivenLevel(root->right, level-1, data);
	}
}

// display tree reading it from left to right
VectOfVect levelOrder(TreeNode* root) {
	if (!root) return {{}};
	TreeNode* tmp = root;
	int height = maxDepthV2(tmp);
	tmp = root;
	VectOfVect result(height);
	for (int lvl = 0; lvl < height; lvl++) {
		_collectGivenLevel(root, lvl, result[lvl]);
	}
	return result;
}

void _DFS(VectOfVect &res,TreeNode* root,int level){
	if(root==nullptr)
		return;
	if(res.size()==level)
		res.push_back(std::vector<int>());
	res[level].push_back(root->val);
	_DFS(res,root->left,level+1);
	_DFS(res,root->right,level+1);
}

// faster more efficient version (6ms)
VectOfVect levelOrderV2(TreeNode* root) {
	if(!root)
		return VectOfVect();
	VectOfVect res;
	_DFS(res,root,0);
	return res;
}

// iterative using queue solution, left to right
VectOfVect levelOrderV3(TreeNode* root) {
	std::queue<TreeNode*> nodeQue;
	VectOfVect result;
	if (!root)
		return result;
	nodeQue.push(root);
	while (!nodeQue.empty()) {
		auto lvlSize = (int)nodeQue.size();
		std::vector<int> curLvl;
		for (int i = 0; i < lvlSize; i++) {
			TreeNode* nd = nodeQue.front();
			nodeQue.pop();
			if (nd->left) nodeQue.push(nd->left);
			if (nd->right) nodeQue.push(nd->right);
			curLvl.push_back(nd->val);
		}
		result.push_back(curLvl);
	}
	return result;
}

TreeNode* sortedArrayToBST(std::vector<int>& data) {
	if (data.empty()) return nullptr;
	return _insertData(0, (int)(data.size()-1), data);
}

VectOfVect zigzagLevelOrder(TreeNode *root) {
	VectOfVect result;
	std::deque<TreeNode*> nodeQue;
	if (!root) return result;
	bool leftToRight = true;  // bool to dictate direction of level traversal
	nodeQue.push_back(root);
	while(!nodeQue.empty()) {
		int lvlSize = (int)nodeQue.size();
		std::vector<int> currLvl;
		for (int i = 0; i < lvlSize; i++) {
			TreeNode* nd;
			if (leftToRight) {
				nd = nodeQue.front();
				nodeQue.pop_front();
			}
			else {
				nd = nodeQue.back();
				nodeQue.pop_back();
			}
			currLvl.push_back(nd->val);
			if (leftToRight) {
				if (nd->left) nodeQue.push_back(nd->left);
				if (nd->right) nodeQue.push_back(nd->right);
			} else {    // we go right to left
				if (nd->right) nodeQue.push_front(nd->right);
				if (nd->left) nodeQue.push_front(nd->left);
			}
		}
		leftToRight = !leftToRight;
		result.push_back(currLvl);
	}
	return result;
}

/*
 *
    3
   / \
  0   4
   \
    2
   /
  1

  L = 1
  R = 3

Output:
      3
     /
   2
  /
 1

 */
TreeNode *trimBST(TreeNode *root, int L, int R) {
	if (!root) return root;

	// check if out of range
	if (root->val < L) return trimBST(root->right, L, R);
	if (root->val > R) return trimBST(root->left, L, R);

	// assign nodes
	root->left = trimBST(root->left, L, R);
	root->right = trimBST(root->right, L, R);
	return root;
}

std::vector<int> inorderTraversal(TreeNode* root) {
	if (!root) return {};
	std::stack<TreeNode*> stk;
	std::vector<int> result;
	TreeNode* node = root;
	while(node||!stk.empty()) {
		if (node) {
			stk.push(node);
			node = node->left;
		} else {
			node = stk.top();
			result.push_back(node->val);
			node = node->right;
			stk.pop();
		}
	}
	return result;
}

int longestUnivaluePath(TreeNode *root) {
    if (!root) return -1;
    int longestPath = 0;
    int tmp = 0;
    helper_findUnivaluedPath(root, root->val, tmp, longestPath);
    return longestPath;
}

/*
Example:
Given a / b = 2.0, b / c = 3.0.
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
return [6.0, 0.5, -1.0, 1.0, -1.0 ]

equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ].
 */
std::vector<double>
calcEquation(std::vector<std::pair<std::string, std::string>> equations,
				std::vector<double> &values,
			 	std::vector<std::pair<std::string, std::string>> queries) {
	std::unordered_map<std::string, std::vector<std::string>> pairs;
	std::unordered_map<std::string, std::vector<double>> valuesPairs;

	for (int i = 0; i < equations.size(); i++) {
		std::pair<std::string, std::string> equation = equations[i];
		if (pairs.find(equation.first) == pairs.end()) {
			pairs[equation.first] = std::vector<std::string>();
			valuesPairs[equation.first] = std::vector<double>();
		}
		if (pairs.find(equation.second) == pairs.end()) {
			pairs[equation.second] = std::vector<std::string>();
			valuesPairs[equation.second] = std::vector<double>();
		}
		pairs.find(equation.first)->second.push_back(equation.second);
		pairs.find(equation.second)->second.push_back(equation.first);
		valuesPairs.find(equation.first)->second.push_back(values[i]);
		valuesPairs.find(equation.second)->second.push_back(1/values[i]);
	}
	std::pair<std::string, std::string> query;
	std::vector<double> result(queries.size());
	for (int i = 0; i < queries.size(); i++) {
		query = queries[i];
		result[i] = calcEquation_dfs(query.first, query.second, pairs, valuesPairs, std::set<std::string>(), 1.0);
		if (result[i] == 0.0) result[i] = -1.0;
	}
	return result;
}

// Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
// O(n) time and space
int kthSmallest(TreeNode* root, int k) {
    if (!root) return -1;
    std::vector<int> binTree;
    inorderTravel(root, binTree);
    return binTree[k-1];
}

// attempt to optimize space usage
int kthSmallestV2(TreeNode* root, int k) {
    return inorderTravel(root);
/*
	Input:

		   4
		/   \
	   2     7
	  / \   / \
	1   3  6   9

	Output:

		4
	  /   \
	 7     2
    / \   / \
   9   6 3   1
	 time: O(n)
	 space: O(h)  where h is depth of tree, each function call stores a node
*/
TreeNode* invertTree(TreeNode* root) {
	if (!root) return nullptr;
	TreeNode* left = invertTree(root->left);
	TreeNode* right = invertTree(root->right);
	root->left = right;
	root->right = left;
	return root;
}













/*
	Iterative solution using queue
	Approach:
		swap the left and right child of all nodes in the tree. We use a queue to store nodes
		whose left and right child have not been swapped yet. Null nodes are not added to
		the queue. Eventually the queue will be empty and all children have been swapped
	time complexity: O(n)
	space complexity: O(n)
*/
TreeNode* invertTreeV2(TreeNode* root) {
	if (!root) return nullptr;
	std::queue<TreeNode*> ndQ;
	ndQ.push(root);
	while (!ndQ.empty()) {
		TreeNode* curr = ndQ.front();
		TreeNode* tmp = curr->left;
		curr->left = curr->right;
		curr->right = tmp;
		if (curr->left) ndQ.push(curr->left);
		if (curr->right) ndQ.push(curr->right);
	}
	return root;
}
