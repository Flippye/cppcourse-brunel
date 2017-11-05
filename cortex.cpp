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
	}
	
	for (unsigned int i = nbNeuronsE; i < (nbNeuronsE + nbNeuronsI); ++i)
	{
		neurons_.push_back(new neuron);
		neurons_[i]->setExcitatory(false);
	}
	
	connexionMatrix_.resize((nbNeuronsE + nbNeuronsI), std::vector<int> (nbNeuronsE + nbNeuronsI));
	
	createRandomConnexionMatrix(nbNeuronsE, nbNeuronsI);
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

void cortex::increaseNeuronNumber()
{
	neuronNb_ ++;
}

void cortex::pushbackToNeurons_(neuron* const neuronToAdd)
{
	neurons_.push_back(neuronToAdd);
}

void cortex::receiveSpike(neuron receiver, bool whichSign)
{
	receiver.setRingBuffer(delaySteps_, whichSign);
}

void cortex::addAConnexion(unsigned int row, unsigned int column)
{
	connexionMatrix_[row][column] += 1;
}

void cortex::createRandomConnexionMatrix(unsigned int nbNeuronsE, unsigned int nbNeuronsI)
{
	std::random_device randomD;
	std::mt19937 gen(randomD());
	std::uniform_int_distribution<> excitatoryDistribution(0, nbNeuronsE - 1);
	std::uniform_int_distribution<> inhibitoryDistribution(nbNeuronsE, nbNeuronsE + nbNeuronsI - 1);
	
	for (unsigned int i = 0; i < neurons_.size(); ++i)
	{
		for (unsigned int j = 0; j < nbNeuronsE/10; ++j)
		{
			addAConnexion(excitatoryDistribution(gen),i);
		}
		for (unsigned int k = 0; k < nbNeuronsI/10; ++k)
		{
			addAConnexion(inhibitoryDistribution(gen),i);
		}
	}
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
				
				/*if the neuron has spiked, we send its membrane potential (different depending on if 
				 * it's an excitatory or inhibitory neuron) to all the neurons it is connected with */
				if(isItASpike) 
				{
					bool whatStateIsMyNeuronSpikingIn(neurons_[j]->getExcitatoryState()); //long variable name but at least it's comprehensible
					
					for (unsigned int k = 0; k < connexionMatrix_[j].size(); ++k)
					{
						//we send as many spikes as the weigh of the connexion
						for (int l = 1; l < connexionMatrix_[j][k]; ++l)
						{
							receiveSpike(*neurons_[k], whatStateIsMyNeuronSpikingIn);
						}
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
