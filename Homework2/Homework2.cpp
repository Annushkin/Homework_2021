#include <iostream>
#include <set>
#include <random>

class State
{
public:
	virtual bool operator()(int prob) const = 0;	
};

class DiscreteState: public State 
{
private:
    int const state;

public:
    DiscreteState(int state): state(state) { }

    bool operator()(int s) const {
        return s == state;
    }
};

class SegmentState: public State
{
private:
    int const beg, end;
    
public:
    SegmentState(): beg(0), end(-1) { }
    SegmentState(int beg, int end): beg(beg), end(end) { }
    
    bool operator()(int s) const {
        return s >= beg && s <= end;
    }
};

class SetState: public State
{
private:
    std::set<int> const states;
    
public:
    SetState(): states() { }
    SetState(std::set<int> const &src): states(src) { }
    
    bool operator()(int s) const {
        return states.count(s) > 0;
    }
};


class CrossState: public State
{	
	private:
		const State &s1, &s2;
	public:
		CrossState(State &s1, State &s2): s1(s1), s2(s2){	}
		
		bool operator()(int s) const {
			return s1(s) and s2(s);
		}
};


class UnionState: public State
{	
	private:
		const State &s1, &s2;
	public:
		UnionState(State &s1, State &s2): s1(s1), s2(s2){	}
		
		bool operator()(int s) const {
			return s1(s) or s2(s);
		}
};


class GapState: public State
{
	private:
		const State &s1, &s2;
	public:
		GapState(State &s1, State &s2): s1(s1), s2(s2){	}
		
		bool operator()(int s) const {
			return s1(s) and !s2(s);
		}
};


class UnionGapState: public State
{
	private:
		const State &s1, &s2, &s3;
	public:
		UnionGapState(State &s1, State &s2, State &s3): s1(s1), s2(s2), s3(s3){	}
		
		bool operator()(int s) const {
			return (s1(s) or s2(s)) and !s3(s);
		}
};	
 
float ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count, State & s)
 {
 	std::default_random_engine rng(seed); 
    std::uniform_int_distribution<int> dstr(test_min,test_max); 
    unsigned good = 0; 
    for (unsigned cnt = 0; cnt != test_count; ++cnt)
        if (s(dstr(rng))) ++good;
        
        return static_cast<float>(good)/static_cast<float>(test_count); 
 }

int main(int argc, const char * argv[]) {
    DiscreteState d1(2);
    DiscreteState d2(12);
    SegmentState s(0,10);
    SetState ss({1, 3, 5, 7, 23, 48, 57, 60, 90, 99});
    UnionState us(s, ss);
    CrossState cs(s, ss);
    GapState gs(s, d1);
    UnionGapState ugs(s, d2, d1);
    int c = 100000;
    int N = 100;
    std::cout << ProbabilityTest (10, 0, N ,c, d1) << '\n';
 	std::cout << ProbabilityTest (10, 0, N, c, s) << '\n';
    std::cout << ProbabilityTest (10, 0, N, c, ss) << '\n';
    std::cout << ProbabilityTest (10, 0, N, c, us) << '\n';
    std::cout << ProbabilityTest (10, 0, N, c, cs) << '\n';
    std::cout << ProbabilityTest (10, 0, N, c, gs) << '\n';
    std::cout << ProbabilityTest (10, 0, N, c, ugs) << '\n';

    return 0;
}
