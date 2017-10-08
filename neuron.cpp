#include <iostream>
#include "neuron.hpp"

//constant declaration
const double threshold(20.0);



neuron::neuron(double mPot, unsigned int spikesNb) //constructor
	: mPot_(mPot), spikesNb_(spikesNb)
{}
	
//getters
double neuron::getPot()
{
	return mPot_;
}

unsigned int neuron::getSpikesNb()
{
	return spikesNb_;
}

std::vector<double> neuron::getSpikesTime()
{
	return spikesTime_;
}


//setters
void neuron::setPot(double mPot)
{
	mPot_ = mPot;
}

void neuron::setSpikesNb(unsigned int spikesNb)
{
	spikesNb_ = spikesNb;
}

/*void neuron::getSpikesTime()
{}*/


//we suppose that we can only have one spike per interval, and we consider the input current to be constant inside a loop
void neuron::update(double t, double exp, double constante, double Iext)
{
	//we check if there was a spike, and if yes, we memorize the hour in the vector spikesTime_
	if(mPot_ >= threshold)
	{
		spikesNb_++;
		spikesTime_.push_back(t);
		
		//std::cout << "if we're here the time is in the file" << std::endl;
		std::cout << "WE HAVE A PEAK" << std::endl;
		
		mPot_ = 0.0; //the neuron must get back to its original membrane potential after a spike
	}
	else
	{
		//we actualize V(t+h)
		mPot_ = (exp*mPot_ + Iext*constante);
		//std::cout << mPot_ << std::endl;
	}	
}
