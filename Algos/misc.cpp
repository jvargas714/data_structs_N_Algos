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

/*
  take integer input and return string representation of that integer ie 123456 --> 123,456
*/
std::string format_number(const int& num) {
  std::string result("");
  std::string sign = "";
  const unsigned int ASCII_ZERO = 48; 
  const char SEP = ',';
  bool neg = (num<0);
  unsigned int tmp, charCnt=0;
  int rem = num;
  
  if(neg) {
    sign = "-";
    rem*=-1;
  }
  if (num == 0) {
    return "0";
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
