#include "binary_tree_problems.h"
#include "utility.h"
using namespace std;

void test_longestUnivaluePath(const std::vector<int>& nodes, int expected) {
    FUNCT_HEADER;
    LOG << "node source vector: ";
    display(nodes);
    TreeNode* root = allocateBinTreeFromVect(nodes);
    int result = longestUnivaluePath(root);
    LOG << "result: " << result << " expected: " << expected << END;
    FUNCT_END;
}

int main() {
    test_longestUnivaluePath({1, 4, 5, 4, 4, 3, 5}, 2);
	return 0;
}

