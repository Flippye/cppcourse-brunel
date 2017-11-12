#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <cmath>

class neuron {
	public :
	//DOXYGEN
	/**
	@brief : constructor of neuron
	@param mPot : initial membrane potential (per default: 0.0 mV)
	@param Iext : initial external current (per default: 0.0 mV)
	@param type : type of the neuron (either excitatory (true) or inhibitory (false))
	@param poisson : boolean allowing us to choose if we take the poisson distribution into account or not
	@param g : another constant taking into account the type of the neuron (either 5 (excitatory) or -5 (inhibitory))
	@param mu : a constant of the neuron
	@param spikesNb : number of spikes of the neuron (initialized to 0)
	@param clock : personnal clock of the neuron (initialized to 0)
	@param refractoryTime : another internal clock  of the neuron allowing us to know if it is refractory or not (initialized to 2.0 ms)
	*/
	neuron(double mPot=0.0, double Iext=1.01, bool type=true, bool poisson=false, double g=5, double mu=20.0, unsigned int spikesNb=0, int clock=0, double refractoryTime=2.0);
	
	//getters
	/**
	@brief : getter for the membrane potential
	@return : membrane potential of the neuron
	*/
	double getPot() const;
	
	/**
	@brief : getter for the number of spikes of the neuron
	@return : number of spikes of the neuron since the beginning of the simulation
	*/
	unsigned int getSpikesNb() const;
	
	/**
	@brief : getter for the refractory time
	@return : refractory time
	*/
	double getRefractoryTime() const;
	
	/**
	@brief : getter for the stepsize of the simulation
	@return : stepsize of the simulation
	*/
	double getH() const;
	
	/**
	@brief : getter for the current excitatory state of the neuron
	@return : bool as the excitatory state of the neuron (true if excitatory, false if inhibitory)
	*/
	bool getExcitatoryState() const;
	
	/**
	@brief : getter for the spikesTime vector, storing the time of all the spikes of the neuron
	@return : spikesTime_ vector, vector storing the time of all the spikes of the neuron
	*/
	std::vector<double> getSpikesTime() const;
	
	//setters
	/**
	@brief : setter for the membrane potential
	@param mPot : new membrane potential
	*/
	void setPot(double mPot);
	
	/**
	@brief : setter for the external current
	@param newExternalCurrent : the new wanted external current
	*/
	void setIext(double newExternalCurrent);
	
	/**
	@brief : setter for the number of spikes of the neuron
	@param spikesNb : number of spikes of the neuron (useful for a reinitialisation during the simulation)
	*/
	void setSpikesNb(unsigned int spikesNb);
	
	/**
	@brief : setter for the refractory time
	@param refractoryTime : new refractory time of the neuron
	*/
	void setRefractoryTime(double const refractoryTime);
	
	/**
	@brief : setter for the ring buffer of the neuron
	@param delaySteps : delay allowed inside the simulation, used to determine the size of the ring buffer
	@param whichTypeOfNeuron : bool representing the excitatory state of the neuron sending a spike to us, allowing us to know of which sign is the additional potential
	*/
	void setRingBuffer(int delaySteps, bool whichTypeOfNeuron);
	
	/**
	@brief : empty the ring buffer of the neuron in case it is refractory
	*/
	void emptyRingBuffer();
	
	/**
	@brief : setter for the excitatory state of the neuron
	@param yes : bool (true if the neuron is excitatory, false if it is inhibitory)
	*/
	void setExcitatory(bool yes);
	
	/**
	@brief : setter for the parameter g
	@param newGpoint : new g of the neuron
	*/
	void setG(double newGpoint);
	
	//The Function
	/**
	@brief : update the membrane potential of a neuron
	@param i : number of the iteration of the simulation 
	@return : bool, true if the neuron spiked, false if it didn't
	*/
	bool update(unsigned int i);
	
	private :
	double mPot_;					///<membrane potential [mV]
	double Iext_; 					///<external current [mV]
	bool isExcitatory_ = true;		///<if the neuron is excitatory, bool is true, if the neuron is inhibitory, bool is false (initialized to true)
	bool doWeAcknowledgeTheBackgroundNoise_ = false;		///<boolean to choose if we take into account the poisson distribution (aka the rest of the cortex) (useful to keep the tests working)
	double g_;						///<constant for the neuron, different if excitatory (5) or inhibitory (-5)
	const double MU_EXT_ = 20.0;	///<constant for the poisson distribution
	unsigned int spikesNb_; 		///<number of spikes of the neuron	
	int clock_; 					///<personnal clock of the neuron (not in ms but in number of cycles)
	double refractoryTime_; 		///<refractory time [ms]

	double refractoryMPot_ = 0.0; 	///<initial membrane potential [mV]
	int refractorySteps_ = 0;		///<refractory time converted in simulation steps (initialized to 0, modified in update() if the neuron becomes refractory)
	
	std::vector<double> spikesTime_; 	///<vector with all spikes times of the neuron
	std::vector<int> ringBuffer_; 		///<vector that allows to create a delay when transmitting spikes between neurons (initial size 10)
	
	double h_ = 0.1; 					///<integration stepsize
	const double threshold_ = 20.0; 	///<spike threshold [mV]
	const double capacity_ = 1.00;		///<capacity of the neuron
	const double tau_ = 20.0; 			///<membrane time constant
	const double R_ = (tau_/capacity_); ///<membrane resistance : tau = R*capacity
	const double J_ = 0.1; 				///<additionnal potential for spiking [mV]
	
	const double EXP = (exp(-h_/tau_)); ///<constant for the differential equation
	const double CONST = (R_ * (1-EXP));///<constant for the differential equation
};

#endif 
