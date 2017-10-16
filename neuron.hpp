#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <cmath>

class neuron {
	
	private :

	double mPot_; 				//membrane potential
	double Iext_; 				//external current
	unsigned int spikesNb_; 	//number of spikes of the neuron	
	int clock_; 				//personnal clock of the neuron (not in ms but in number of cycles)
	double refractoryTime_; 	//refractory time (in ms)
	std::vector<double> spikesTime_; 	//vector with all spikes time of the neuron
	std::vector<int> ringBuffer_; 		//vector that allows to create a delay when transmitting spikes between neurons (initial size 10)
	
	const double threshold_ = 20.0; 	//spike threshold
	double h_ = 0.1; 					//integration stepsize
	int refractorySteps_ = 0;			//refractory time converted in simulation steps
	const double capacity_ = 1.00;
	const double tau_ = 20.0; 			//membrane time constant
	const double R_ = (tau_/capacity_); //membrane resistance : tau = R*capacity
	const double J_ = 0.1; 				//additionnal potential for spiking [mV]

	//constants
	double EXP = (exp(-h_/tau_));
	double CONST = (R_ * (1-EXP));
	
	
	
	public :
	
	neuron(double mPot, double Iext = 10.0, unsigned int spikesNb = 0, int clock = 0, double refractoryTime = 2.0); //constructor
	
	//getters
	double getPot() const; 				//return the membrane potential
	unsigned int getSpikesNb() const; 	//return the number of spikes of the neuron
	double getRefractoryTime() const; 	//retunrn the refractory time
	double getH() const;				//return the stepsize of the simulation 
	double getIext() const;				//return the external current
	
	//setters
	void setPot(double mPot);					//set a new membrane potential
	void setSpikesNb(unsigned int spikesNb); 	//set the number of spikes of the neuron
	void setRefractoryTime(double const refractoryTime); 	//set the refractory time
	void setRingBuffer(int delaySteps); 		//allow us to create a delay between neurons when spiking
	
	bool update(unsigned int i); //return true if we have a spike, else false

};

#endif 
