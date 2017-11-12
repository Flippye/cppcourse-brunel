#include <iostream>

#include "experiment.hpp"

experiment::experiment()
{}

experiment::~experiment()
{}

void experiment::setSimulation(double g, double mu, double time, std::ofstream& fileUno)
{
	unsigned int noExcitatory = 10000;
	unsigned int noInhibitory = 2500;
	
	for (unsigned int i = 0; i < noExcitatory ; ++i)
	{
		coco_.initiateNeuron(new neuron(0.0, 1.01, true, true, g, mu));
	}
	for (unsigned int i = 0; i < noInhibitory ; ++i)
	{
		coco_.initiateNeuron(new neuron(0.0, 1.01, false, true, g, mu));
	}
	
	coco_.createRandomConnexionMatrix(noExcitatory, noInhibitory, true);
	
	unsigned int nit (time/coco_.getH());
	coco_.updateAll(nit);
	
	coco_.storeInFile(fileUno);
}
