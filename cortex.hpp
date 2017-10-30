#ifndef CORTEX_H
#define CORTEX_H

#include "neuron.hpp"

#include <vector>

class cortex : public neuron {
	private:
	
	std::vector<neuron*> neurons_; 	//neuron network
	std::vector<std::vector<int>> connexionMatrix_; 	//matrix that represents the connexion between the neurons (lines send a spike, columns receive it)
	
	unsigned int neuronNb_; 		//number of neurons inside neurons_
	const double delay_ = 0.9;		//synaptic delay [ms]
	
	double h_ = 0.1; 							//integration stepsize TEMPORARY SOLUTION
	const int delaySteps_ = (int) (delay_/h_); 	//number of time steps of the synaptic delay (int conversion)
	
	
	
	public:
	cortex(unsigned int neuronNb = 0);	//constructor for excitatory neurons (per default)
	cortex(unsigned int nbNeuronsE, unsigned int nbNeuronsI); 	//constructor allowing to make a distinction between excitatory and inhibitory neurons
	~cortex();							//destructor
	
	/**
	 * at param
	 * at return
	 * */
	double getH() const;
	 
	void increaseNeuronNumber();		//increase the instance that keeps in mind the number of neurons inside the vector neurons_
	void pushbackToNeurons_(neuron* const neuronToAdd);			//adds a pointer to neuron inside the vector neurons_
	void receiveSpike(neuron receiver, bool whichSign);			//puts a spike in the ring buffer of a neuron receiver
	
	void addAConnexion(unsigned int row, unsigned int column);	//add a connexion between two neurons in the connexion matrix
	void createRandomConnexionMatrix(unsigned int nbNeuronsE, unsigned int nbNeuronsI);	//create a randon connexion matrix with the same number of connexions between inhibatory and excitatory neurons
	
	void updateAll(unsigned int nit);	//update all neurons inside the vector neurons_
	
	void timeOfTheSpikes();
};

#endif
