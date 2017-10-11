#include <iostream>
#include "neuron.hpp"


neuron::neuron(double mPot, double Iext, unsigned int spikesNb, int clock, double refractoryTime) //constructor
	: mPot_(mPot), Iext_(Iext), spikesNb_(spikesNb), clock_(clock), refractoryTime_(refractoryTime)
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

double neuron::getH() const
{
	return h_;
}

double neuron::getIext() const
{
	return Iext_;
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


void neuron::update(unsigned int i)
{
	//we check if there is a spike, and if yes, we memorize the hour in the vector spikesTime_
	if(mPot_ >= threshold_)
	{
		spikesNb_++;
		spikesTime_.push_back(i*h_); //(nit*h_) is the time when the spike occurs
		
		//std::cout << "if we're here the time is in the file" << std::endl;
		std::cout << "WE HAVE A PEAK (at " << (i*h_) << ")" << std::endl;
		
		refractorySteps_ = (2/h_); //2ms
		
		mPot_ = 0.0; //the neuron must get back to its original membrane potential after a spike
	}
	
	
	if(refractorySteps_ <= 0)
	{
		//we actualize V(t+h)
		mPot_ = (EXP*mPot_ + Iext_*CONST);
		std::cout << "j'actualise " << mPot_ << " voici Iext " << Iext_ << " et EXP " << EXP << " et CONST " << CONST << std::endl;
	}
	
	clock_ = i; //the neuron time is refreshed
	refractorySteps_ --; //refractorySteps_ is decremented
} 

/*bool neuron::isRefractory() const
{
	if(refractoryTime_ > 0.0000000000000000)
	{
		return true;
	}
	else
	{
		return false;
	}
}*/
