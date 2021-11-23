#include<iostream>
#include<string>
#include<vector>
#include<deque>

template<typename T, int s>
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
   for(int i = 0; i < words.size(); ++i){
   	  if(p(words[i]))
   	  	 result.push_back(words[i]); 	
   }  
    return result;
}


int main(){
	  
	//std::vector<std::string>words = {"lol", "topot", "the", "cooc", "these"};  
	std::deque<std::string>words = {"lol", "topot", "the", "cooc", "these"};	 
	
	//std::vector<std::string>res = Palindrom(words);
    std::deque<std::string>res = Palindrom(words);     
	
	for(auto &i: res) std::cout << i << " ";    

}
