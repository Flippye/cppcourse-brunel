#include <iostream>
#include <fstream>
#include "neuron.hpp"

int main () {
	
	//we first ask the user to type a time interval, represented by doubles
	double a, b;
	try
	{
		std::cout << "Choose an interval [ms] :";
		std::cin >> a >> b;
		
		//we check if the interval is correct with a try-catch block
		if(a>=b or a<0 or b<0) { throw 42; }
	}
	catch(int x) 
	{
		std::cout << "Interval not correct. Error :" << x << std::endl;
	}

	neuron neuron1(10); //we instantiate a neuron test
	std::ofstream membranePotentials1("membranePotentials.txt"); //we create a file to store its membrane potentials values
	
	std::cout << "Iext: " << neuron1.getIext() << " mPot " << neuron1.getPot() << " refractory time : " << neuron1.getRefractoryTime() << std::endl;
	
	//we test its values
	//std::cout << "Potential of neuron1 is : " << neuron1.getPot() << " and actual nb of spikes is : " << neuron1.getSpikesNb() << std::endl;
			
	unsigned int nit_ = ((b-a)/neuron1.getH()); //number of iterations (or steps) of the simulation

	for(unsigned int i = 0; i < nit_; i++)
	{
		std::cout << "Iteration number " << i << std::endl;
		//std::cout << "Time is " << i*neuron1.getH() << std::endl;
		
		neuron1.update(i);
		membranePotentials1 << neuron1.getPot() << "\n"; //we store the membrane potential of this interval in a file
	}
	
	membranePotentials1.close();
	
	return 0;
} 
