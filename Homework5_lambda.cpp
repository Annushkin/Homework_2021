#include<iostream>
#include<vector>
#include<list>
#include<deque>
#include<set>
#include<map>

template<typename T>
T Palindrom(const T& words)
{
	auto p = [](std::string words) -> bool {
		if (words.size() < 2) return true;
		else {
			for (int i = 0; i < words.size() / 2; ++i)
			{
				if (words[i] != words[words.size() - 1])
					return  false;
				return true;
			}
		}
	};
	T result;

	for (auto& i : words) {
		if (p(i)) result.insert(result.end(), i);

	}
	return result;
}

template<>
std::map<int, std::string> Palindrom<std::map<int, std::string>>(const std::map<int, std::string>& words)
{
	auto p = [](std::string words) -> bool {
		if (words.size() < 2) return true;
		else {
			for (int i = 0; i < words.size() / 2; ++i)
			{
				if (words[i] != words[words.size() - 1])
					return  false;
				return true;
			}
		}
	};
	std::map<int, std::string> result;

	for (auto& i : words) {
		if (p(i.second)) result.insert({ i.first, i.second });

	}
	return result;
}

int main(){	  

	std::vector<std::string>words_v = {"lol", "topot", "the", "cooc", "these", " ", "l"};
	std::list<std::string>words_l = {"lol", "topot", "the", "cooc", "these", " ", "l"};
	std::deque<std::string>words_d = {"lol", "topot", "the", "cooc", "these", " ", "l"};
	std::set<std::string>words_s = {"lol", "topot", "the", "cooc", "these", " ", "l"};
	std::map<int, std::string>words_m = {{1, "lol"}, {2, "topot"}, {3, "the"}, {4, "cooc"}, {5, "these"}, {6, " "}, {7, "l"}};

	std::vector<std::string>res_v = Palindrom(words_v);
	std::list<std::string>res_l = Palindrom(words_l);
	std::deque<std::string>res_d = Palindrom(words_d);
	std::set<std::string>res_s = Palindrom(words_s);
	std::map<int, std::string>res_m = Palindrom(words_m);
	
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
	
	std::cout << "m: ";
	for (auto& i : res_m) std::cout << i.second << " ";
	std::cout << '\n' << '\n';
}
