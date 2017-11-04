#include <iostream>
#include <fstream>
#include "neuron.hpp"
#include "cortex.hpp"

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
	
	unsigned int neuronsNumber;
	try
	{
		std::cout << "Choose number of neurons :";
		std::cin >> neuronsNumber;
		
		//we check if the number of neurons is possible
		if(neuronsNumber < 2) { throw 10; }
	}
	catch(unsigned int x) 
	{
		std::cout << "Number of neurons not correct. Error :" << x << std::endl;
	}
	
	cortex coco(neuronsNumber);
	
	//std::ofstream membranePotentials1("membranePotentials.txt");	//we create a file to store its membrane potentials values
		
	unsigned int nit_ = (unsigned int) ((b-a)/coco.getH()); 		//number of iterations (or steps) of the simulation (double cast into int)

	/*for(unsigned int i = 0; i < nit_; i++)
	{
		std::cout << "Iteration number " << i << std::endl;
		//std::cout << "Time is " << i*neuron1.getH() << std::endl;
		
		neuron1.update(i);
		membranePotentials1 << neuron1.getPot() << "\n"; 			//we store the membrane potential of this interval in a file
	}
	
	membranePotentials1.close();*/
	
	
	coco.updateAll(nit_);
	coco.timeOfTheSpikes();
	
	return 0;
} 
