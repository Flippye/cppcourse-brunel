#ifndef CORTEX_H
#define CORTEX_H

#include "neuron.hpp"

#include <vector>
#include <fstream>

class cortex : public neuron {
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
	@brief : getter for a single neuron in our cortex
	@param index : number of the wanted neuron
	@return : a pointer on neuron
	*/
	neuron* getNeuron(unsigned int index) const;
	
	/**
	@brief : getter for the connexion matrix of our cortex
	@return : a vector<vector<int>> representating the connexion matrix between the neurons
	*/
	std::vector<std::vector<int>> getConnexionMatrix() const;
	
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
	@param plotOrSimulation : boolean allowing us to create a connexion matrix with the good size if we choose either to dra the plots or to run the simulation
	*/
	void addAConnexion(unsigned int row, unsigned int column, bool plotOrSimulation);
	
	/**
	@brief : creates a randon connexion matrix with the same number of connexions between inhibatory and excitatory neurons
	@param nbNeuronsE : number of excitatory neurons
	@param nbNeuronsI : number of inhibitory neurons
	@param plotOrSimulation : boolean allowing us to create a connexion matrix with the good size if we choose either to dra the plots or to run the simulation
	*/
	void createRandomConnexionMatrix(unsigned int nbNeuronsE, unsigned int nbNeuronsI, bool plotOrSimulation);
	
	/**
	@brief : reset the connexion matrix for testinf purposes
	*/
	void resetConnexionMatrix();
	
	/**
	@brief : updates all neurons inside the vector neurons_
	@param nit : number of iteration of the simulation
	*/
	void updateAll(unsigned int nit);
	
	/**
	@brief : creates a document called "TimeFlies.csv" storing the time of all the spikes and the number of the neuron spiking
	*/
	void timeOfTheSpikes();
	
	/**
	@brief : stores in a given file the time of the spikes and the neuron number
	@param fileUno : given file to store the spikes times and the neurons number
	*/
	void storeInFile(std::ofstream& fileUno);
	
	/**
	@brief : allows to add just one neuron to the neurons_ vector
	@param neuronToAdd : pointer on the neuron taht we want to add to neurons_
	*/
	void initiateNeuron(neuron* neuronToAdd);
	
	private:
	std::vector<neuron*> neurons_; 						///<neuron network (vector of pointers on neuron)
	std::vector<std::vector<int>> connexionMatrix_; 	///<matrix that represents the connexion between the neurons (lines send a spike, columns receive it)
	unsigned int neuronNb_; 							///<number of neurons inside neurons_
	
	double h_ = 0.1; 							///<integration stepsize
	const double delay_ = 1.5;					///<synaptic delay [ms]
	const int delaySteps_ = (int) (delay_/h_); 	///<number of time steps of the synaptic delay (int conversion)
	
	
};

#endif
