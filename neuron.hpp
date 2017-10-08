#ifndef NEURON_H
#define NEURON_H

#include <vector>

class neuron {
	public :
	
	neuron(double mPot, unsigned int spikesNb = 0); //constructor
	
	//getters
	double getPot();
	unsigned int getSpikesNb();
	std::vector<double> getSpikesTime();
	
	//setters
	void setPot(double mPot);
	void setSpikesNb(unsigned int spikesNb);
	//void setSpikesTime();
	
	void update(double t, double exp, double constante, double Iext);
	
	
	private :
	
	double mPot_;
	unsigned int spikesNb_;
	std::vector<double> spikesTime_;
};

#endif
