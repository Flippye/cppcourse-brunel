#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "cortex.hpp"
#include <iostream>

class experiment{
	public:
	/**
	@brief : constructor of the class experiment
	*/
	experiment();
	
	/**
	@brief : destructor of the class experiment
	*/
	~experiment();
	
	/**
	@brief : launches a simulation
	@param g : a neuron constant, dependant on the type of the neuron
	@param mu : a neuron constant, used for the poisson distribution
	@param time : time of the simulation
	@param fileUno : file to store the results of the simulation
	*/
	void setSimulation(double g, double mu, double time, std::ofstream& fileUno);
	
	private:
	cortex coco_;		///<a simulation needs a cortex to be launched
	
};

#endif 
