#ifndef NEURON_H
#define NEURON_H

#include <vector>

class neuron {
	public :
	
	neuron(double mPot, unsigned int spikesNb = 0, double refractoryTime = 0.0); //constructor
	
	//getters
	double getPot() const;
	unsigned int getSpikesNb() const;
	std::vector<double> getSpikesTime() const;
	double getRefractoryTime() const;
	
	//setters
	void setPot(double mPot);
	void setSpikesNb(unsigned int spikesNb);
	//void setSpikesTime();
	void setRefractoryTime(double const refractoryTime);
	
	void update(double t, double exp, double constante, double Iext);
	bool isRefractory() const;
	
	private :
	
	double clock_;
	double refractoryTime_;
	double mPot_;
	unsigned int spikesNb_;
	std::vector<double> spikesTime_;
};

#endif 
