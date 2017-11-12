#include <iostream>
#include <fstream>
#include <vector>
#include <random>

#include "cortex.hpp"

cortex::cortex(unsigned int neuronNb)
{
	//we fill our vector of pointers to neurons with the number of neurons chosen by the utilisator
	for (unsigned int i = 0; i < neuronNb; ++i)
	{
		neurons_.push_back(new neuron);
	}
}

cortex::cortex(unsigned int nbNeuronsE, unsigned int nbNeuronsI)
{
	//we fill our vector of pointers to neurons with the number of neurons chosen by the utilisator
	for (unsigned int i = 0; i < nbNeuronsE; ++i)
	{
		neurons_.push_back(new neuron);
		neurons_[i]->setExcitatory(true);
		neurons_[i]->setG(5);
	}
	
	for (unsigned int i = nbNeuronsE; i < (nbNeuronsE + nbNeuronsI); ++i)
	{
		neurons_.push_back(new neuron);
		neurons_[i]->setExcitatory(false);
		neurons_[i]->setG(-5);
	}
	
	connexionMatrix_.resize(nbNeuronsE+nbNeuronsI);
	createRandomConnexionMatrix(nbNeuronsE, nbNeuronsI, false);
}

cortex::~cortex()
{
	//the destructor must delete all its pointers on neurons
	for (unsigned int i = 0; i < neurons_.size(); ++i)
	{		
		delete neurons_[i];
		neurons_[i] = NULL;
	}
}

double cortex::getH() const
{
	return h_;
}

std::vector<std::vector<int>> cortex::getConnexionMatrix() const
{
	return connexionMatrix_;
}

neuron* cortex::getNeuron(unsigned int index) const
{
	return neurons_[index];
}

void cortex::increaseNeuronNumber()
{
	++neuronNb_;
}

void cortex::pushbackToNeurons_(neuron* const neuronToAdd)
{
	neurons_.push_back(neuronToAdd);
}

void cortex::receiveSpike(neuron receiver, bool whichSign)
{
	receiver.setRingBuffer(delaySteps_, whichSign);
}

void cortex::addAConnexion(unsigned int numberOfSenderNeuron, unsigned int numberOfReceiverNeuron, bool plotOrSimulation)
{
	if (plotOrSimulation)
	{
		connexionMatrix_.resize((12500), std::vector<int> (1250));
	}
	connexionMatrix_[numberOfSenderNeuron].push_back(numberOfReceiverNeuron);
}

void cortex::createRandomConnexionMatrix(unsigned int nbNeuronsE, unsigned int nbNeuronsI, bool plotOrSimulation)
{
	std::random_device randomD;
	std::mt19937 gen(randomD());
	std::uniform_int_distribution<> excitatoryDistribution(0, nbNeuronsE-1);
	std::uniform_int_distribution<> inhibitoryDistribution(nbNeuronsE, nbNeuronsE+nbNeuronsI-1);
	
	for (unsigned int i = 0; i < neurons_.size(); ++i) //we iterate on all our vector of neurons_
	{
		for (unsigned int j = 0; j < nbNeuronsE/10; ++j) //the lines send a spike, the column receives it
		{
			addAConnexion(i, excitatoryDistribution(gen), plotOrSimulation);
		}
		for (unsigned int k = 0; k < nbNeuronsI/10; ++k)
		{
			addAConnexion(i, inhibitoryDistribution(gen), plotOrSimulation);
		}
	}
}

void cortex::resetConnexionMatrix()
{
	for (unsigned int i = 0; i < connexionMatrix_.size(); ++i)
	{
		for (unsigned int j = 0; i < connexionMatrix_[i].size(); ++j)
		{
			connexionMatrix_[i][j]=0;
		}
	}
}

void cortex::updateAll(unsigned int nit)
{
	if(neuronNb_ > 0) //we check if the vector isn't empty
	{
		for(unsigned int i = 0; i < nit; ++i) //we make an iteration on all the time steps of the simulation
		{
			for(unsigned int j = 0; j < neurons_.size(); ++j) //at each time step we update each neuron by iteration on the vector neurons_
			{
				/*if we have a spike, isItASpike becomes true 
				 * and allow the access to the following if condition*/
				bool isItASpike (neurons_[j]->update(i)); 
				
				/*if the neuron has spiked, we send its membrane potential (different depending on if 
				 * it's an excitatory or inhibitory neuron) to all the neurons it is connected with*/
				if(isItASpike) 
				{
					bool whatStateIsMyNeuronSpikingIn(neurons_[j]->getExcitatoryState()); //long variable name but at least it's comprehensible
					
					for (unsigned int k = 0; k < connexionMatrix_[j].size(); ++k) //we iterate on the connexionMatrix_
					{
						receiveSpike(*neurons_[connexionMatrix_[j][k]], whatStateIsMyNeuronSpikingIn);
					}
				}
			}
		}	
	}
}

void cortex::timeOfTheSpikes()
{
	std::ofstream documentContainingTheSpikesTime("TimeFlies.csv"); //csv = document Excel + facile à lire
	if (!documentContainingTheSpikesTime.fail())
	{
		for (unsigned int i = 0; i < neurons_.size(); ++i) //neuron iteration
		{
			for (unsigned int j = 0; j < neurons_[i]->getSpikesTime().size(); ++j)
			{
				documentContainingTheSpikesTime << neurons_[i]->getSpikesTime()[j] << '\t' << i << '\n';
			}	
		}	
	}
	documentContainingTheSpikesTime.close();
}

void cortex::storeInFile(std::ofstream& fileUno)
{
	try
	{
		if (fileUno.fail())
		{
			throw 4;
		}
		else
		{
			for (unsigned int i = 0; i < neurons_.size(); ++i)
			{
				for (unsigned int j = 0; j < neurons_[i]->getSpikesTime().size(); ++j)
				{
					fileUno << neurons_[i] -> getSpikesTime()[j] << '\t' << i << '\n';
				}
			}
		}
	}
	catch (unsigned int i)
	{
		std::cout << "Couldn't manage to open the needed file." << std::endl;
	}
	fileUno.close();
}

void cortex::initiateNeuron(neuron* neuronToAdd)
{
	neurons_.push_back(neuronToAdd);
}
