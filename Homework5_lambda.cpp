#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<list>

template<typename T>
T Palindrom(T& words)
{	
	auto p = [](std::string & words) -> bool{	
    for (int i = 0; i < words.size()/2; ++i)
    {		
            if (words[i] != words[words.size() - 1])            
            	return  false;				
        return true;              	
    }
};
      T result;
   for(auto it = words.begin(); it != words.end(); ++it){
   	  if(p(*it))
   	  	 result.push_back(*it); 	
   }  
    return result;
}

int main(){
	  
//std::vector<std::string>words = {"lol", "topot", "the", "cooc", "these"};  
//std::list<std::string>words = {"lol", "topot", "the", "cooc", "these"};
std::deque<std::string>words = {"lol", "topot", "the", "cooc", "these"};	
	
//std::vector<std::string>res = Palindrom(words);
//std::list<std::string>res = Palindrom(words);
std::deque<std::string>res = Palindrom(words);
	
for(auto &i: res) std::cout << i << " ";   

}
