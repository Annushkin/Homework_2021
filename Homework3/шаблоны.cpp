#include<iostream>

template<typename T>
T f_min(const T& a, const T& b){
	if(a <= b) return a;
	 return b;
	}

template<typename T>
T f_max(const T& a, const T& b){
	if(a >= b) return a;
	 return b;
	}
template<typename T>

void swap(T& a, T& b){
T c = a;
a = b;
b = c;	
}

template<typename T>
T abs(T a){
	return sqrt(a*a);
}

template<unsigned N>
unsigned fact()
{
	return N*fact <N-1>();
}

template<>
unsigned fact<1>()
{
	return 1;
}

	
int main(){
	int a, b;
	std::cin >> a >> b;
	std::cout << f_max(a, b) << " " << f_min(a, b) << '\n'; 
	swap(a, b);
	std::cout << a << " " << b << '\n'; 
	std::cout << abs(-8) << '\n';
	std::cout << fact<5>() << '\n';
}
