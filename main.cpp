#include <iostream>
#include <fstream>
#include <cmath>
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
	
	//we set h, the interval incrementer
	double h = 0.1;
	
	//we set the constants
	const double tau(20.0);
	const double capacity(1.00);
	const double R(tau/capacity); //because tau = R*capacity
	double EXP(exp(-h/tau));
	double CONST((R/tau) * (1-EXP));
	
	neuron neuron1(20); //we instantiate a neuron test
	std::ofstream membranePotentials1("membranePotentials.txt"); //we create a file to store its membrane potentials values
	
	//we test its values
	//std::cout << "Potential of neuron1 is : " << neuron1.neuron::getPot() << " and actual nb of spikes is : " << neuron1.neuron::getSpikesNb() << std::endl;
	
	unsigned int n = 0; //to keep track of the iteration for testing purpose
	
	//we ask the user what will be the input current for this loop
	double Iext;
	std::cout << "Type the input current :";
	std::cin >> Iext;
	std::cout << "thanks" << std::endl;
	
	//this while loop will increment the time interval, and update the neuron at each iteration
	while(a<=b) 
	{
		std::cout << "Iteration number " << n << std::endl;
		//std::cout << "Time is " << a << std::endl;
		
		neuron1.update(a, EXP, CONST, Iext);
		neuron1.setRefractoryTime(neuron1.getRefractoryTime() - h);
		
		//we store the membrane potential of this interval in a file
		membranePotentials1 << neuron1.getPot() << "\n";
				
		//we increase the iteration variable and the time interval
		a += h;
		++n;
	}
	
	membranePotentials1.close();
	
	return 0;
} 
