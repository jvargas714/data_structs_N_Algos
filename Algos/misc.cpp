#include "misc.h"


bool check_order(std::vector<int>& v){
// now we can check if its a bin tree or not
       for(int i = 0; i < v.size(); i++){

           for(int j = i+1; j < v.size(); j++){

               if( v[i] > v[j] || 
                            v[i] == v[j] ){
               		std::cout << "i: " << i  << " j: " << j << std::endl; 
               		std::cout << v[i] << " > " << v[j] << std::endl; 
                   return false;
               }
           }
       }return true;
}


// Worst Case: O(n^2)
// bool unique_chars( const std::string& str )
// {
// 	// check for empty string
// 	if( !str.size() )
// 		return false;

// 	// can try a brute strength way first
// 	//for( auto it = str.begin(); it != str.end(); ++it )
// 	for( std::string::iterator it = str.begin(); it != str.end(); ++it )
// 	{
// 		for( auto it_ = it+1; it_ != str.end(); ++it_ )
// 		{
// 			if( *it == *it_ )
// 				return false;
// 		}
// 	}
// 	return true;
// }