#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<deque>
#include<set>

template<typename T>
T Palindrom(T& words)
{	
	auto p = [](std::string words) -> bool{	
    if (words.size() < 2) return true;
    else{	
		for (int i = 0; i < words.size()/2; ++i)
	    {		
	            if (words[i] != words[words.size() - 1])            
	            	return  false;				
	        return true;              	
	    }
 	}
};  
   
   T result; 	
   	for(auto &i: words)  
   		if (p(i)) result.insert(result.end(), i);	
   		
    return result;
}

int main(){	  

	std::vector<std::string>words_v = {"lol", "topot", "the", "cooc", "these", " ", "l"};
	std::list<std::string>words_l = {"lol", "topot", "the", "cooc", "these", " ", "l"};
	std::deque<std::string>words_d = {"lol", "topot", "the", "cooc", "these", " ", "l"};
	std::set<std::string>words_s = {"lol", "topot", "the", "cooc", "these", " ", "l"};	

	std::vector<std::string>res_v = Palindrom(words_v);
	std::list<std::string>res_l = Palindrom(words_l);
	std::deque<std::string>res_d = Palindrom(words_d);
	std::set<std::string>res_s = Palindrom(words_s);
	
	std::cout << "v: ";
	for(auto &i: res_v) std::cout << i << " ";  
	std::cout << '\n' << '\n'; 
	
	std::cout << "l: ";
	for(auto &i: res_l) std::cout << i << " ";  
	std::cout << '\n' << '\n';
	
	std::cout << "d: ";
	for(auto &i: res_d) std::cout << i << " ";  
	std::cout << '\n' << '\n';
	
	std::cout << "s: ";
	for(auto &i: res_s) std::cout << i << " ";  
	std::cout << '\n' << '\n';
}
