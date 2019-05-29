#include <iostream>
#include <sstream>
#include <random>
#include <queue>
#include <map>
#include <fstream>
#include "time.h"
#include "types.h"
#include "utility.h"


// displays an array
void display( const int* ar, size_t num_els ) {
    for( uint i = 0; i < num_els; i++ ) {
        std::cout << ar[i] << " ";
    }
    std::cout << std::endl;
}

/*
    Descr:
    As we traverse through, we know that when the if case is true (data[j] <= pivot) that all
    The idea behind this partitioning algorithm is to place all elements smallers than the pivot
    to the left and all the greater elements to the right. Returns index of division point.
    the elements that came before that are larger than the pivot. So we can increment i and swap
    with the element that is larger than the pivot. We continue from there doing the same till we
    run through all the elements of the std::vector.
    Data is split like this: 0....divPt ; divPt+1....n
    Worst Case: O(n)
*/
int partition( std::vector<int>& data, int low, int high ) {
    int pivot   = data[high];   // typically pivot point is at end of std::vector
    int i       = (low - 1);    // index where smaller element exists
    for( int j = low; j <= high-1; j++ ) {
        if( data[j] <= pivot ) {
            i++;
            swap_el( &data[i], &data[j] );
        }
    }
    swap( data[i+1], data[high] );
    return ( i + 1 );
}

// display std::vector in its respective partitioned sections according to the partition point
void show_partition( std::vector<int>& data, int part_pt )
{
    std::cout << "div_pt: " << part_pt << std::endl;
    std::cout << "\nThe low side: " << std::endl;
    for( int i = 0; i <= part_pt; i++ )
    {
        std::cout << data[i] << " ";
    }
    for( int64_t i = part_pt+1; i < data.size(); i++ )
    {
        std::cout << data[i] << " ";
    }
}

// simply swap function
void swap_el( int* a, int* b )
{
    int tmp = *a;
    *a      = *b;
    *b      = tmp;
}

// split a string by specified delim, if empty token between delims then do not collect it
void split( const std::string& s, char delim, std::vector<std::string>& elems )
{
    std::stringstream ss;
    ss.str(s);  // set contents of ss with s
    std::string item;
    while( getline(ss, item, delim) )
    {
        if( !item.empty() )
            elems.push_back(item);
    }
}

std::vector<int> fill_vector( uint32_t num_els, bool isRand )
{
    std::vector<int> vect;
    std::random_device rd;
    int val;
    srand( static_cast<uint32_t>( time( nullptr ) ) );
    for( uint i = 0; i < num_els; i++ )
    {
        if (isRand)
            val = rd() % num_els;
        else
            val = i;
        vect.push_back(val);
    }
    return vect;
}

// fills array with num_els random integers
// allocated on the heap
int* fill_array( uint32_t num_els ) {
    std::random_device rd;
    auto* ar = new int[ num_els ];
    srand( static_cast<unsigned int>( time(nullptr) ) );
    for(uint i = 0; i < num_els; i++ ) {
        ar[i] = static_cast<uint32_t>((rd() % num_els));
    }
    return ar;
}

void swap(int & a, int &b) {
    int tmp = b;
    b = a;
    a = tmp;
}

int accum(std::vector<int>::iterator a, std::vector<int>::iterator b) {
    int sum = 0;
    for (auto it = a; it!=b; it++)
        sum += *it;
    return sum;
}

ListNode*fillListNode(std::vector<int>&& vect) {
    size_t sz = vect.size();
    if(!sz)
        return nullptr;
    auto* head = new ListNode(vect[0]);
    ListNode* tmp = head;
    for(auto it = vect.begin()+1; it != vect.end(); ++it) {
        tmp->next = new ListNode(*it);
        tmp = tmp->next;
    }
    return head;
}

size_t deallocateLList(ListNode* head) {
    size_t cnt = 0;
    ListNode* tmp = head;
    while(tmp) {
        delete tmp;
        tmp = tmp->next;
        cnt +=1;
    }
    return cnt;
}

void _carry(std::vector<int>& digits, int digit_pos) {
	// terminating condition
	if (digits[digit_pos] <= 9) {
		return;
	}
	digits[digit_pos] = 0;
	digit_pos--;
	if (digit_pos < 0)
		digits.insert(digits.begin(), 1);
	else
		digits[digit_pos]++;
	_carry(digits, digit_pos);
}

/*
  take integer input and return string representation of that integer ie 123456 --> 123,456
*/
std::string format_number(const int& num) {
    std::string result("");
    std::string sign = "";
    const char SEP = ',';
    bool neg = (num<0);
    unsigned int charCnt=0;
    int rem = num;

    if(neg) {
        sign = "-";
        rem*=-1;
    }
    if (num == 0) {
        return std::string("0");
    }
    else if (rem < 10) {
        result = std::string(1, static_cast<char>(rem+ASCII_ZERO));
        std::cout << "result: " << result << std::endl;
        return (sign + result);
    }
    while(rem > 0) {
        result.insert(0, 1, static_cast<char>((ASCII_ZERO+(rem%10))));   // string::insert(pos, size, char)
        charCnt++;
        if( !(charCnt%3) ) {
            result.insert(0, 1, SEP);
        }
        rem /= 10;
    }
    // remove comma if at front of number
    if(result[0] == ',')
        result.erase(0, 1);   // std::string::erase(pos, npos); position and number of positions to erase
    return (sign + result);
}

std::string elim_whitespace( std::string& str )
{
    // find char index of first none white space
    uint32_t ind = 0;
    for( auto& ch : str )
    {
        if( ch == 32 ) // 32 ASCII for Space
            ind++;
        else
            break;
    }
    return str.substr( ind, str.size() );
}

std::vector<std::vector<int>> generateNxNMatrix(size_t n) {
    int val;
    std::random_device randomDevice;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            val = static_cast<int>(randomDevice() % n);
            matrix[i][j] = val;
        }
    }
    return matrix;
}

// shifts in a zero at the beginning of the vector
void logicalShiftR(std::vector<int>& nums) {
    for(size_t i = nums.size()-1; i > 0; i--)
        nums[i] = nums[i-1];
    nums[0] = 0;
}

void logicalShiftL(std::vector<int>& nums) {
    for(size_t i = 0; i < nums.size(); i++) {
        nums[i] = nums[i+1];
    }
    nums[nums.size()-1] = 0;
}

void displayListNodes(ListNode* root) {
    if (!root)  return;
    const ListNode* tmp = root;
    while (tmp) {
         std::cout << tmp->val << " ";
        tmp = tmp->next;
    }
    std::cout << std::endl;
}

/*
 * example:
 *              (1)
 *            /    \
 *          /       \
 *        (2)      (3)
 *       /   \    /  \
 *     (4)  (5) (6)  (7)
 *
 * from vector [1,2,3,4,5,6,7]
 */
void _fill(const std::vector<int>& data, TreeNode** node, int i) {
    if ( (2*i+1) >= data.size() ) {
        node = nullptr;
        return;
    }
    (*node)->left = new TreeNode(data[i]);
    if ( (i) >= data.size() ) {
        (*node)->right = nullptr;
        return;
    }
    (*node)->right = new TreeNode(data[i+1]);
    _fill(data, &(*node)->left, (2*i+1));
    _fill(data, &(*node)->right, (2*i+2));
}

/*
    fills bin tree from left to right from a std::vector<int>, to fill in a null node
    pass INT32_MIN for that val
    [1, 2, 3, 4, 5, 6, 7] -->
       1
    /   \
   2    3
  /\   /\
 4 5  6 7

 todo :: write subroutine to this function to search for INT_MIN and replace that node with a null
*/
TreeNode* allocateBinTreeFromVect(const std::vector<int>& data) {
    if ( data.empty() ) return nullptr;
    auto root = new TreeNode(data[0]);
    TreeNode* tmp = root;
    std::queue<TreeNode*> cache;
    cache.push(tmp);
    size_t cnt = 1;
    while (cnt < data.size()) {
        cache.front()->left = new TreeNode(data[cnt++]);
        if (cnt >= data.size())
            break;
        cache.front()->right = new TreeNode(data[cnt++]);
        cache.push(cache.front()->left);
        cache.push(cache.front()->right);
        cache.pop();
    }
    return root;
}

void _inorder(const TreeNode* node, std::vector<int>& data) {
    if (!node||(node->val==INT32_MIN)) return;
    _inorder(node->left, data);
    data.push_back(node->val);
    _inorder(node->right, data);
}

std::vector<int> inOrderTraversal(const TreeNode* root) {
    if (!root) return {INT32_MIN};
    std::vector<int> result;
    const TreeNode* tmp = root;
    _inorder(tmp, result);
    return result;
}

void _preorder(const TreeNode* node, std::vector<int>& result) {
    if (!node||(node->val==INT32_MIN)) return;
    result.push_back(node->val);
    _preorder(node->left, result);
    _preorder(node->right, result);
}

std::vector<int> preOrderTraversal(const TreeNode* root) {
    if (!root) return {INT32_MIN};
    std::vector<int>result;
    const TreeNode* tmp = root;
    _preorder(tmp, result);
    return result;
}

void _postorder(const TreeNode* node, std::vector<int>& result) {
    if (!node||(node->val==INT32_MIN)) return;
    _postorder(node->left, result);
    _postorder(node->right, result);
    result.push_back(node->val);
}

std::vector<int> postOrderTraversal(const TreeNode* root) {
    if (!root) return {INT32_MIN};
    const TreeNode* tmp = root;
    std::vector<int> result;
    _postorder(tmp, result);
    return result;
}

static bool saveToFile() {

}
/*
   -- generate prime numbers using Sieve of Eratosthenes Algorithm --
	1. Create a list of consecutive integers from 2 through n: (2, 3, 4, ..., n).
		Initially, let p equal 2, the smallest prime number.
	2. Enumerate the multiples of p by counting to n from 2p in increments of p, and mark them in the list
	    (these will be 2p, 3p, 4p, ...; the p itself should not be marked).
	3. Find the first number greater than p in the list that is not marked. If there was no such number, stop. Otherwise,
		let p now equal this new number (which is the next prime), and repeat from step 3.
		When the algorithm terminates, the numbers remaining not marked in the list are all the primes below n.
 */
std::vector<uint64_t> genPrimes(const uint64_t n) {
    std::vector<uint64_t> primes = {2};
    std::map<uint64_t, bool> primeMap;
    uint64_t val, i;
    uint64_t p = 2;

    // init map
    for (i = 2; i < n; i++)
        primeMap[i] = true;

    while (true) {
        val = p;
        while (val < n) {
            primeMap[val] = false;
            val += p;
        }
        for (i = p+1; i < n; i++) {
            if (primeMap[i]) {
                p = i;
                primes.push_back(p);
                break;
            }
        }
        if (i==n) break;
    }
    return primes;
}

// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
std::vector<uint64_t> genPrimesV2(const uint64_t n) {
    std::vector<bool> notPrime(n, false);
    std::vector<uint64_t> primes;
    for (uint32_t i = 2; i < n; i++) {
        if (!notPrime[i]) {
            primes.push_back(i);  // 2

            // from i^2 to either i > sqrt(n) or j > n
            // finds non primes by finding there multiple i.e: j+=i
            if (i * i < n) {
                for (uint32_t j = 2; j * i < n; ++j)
                    notPrime[i * j] = true;
            }
        }
    }
    return primes;
}

bool isPrime(int n) {
    int rt = sqrt((float)n);
    for(int i=2;i<=rt;i++){
        if(n%i==0)
            return false;
    }
    return true;
}

/*
Optimized School Method
We can do following optimizations:

Instead of checking till n, we can check till √n because a larger factor of n must be a
multiple of smaller factor that has been already checked.
The algorithm can be improved further by observing that all
primes are of the form 6k ± 1, with the exception of 2 and 3.
This is because all integers can be expressed as (6k + i)
for some integer k and for i = -1, 0, 1, 2, 3, or 4; 2 divides (6k + 0), (6k + 2), (6k + 4);
and 3 divides (6k + 3). So a more efficient method is to test if n is divisible by 2 or 3,
then to check through all the numbers of form 6k ± 1.
Source :: https://en.wikipedia.org/wiki/Primality_test#Simple_method
*/
// check if prime or not
bool is_prime(const uint32_t& x) {
    // check for fact or 3
    if (x <= 3) return x > 1;

    // check if a factor of 2 or 3
    if (!(x & 1) || !(x % 3)) return false;

    // incrementing by 6 skips over multiples of 2 and 3
    // 6k + i or 6k - i
    for (uint32_t i = 5; i*i <= x; i += 6) {
        if ( !(x%i) || !(x%(i+2)) )
            return false;
    }
    return true;
}


bool fillVectorFromFile(const std::string& fileName, std::vector<int>& vect) {
    std::ifstream freader(fileName);

    if (!freader.is_open()) return false;

    std::string line;
    std::vector<std::string> splitVect;
    std::getline(freader, line);

    if (!line.empty())
        split(line, ',', splitVect);
    else
        return false;

    for (const auto& el : splitVect) {
        vect.push_back(
                static_cast<int>(
                        std::strtoll(el.c_str(), 0, 10)
                )
        );
    }
    return true;
}


std::vector<int> findBitPositions(uint64_t val) {
    uint64_t mask = 1;
    std::vector<int> res;
    for (int shiftBy = 0; shiftBy < sizeof(uint64_t)*8; shiftBy++) {
        if ((val & mask) > 0) res.push_back(shiftBy);
        mask <<= 1;
    }
    return res;
}
