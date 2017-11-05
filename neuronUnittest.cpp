#include <iostream>
#include <cmath>

#include "neuron.hpp"
#include "cortex.hpp"
#include "gtest/gtest.h"

TEST(oneNeuron, noSpike)		//we test if the neuron spike if we give it initially a current of 1.00 (normally it shouldn't)
{
	neuron nana(10.0, 1.0);
	unsigned int nit(1000/nana.getH());
	for (unsigned int i = 0; i < nit; ++i)
	{
		nana.update(i);
	}
	
	EXPECT_EQ(0, nana.getSpikesNb());
}

TEST(oneNeuron, mPotTwenty)		//we test if the membrane potential of the neuron stays around twenty if it has an initial current of 1.0
{
	neuron nana(0.0, 1.0);
	unsigned int nit(1000/nana.getH());
	for (unsigned int i = 0; i < nit; ++i)
	{
		nana.update(i);
	}
	
	ASSERT_FLOAT_EQ(20, nana.getPot());
}

TEST(oneNeuron, negativePot)	//we test if the membrane potential of the neuron stays around minus twenty if it has an initial current of minus 1.0
{
	neuron nana(0.0, -1.0);
	unsigned int nit(1000/nana.getH());
	for (unsigned int i = 0; i < nit; ++i)
	{
		nana.update(i);
	}
	
	ASSERT_FLOAT_EQ(-20, nana.getPot());
}

TEST(oneNeuron, zeroExternalCurrent)
{
	neuron nana(0.0, 0.0);
	unsigned int nit(1000/nana.getH());
	for (unsigned int i = 0; i < nit; ++i)
	{
		nana.update(i);
	}
	
	ASSERT_FLOAT_EQ(0, nana.getPot());
}

TEST(oneNeuron, doesItSpike)
{
	neuron nana(0.0, 1.01);
	unsigned int nit(100/nana.getH());
	for (unsigned int i = 0; i < nit; ++i)
	{
		nana.update(i);
	}
	
	EXPECT_EQ(1, nana.getSpikesNb());
}

TEST(twoNeurons, bufferTest)
{
	neuron nana;
	neuron nono;
	
}
