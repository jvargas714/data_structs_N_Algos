#include <iostream>
#include <vector>

using namespace std;

/*
	t 	: # of trips 
	m 	: pool of money they have
	n 	: # flavors 
	i 	: flavor id #
	c_i : cost associated with flavor id

	-- must spend all money m 
	-- print 2 flavors they choose (lowest id first)
	-- ice creams may cost the same


*/


class IceCream {
    
    public: 
        int flavor; 
        int index;

        IceCream(int flavor, int index) { // index id and flavor is cost
            
       }
};
    
int binarySearch(int first, int last, vector<IceCream> arr, int search) {
   
}


int main() {
    int t;
    int n, m;
    cin >> t;
    for(int test = 0; test < t; test++) {       
        cin >> m >> n;
        vector<IceCream> arr;
        arr.reserve(n); 

        for (int i = 0; i < n; i++) {
            int cost;
            cin >> cost;
            arr.push_back(IceCream(cost, i + 1));
        }

        sort(arr.begin(), arr.end(), compare);
        int firstIndex = 100000, secondIndex = 100000;
        for(int i = 0; i < n - 1 ; i++) {
            int search = m - arr[i].flavor;
            if(search >= arr[i].flavor) {
                int index = binarySearch( i + 1, n - 1, arr, search);
                if( index != -1 ) {
                    cout << min(arr[i].index, index) << " " << max(arr[i].index, index) << endl;
                    break;

                }
            }
        }

    }

}