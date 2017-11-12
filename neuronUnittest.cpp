#include <iostream>
#include <cmath>

#include "neuron.hpp"
#include "cortex.hpp"
#include "gtest/gtest.h"

//we test if the neuron spike if we give it initially a current of 1.00 (normally it shouldn't)
TEST(oneNeuron, noSpike)		
{
	neuron nana(0.0, 1.0);
	unsigned int nit(1000/nana.getH());
	for (unsigned int i = 0; i < nit; ++i)
	{
		nana.update(i);
	}
	
	EXPECT_EQ(0, nana.getSpikesNb());
}

//we test if the membrane potential of the neuron stays around twenty if it has an initial current of 1.0
TEST(oneNeuron, mPotTwenty)		
{
	neuron nana(0.0, 1.0);
	unsigned int nit(1000/nana.getH());
	for (unsigned int i = 0; i < nit; ++i)
	{
		nana.update(i);
	}
	
	ASSERT_FLOAT_EQ(20, nana.getPot());
}

//we test if the membrane potential of the neuron stays around minus twenty if it has an initial current of minus 1.0
TEST(oneNeuron, negativePot)	
{
	neuron nana(0.0, -1.0);
	unsigned int nit(1000/nana.getH());
	for (unsigned int i = 0; i < nit; ++i)
	{
		nana.update(i);
	}
	
	ASSERT_FLOAT_EQ(-20, nana.getPot());
}

//the membrane potential of our neuron should stay equal to 0 if we don't initially give it an external current
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

//our neuron should spike with a current of 1.01 at 92.4ms, then at 186.8ms, then at 281.2ms
TEST(oneNeuron, doesItSpike)	
{
	neuron nana(0.0, 1.01);
	unsigned int nit(300/nana.getH());
	for (unsigned int i = 0; i < nit; ++i)
	{
		nana.update(i);
	}
	
	EXPECT_EQ(3, nana.getSpikesNb());
	EXPECT_EQ(92.4, nana.getSpikesTime()[0]);
	EXPECT_EQ(186.8, nana.getSpikesTime()[1]);
	EXPECT_EQ(281.2, nana.getSpikesTime()[2]);
}

TEST(twoNeurons, spikeTestForFirstConstructor)
{
	cortex coco(1);
	coco.getNeuron(0)->setIext(1.01);
	
	unsigned int nit(300/coco.getH());
	
	for (unsigned int i = 0; i < nit; ++i)
	{
		coco.getNeuron(0)->update(i);
	}
	
	EXPECT_EQ(92.4, coco.getNeuron(0)->getSpikesTime()[0]);
	EXPECT_EQ(186.8, coco.getNeuron(0)->getSpikesTime()[1]);
	EXPECT_EQ(281.2, coco.getNeuron(0)->getSpikesTime()[2]);
}
