#include <iostream>
#include "neuron.hpp"

//constructor
neuron::neuron(double mPot, double Iext, unsigned int spikesNb, int clock, double refractoryTime) //constructor
	: mPot_(mPot), Iext_(Iext), spikesNb_(spikesNb), clock_(clock), refractoryTime_(refractoryTime), ringBuffer_(10,0)
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

void neuron::setRefractoryTime(double const refractoryTime)
{
	refractoryTime_ = refractoryTime;
}

/*this function adds one in the ring buffer of our neuron when another 
 * neuron around spikes and transfers an additionnal potential J_ to our neuron*/
void neuron::setRingBuffer(int delaySteps)
{
	ringBuffer_[(clock_ + delaySteps) % ringBuffer_.size()] += 1;
}



bool neuron::update(unsigned int i)
{
	bool isItASpike (false); //bool variable, initialized to false if there is no spike, set to true if we have one
	
	//we check if there is a spike, and if yes, we memorize the hour in the vector spikesTime_
	if(mPot_ >= threshold_)
	{
		spikesNb_++;
		spikesTime_.push_back(i*h_); //(nit*h_) is the time when the spike occurs
		
		//std::cout << "if we're here the time is in the file" << std::endl;
		std::cout << "WE HAVE A PEAK (at " << (i*h_) << ")" << std::endl;
		
		refractorySteps_ = (2/h_); //2ms
		
		mPot_ = 0.0; //the neuron must get back to its original membrane potential after a spike
		
		isItASpike = true;
	}
	
	//we actualize V(t+h)
	if(refractorySteps_ <= 0)
	{
		/*we check if there is any spikes inside the ring buffer 
		 * waiting to be counted in the membrane potential of the neuron*/
		double Js = (ringBuffer_[i%ringBuffer_.size()]*J_);
		mPot_ = (EXP*mPot_ + Iext_*CONST + Js);
		
		std::cout << "j'actualise " << mPot_ << std::endl;
	}
	
	clock_ = i; 			//the neuron time is refreshed
	refractorySteps_ --; 	//refractorySteps_ is decremented
	ringBuffer_[i%ringBuffer_.size()] = 0; 		//we set the ring buffer back to 0
	
	return isItASpike;
} 
