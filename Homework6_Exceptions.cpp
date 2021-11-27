#include<iostream>

enum class IntError{
	ZERO,
	OVERFLOW
};

class IntException: public std::exception{
private:
	IntError code;
public:
	IntException(IntError code): code(code) {}
	
	const char* what() const throw() override{
		if(code == IntError::OVERFLOW) return "overflow";
		else if(code == IntError::ZERO) return "division by zero";
		
	}	
};

class Int
{
private:
	int val;
	int max = 2000;
	int min = -2000;	
public:		
	Int(): Int(0){}
	Int(int val): val(val) {
	if (val > max or val < min) throw IntException(IntError::OVERFLOW);
	}
	Int(Int const& c): Int(c.val){}
	Int(Int &&c): val(std::move(c.val)){}
	Int& operator=(Int const& c)
    {
        Int tmp(c);        
        std::swap(this->val, tmp.val);
        return *this;
    }
    Int& operator=(Int &&c)
    {
    	Int tmp(std::move(c));
    	std::swap(this->val, tmp.val);
    	return *this;
	}
    Int& operator=(int y)
    {
    	this->val = y;
    	return *this;
	}
    
	~Int(){}
	
	int getInt () const { return val;}
		
		void subtr (Int y){
		if (this->val - y.val > max or this->val - y.val < min) throw IntException(IntError::OVERFLOW);	
		else std::cout << "x - y = " << this->val - y.val << '\n';
	}
	
	void addition (Int y){		
		if (this->val + y.val > max or this->val + y.val < min) throw IntException(IntError::OVERFLOW);	
		else std::cout << "x + y = " << this->val + y.val << '\n';	
	}
	
	void multipl (Int y){
		if (this->val * y.val > max or this->val * y.val < min) throw IntException(IntError::OVERFLOW);	
		else std::cout << "x * y = " << this->val * y.val << '\n';
	}
	
	void division (Int y){
		if (y.val == 0) throw IntException(IntError::ZERO);	
		else std::cout << "x / y = "<< this->val / y.val << '\n';		
	}
	
	int operator + (int z)	{	
		return this->val + z;
	}
	
	int operator - (int z)	{	
		return this->val - z;
	}
	
};

int main()
{
	try{
		Int x(-100);
		Int y (x + 350);	
		
		x.addition(y);
		x.division(y);	
		x.subtr(y);	
		x.multipl(y);		

	}
	catch (IntException err){
		std::cout << "IntExeption: " << err.what();
	}	
  
  return 0;
}
