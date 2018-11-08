#ifndef DATASTRUCTS_N_ALGOS_DESIGN_PROBLEMS_H
#define DATASTRUCTS_N_ALGOS_DESIGN_PROBLEMS_H
#include <stack>
#include <vector>
#include <cstddef>
#include <string>

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%EASY%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// problem #155
// result: 79.71% 29 ms
/*
 * arr[(i-1)/2] --> returns parent node
 * arr[(2i)+1] --> returns left child node
 * arr[(2i)+2] --> returns right child node
 *
 * ["MinStack","push","push","push","push","pop","getMin","pop","getMin","pop","getMin"]
[[],[512],[-1024],[-1024],[512],[],[],[],[],[],[]]
 * */
class MinStack {
public:
    MinStack(): _size(0){};
    void push(int x);
    void pop();
    int top();
    int getMin();
private:
    inline size_t parent(size_t i) const { return (i-1)/2; }
    inline size_t left(size_t i) const { return (2*i)+1; }
    inline size_t right(size_t i) const { return (2*i)+2; }
    void deleteNode(size_t i);
    void heapify(size_t i);
    void decreaseNode(size_t i, int val);
    size_t _size;
    std::stack<int> _stk;
    std::vector<int> _data;
};

// second version (much faster uses two stacks instead)
class MinStackV2 {
public:
    /** initialize your data structure here. */
    MinStackV2()=default;

    void push(int x) {
        stack1.push(x);
        if(stack2.empty())
            stack2.push(x);
        else {
            if(stack2.top() > x)
                stack2.push(x);
            else
                stack2.push(stack2.top());
        }
    }

    void pop() {
        if(!stack1.empty() && !stack2.empty()){
            stack1.pop();
            stack2.pop();
        }
    }

    int top() {
        if(!stack1.empty()) return stack1.top();
        else return -1;
    }

    int getMin() {
        if(!stack2.empty()) return stack2.top();
        else return -1;
    }
private:
    std::stack<int> stack1;
    std::stack<int> stack2;
};

/*
Write a program that outputs the string representation of numbers from 1 to n.
But for multiples of three it should output “Fizz” instead of the number and for the multiples
 of five output “Buzz”. For numbers which are multiples of both three and five output “FizzBuzz”.
*/
std::vector<std::string> fizzBuzz(const int &n);





#endif //DATASTRUCTS_N_ALGOS_DESIGN_PROBLEMS_H
