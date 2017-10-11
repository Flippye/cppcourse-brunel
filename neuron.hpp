#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <cmath>

class neuron {
	public :
	
	neuron(double mPot, double Iext = 10.0, unsigned int spikesNb = 0, int clock = 0, double refractoryTime = 2.0); //constructor
	
	//getters
	double getPot() const;
	unsigned int getSpikesNb() const;
	std::vector<double> getSpikesTime() const;
	double getRefractoryTime() const;
	double getH() const;
	double getIext() const;
	
	//setters
	void setPot(double mPot);
	void setSpikesNb(unsigned int spikesNb);
	void setRefractoryTime(double const refractoryTime);
	
	void update(unsigned int i);
	bool isRefractory() const;
	
	
	
	private :
	const double threshold_ = 20.0; //spike threshold
	double h_ = 0.1; //integration stepsize
	int refractorySteps_ = 0; //refractory time converted in simulation steps
	const double capacity_ = 1.00;
	const double tau_ = 20.0; //membrane time constant
	const double R_ = (tau_/capacity_); //membrane resistance : tau = R*capacity
	
	//constants
	double EXP = (exp(-h_/tau_));
	double CONST = (R_ * (1-EXP));
	
	double mPot_; //membrane potential
	double Iext_; //external current
	unsigned int spikesNb_; //number of spikes of the neuron	
	int clock_; //personnal clock of the neuron (not in ms but in number of cycles)
	double refractoryTime_; //refractory time (in ms)
	std::vector<double> spikesTime_; //vector with all spikes time of the neuron
};

#endif 
