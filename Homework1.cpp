#include <iostream>
#include <vector>
#include <string>
#include <cmath>

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
    //string name;
	double charge = 0;  //заряд
    vector3 coord = {0, 0, 0}; //координаты
   // vector3 force = {0, 0, 0};  //сила
   
        
    Logger logger;

public:
    Particle() = default;
    explicit Particle(double charge, vector3 coord): charge(charge), coord(coord){}
    
   /* string getLog () {return logger;}
	void setLog(string logg) {logger = logg;}*/
	
//	double getCh () const {	return charge; }
//   vector3 getCoord () const {return coord;}
    void print_Particle () const
    {
    	cout << charge << " " << coord.x << " " << coord.y << " " << coord.z << '\n';
	}
		
	virtual void interaction(Particle& p) 
	{
		double q_x = this->charge * charge * (this->coord.x - coord.x);
		double q_y = this->charge * charge * (this->coord.y - coord.y);
		double q_z = this->charge * charge * (this->coord.z - coord.z);
		double X = pow((this->coord.x - coord.x),2);
		double Y = pow((this->coord.y - coord.y),2);	
		double Z = pow((this->coord.z - coord.z),2);	
		double divider = pow((double)(X + Y + Z), (double)1/3);
		double F_x = q_x/divider;
		double F_y = q_y/divider;
		double F_z = q_z/divider;
		//cout << F_x << " " << F_y << " " << F_z;
	}
};


class Electron : public Particle {
public:

    explicit Electron(double charge, vector3 coord): Particle(charge, coord)
    {    	
		logger.log("Electron was created");
	}
	
    void interaction(Particle& p) override
    {
    	Particle::interaction(p);
    	if(this->charge < 0 and charge < 0) logger.log("two electrons are repelled");
    	else if (this->charge < 0 and charge > 0) logger.log("electron and proton are attracted");
    	else if (this->charge < 0 and charge == 0)logger.log("there is no interaction between electron and  neutron");	    	
	}
	
    ~Electron()
    {
    	logger.log("Electron was delete");
    	logger.print_log();
	}
};

class Proton : public Particle {
public:

    explicit Proton(double charge, vector3 coord): Particle(charge, coord)
    {    	
		logger.log("Proton was created");
	}
	
    void interaction(Particle& p) override
    {
    	Particle::interaction(p);
    	if(this->charge > 0 and charge > 0) logger.log("two protons are repelled");
    	else if (this->charge > 0 and charge < 0) logger.log("proton and electron are attracted");
    	else if (this->charge > 0 and charge == 0) logger.log("there is no interaction between proton and  neutron");	
	}
	
    ~Proton()
    {
    	logger.log("Proton was delete");
    	logger.print_log();
	}
};


class World 
{
private:
    vector<Particle> v = {};
public:
    
   
    const vector<Particle>& getv() const
	{
     return v;
   	}
   
    void addParticle(const Particle& p)
    {
    	v.push_back(p);
	}
 
   // void deleteParticle(const Particle& p);

    
    friend ostream& operator<<(ostream& os, const World& w);
};

ostream& operator<<(ostream& os, const World& w)
{
	for(int i = 0; i < w.v.size(); i++)
        {
             w.v[i].print_Particle(); 
             cout << '\n';
        }
       
	return os;
}


int main() {

Electron one (-5, {4, 2, 8});
Proton two (9, {6, 7, 3});
two.interaction(one);
World A;
A.addParticle(one);
A.addParticle(two);
cout << A;	

}
