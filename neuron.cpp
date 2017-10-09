#include <iostream>
#include "neuron.hpp"

//constant declaration
const double threshold(20.0);


neuron::neuron(double mPot, unsigned int spikesNb, double refractoryTime) //constructor
	: mPot_(mPot), spikesNb_(spikesNb)
{}
	
//getters
double neuron::getPot() const
{
	return mPot_;
}

unsigned int neuron::getSpikesNb() const
{
	return spikesNb_;
}

std::vector<double> neuron::getSpikesTime() const
{
	return spikesTime_;
}

double neuron::getRefractoryTime() const
{
	return refractoryTime_;
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

void neuron::setRefractoryTime(double const refractoryTime)
{
	refractoryTime_ = refractoryTime;
}


void neuron::update(double t, double exp, double constante, double Iext)
{
	//we check if there is a spike, and if yes, we memorize the hour in the vector spikesTime_
	if(mPot_ >= threshold)
	{
		spikesNb_++;
		spikesTime_.push_back(t);
		
		//std::cout << "if we're here the time is in the file" << std::endl;
		std::cout << "WE HAVE A PEAK (at " << t << ")" << std::endl;
		
		refractoryTime_ = 2.0; //2ms
	}
	
	
	if(isRefractory())
	{
		mPot_ = 0.0; //the neuron must get back to its original membrane potential after a spike
	}
	else
	{
		//we actualize V(t+h)
		mPot_ = (exp*mPot_ + Iext*constante);
		//std::cout << mPot_ << std::endl;
	}
	
	//time incrementation
	clock_ += t;
} 

bool neuron::isRefractory() const
{
	if(refractoryTime_ > 0.0000000000000000)
	{
		return true;
	}
	else
	{
		return false;
	}
}
