#include <iostream>
#include <fstream>
#include "neuron.hpp"
#include "cortex.hpp"

int main () {
	//we first ask the user to type a time interval, represented by doubles
	double a, b;
	try
	{
		std::cout << "Choose an interval [ms], from: ";
		std::cin >> a;
		std::cout << " to: ";
		std::cin >> b;
		if(a>=b or a<0 or b<0) { throw 42; }	//we check if the interval is correct with a try-catch block
	}
	catch(int x) 
	{
		std::cout << "Interval not correct. Error :" << x << std::endl;
	}
	
	unsigned int neuronsNumber;
	try
	{
		std::cout << "Choose number of neurons :";
		std::cin >> neuronsNumber;
		
		if(neuronsNumber < 2) { throw 10; }		//we check if the number of neurons is possible
	}
	catch(unsigned int x) 
	{
		std::cout << "Number of neurons not correct. Error :" << x << std::endl;
	}
	
	//cortex coco(neuronsNumber);
	cortex coco(1000, 250);		//we create the cortex holding all our neurons together
			
	unsigned int nit_ = (unsigned int) ((b-a)/coco.getH());		//number of iterations (or steps) of the simulation (double cast into int)
	
	coco.updateAll(nit_);		//we update our cortex on all our simulation time
	coco.timeOfTheSpikes();		//we create the file storing the spikes time
	
	return 0;
} 
