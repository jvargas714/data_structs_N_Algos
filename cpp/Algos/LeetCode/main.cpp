#include <iostream>
#include <chrono>
#include <types.h>
#include "utility.h"
#include "leet_algos.h"

using namespace std::chrono;
typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;

void testBinTree() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    TreeNode *binTree = allocateBinTreeFromVect(data);
    std::vector<int> inOrderTrav = inOrderTraversal(binTree);
    std::vector<int> postOrderTrav = postOrderTraversal(binTree);
    std::vector<int> preOrderTrav = preOrderTraversal(binTree);
    std::cout << "InOrder Traversal" << std::endl;
    for (const auto &el: inOrderTrav) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    std::cout << "preOrder Traversal" << std::endl;
    for (const auto &el : preOrderTrav) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    std::cout << "postOrder Traversal" << std::endl;
    for (const auto &el : postOrderTrav) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{   
    using namespace std; 
    t_point t1_bub, t2_bub;
	vector<int> data = {-10, -3, 0, 5, 9};
    
    t1_bub = hrc::now();
    TreeNode* root = sortedArrayToBST(data);
    t2_bub = hrc::now();

    cout << "result tree inorder traversal of test bin tree: " << endl; 
    for(const auto& el: inOrderTraversal(root)) {
        cout << el << " ";
    }cout << endl; 

	std::cout << "\n\n----------------------------------------------------------------------\n\n" << std::endl;
    auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
	std::cout << "time of execution -->\n" << milli_sec << "msec\n" << micro_sec << "usec\n" << std::endl;

#ifdef WIN_32
	std::cout << "\n\npress any key to exit" << std::endl;
	char hold; 
	std::cin >> hold;
#endif
    return 0;
}
