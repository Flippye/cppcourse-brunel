#ifndef CORTEX_H
#define CORTEX_H

#include "neuron.hpp"

#include <vector>

class cortex : public neuron {
	private:
	
	std::vector<neuron*> neurons_; 	///<neuron network
	std::vector<std::vector<int>> connexionMatrix_; 	///<matrix that represents the connexion between the neurons (lines send a spike, columns receive it)
	
	unsigned int neuronNb_; 		///<number of neurons inside neurons_
	const double delay_ = 0.9;		///<synaptic delay [ms]
	
	double h_ = 0.1; 							///<integration stepsize TEMPORARY SOLUTION
	const int delaySteps_ = (int) (delay_/h_); 	///<number of time steps of the synaptic delay (int conversion)
	
	
	
	public:
	/**
	@brief : constructor per default, construct only excitatory neurons
	@param neuronNb : number of neurons to create the cortex with
	*/
	cortex(unsigned int neuronNb = 0);
	
	/**
	@brief : constructor allowing to make a distinction between excitatory and inhibitory neurons
	@param nbNeuronsE : number of excitatory neurons
	@param nbNeuronsI : number of inhibitory neurons
	*/
	cortex(unsigned int nbNeuronsE, unsigned int nbNeuronsI);
	
	/**
	@brief : destructor of the class
	*/
	~cortex();
	
	/**
	@brief : getter for the integration stepsize
	@return : integration stepsize
	*/
	double getH() const;
	
	/**
	@brief : function that keeps track of the number of neurons inside the vector containing all the neurons (called neurons_)
	*/
	void increaseNeuronNumber();
	
	/**
	@brief : adds a pointer to neuron inside the vector neurons_
	@param neuronToAdd : pointer to neuron that we want to add to our vector containing all the pointers to neurons
	*/
	void pushbackToNeurons_(neuron* const neuronToAdd);
	
	/**
	@brief : puts a spike in the ring buffer of a neuron receiver, taking into account the state of the sender neuron (excitatory or inhibitory)
	@param receiver : neuron that will receive a spike to store inside its ring buffer
	@param whichSign : state of the neuron sending the spike (excitatory or inhibitory)
	*/
	void receiveSpike(neuron receiver, bool whichSign);
	
	/**
	@brief : adds a connexion between two neurons in the connexion matrix
	@param row : index of the row to store the information of the connexion
	@param column : index of the column to store the information of the connexion
	*/
	void addAConnexion(unsigned int row, unsigned int column);
	
	/**
	@brief : creates a randon connexion matrix with the same number of connexions between inhibatory and excitatory neurons
	@param nbNeuronsE : number of excitatory neurons
	@param nbNeuronsI : number of inhibitory neurons
	*/
	void createRandomConnexionMatrix(unsigned int nbNeuronsE, unsigned int nbNeuronsI);
	
	/**
	@brief : updates all neurons inside the vector neurons_
	@param nit : number of iteration of the simulation
	*/
	void updateAll(unsigned int nit);
	
	/**
	@brief : creates a document called "TimeFlies.csv" storing the time of all the spikes and the number of the neuron spiking
	*/
	void timeOfTheSpikes();
};

#endif
