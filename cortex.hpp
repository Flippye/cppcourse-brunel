#ifndef CORTEX_H
#define CORTEX_H

#include "neuron.hpp"

#include <vector>

class cortex : public neuron {
	private:
	
	std::vector<neuron*> neurons_; 	//neuron network
	unsigned int neuronNb_; 		//number of neurons inside neurons_
	const double delay_ = 0.9;		//synaptic delay [ms]
	
	double h_ = 0.1; 							//integration stepsize TEMPORARY SOLUTION
	const int delaySteps_ = (int) (delay_/h_); 	//number of time steps of the synaptic delay
	
	public:
	void receiveSpike(neuron receiver);	//puts a spike in the ring buffer of a neuron
	void updateAll(unsigned int nit);	//update all neurons inside the vector neurons_

};

#endif
