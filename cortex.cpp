#include <iostream>
#include "cortex.hpp"

void cortex::pushbackToNeurons_(neuron* const neuronToAdd)
{
	neurons_.push_back(neuronToAdd);
}

void cortex::receiveSpike(neuron receiver)
{
	receiver.setRingBuffer(delaySteps_);	
}

void cortex::updateAll(unsigned int nit)
{
	//we check if the vector isn't empty
	if(neuronNb_ > 0) 
	{
		//we make an iteration on all the time steps of the simulation
		for(unsigned int i = 0; i < nit; ++i) 
		{
			//at each time step we update each neuron by iteration on the vector
			for(unsigned int j = 0; j < neurons_.size(); ++j) 
			{
				/*if we have a spike, isItASpike becomes true 
				 * and allow the access to the following if condition*/
				 
				bool isItASpike (neurons_[j]->update(i)); 
				
				/*if the neuron has spiked and if we are not at the end of the vector, 
				 * the additionnal potential created by the spike is given to the next neuron*/
				if(isItASpike and (j+1)<neurons_.size()) 
				{
					receiveSpike(*neurons_[j+1]);
				}
			}
		}	
	}
}
