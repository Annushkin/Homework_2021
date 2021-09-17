#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include<algorithm>

using namespace std;

struct vector3 {
    double x;
    double y;
    double z;
};

class Logger {
private:
    vector<string> l;	
public:
    Logger() = default;
    void log(const string& s)
	{
    	l.push_back(s);
	}
	
	void print_log()
	{
		for(auto i: l) cout<< i << '\n';
	}
   // ~Logger();
};

class Particle {
protected:  
    string name;
	double charge = 0;  //заряд
    vector3 coord = {0, 0, 0}; //координаты
    Logger logger;

public:
    Particle() = default;
    explicit Particle(string name, double charge, vector3 coord): 
						name(name), charge(charge), coord(coord){}
    
     /* string getLog () {return logger;}
	void setLog(string logg) {logger = logg;}*/
	
	string getName () const { return name; }
	double getCh () const {	return charge; }
//   vector3 getCoord () const {return coord;}
    void print_Particle () const
    {
    	cout  << name << ": \tcharge "  << charge << ", \tcoordinats:  x = " 
		     << coord.x << ", y = " << coord.y << ", z = " << coord.z << '\n';
	}
		
	virtual void interaction(Particle& p) 
	{		
		cout << this->name << " <-> " << p.getName () << '\n';
		double q_x = this->charge * p.charge * (this->coord.x - p.coord.x);		
		double q_y = this->charge * p.charge * (this->coord.y - p.coord.y);
		double q_z = this->charge * p.charge * (this->coord.z - p.coord.z);
		double X = pow((this->coord.x - p.coord.x),2);
		double Y = pow((this->coord.y - p.coord.y),2);	
		double Z = pow((this->coord.z - p.coord.z),2);	
		double divider = pow((double)(X + Y + Z), (double)1/3);
		if (divider != 0 and p.charge != 0 and this->charge !=0)
		{
			double F_x = q_x/divider;
			double F_y = q_y/divider;
			double F_z = q_z/divider;			
			cout << "F_x = " << F_x << '\n';
			cout << "F_y = " << F_y << '\n';
			cout << "F_z = " << F_z << '\n';
		}		
	}
};

class Electron : public Particle 
{
public:
    explicit Electron(string name, double charge, vector3 coord): Particle(name, charge, coord)
    {    	
		logger.log("Electron was created");
	}
	
    void interaction(Particle& p) override
    {
    	Particle::interaction(p); 
    	if (this->charge < 0 and p.getCh () == 0)
		{
			cout << "no interaction\n";
			logger.log("there is no interaction between electron and  neutron");	
		}
		else
		{
			
	    	if(this->charge < 0 and p.getCh () < 0) 
				logger.log("two electrons are repelled");
	    	else if (this->charge < 0 and p.getCh () > 0) 
				logger.log("electron and proton are attracted");			
		}
		cout << '\n';    		    	
	}
	
    ~Electron()
    {
    	logger.log("Electron was delete");
    	logger.print_log();
	}
};

class Proton : public Particle {
public:
    explicit Proton(string name, double charge, vector3 coord): Particle(name, charge, coord)
    {    	
		logger.log("Proton was created");
	}
	
    void interaction(Particle& p) override
    {
    	Particle::interaction(p);
    	if (this->charge > 0 and p.getCh () == 0)
		{
			cout << "no interaction\n";
			logger.log("there is no interaction between proton and  neutron");	
		}
		else
		{
			if(this->charge > 0 and p.getCh () > 0) 
				logger.log("two protons are repelled");
    		else if (this->charge > 0 and p.getCh () < 0) 
				logger.log("proton and electron are attracted");  
		} 
		cout << '\n';
	}
	
    ~Proton()
    {
    	logger.log("Proton was delete");
    	logger.print_log();
	}
};

class Neutron : public Particle {
public:
    explicit Neutron(string name, double charge, vector3 coord): Particle(name, charge, coord)
    {    	
		logger.log("Neutron was created");
	}
	
    void interaction(Particle& p) override
    {
    	Particle::interaction(p);
    	cout << "no interaction\n"; 
       	if (this->charge == 0 and p.getCh () < 0) 
			logger.log("there is no interaction between neutron and electron");
    	else if (this->charge == 0 and p.getCh () > 0) 
			logger.log("there is no interaction between neutron and proton");
		cout << '\n';	
	}	
	
    ~Neutron()
    {
    	logger.log("Neutron was delete");
    	logger.print_log();
	}	
};

class World 
{
private:
    vector<Particle> v;
    
public:
    //const vector<Particle>& getv() const { return v; }
    void addParticle(const Particle& p)
    {
    	v.push_back(p);
	} 
	
    //void deleteParticle(const Particle& p){	}
    
    friend ostream& operator<<(ostream& os, const World& w);
};

ostream& operator<<(ostream& os, const World& w)
{
	cout << "This world contains:\n";
	for(int i = 0; i < w.v.size(); i++)
        {            
			w.v[i].print_Particle();             
        } 
	cout << '\n';      
	return os;
}

int main() 
{
	Electron one ("electron", -5, {4, 2, 8});
	Proton two ("proton", 9, {6, 7, 3});
	Neutron three ("neutron", 0, {8, 1, 9});
	one.interaction(two);
	one.interaction(three);
	two.interaction(one);
	two.interaction(three);
	three.interaction(one);
	three.interaction(two);
	World A;
	A.addParticle(one);
	A.addParticle(two);
	A.addParticle(three);
	cout << A;
}
