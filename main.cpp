#include <iostream>
#include <fstream>
#include "neuron.hpp"
#include "cortex.hpp"
#include "experiment.hpp"

int main () {
	
	//first we ask the utilisator if she wants to draw a plot (PART 1) or to just run the simulation (PART 2)
	char alpha('a');
	do
	{
		try
		{
			std::cout << "Press 'p' to make the plots or 's' to launch your own simulation:" << std::endl;
			std::cin >> alpha;
			if (alpha!='p' and alpha!='s')
			{
				throw('h');
			}
		}
		catch (char h)
		{
			std::cout << "Please only enter 'p' or 's' to make plots or a simulation." << std::endl;
		}
	} while (alpha!='p' and alpha!='s');
	
	
	//PART 1: we set the files correctly to be able to draw the plots
	if (alpha == 'p')
	{
		unsigned int plot(0);
		
		//we check if the given number is correct (within our chosen range)
		do
		{
			try
			{
				std::cout << "Choose the plot you want to creat : '1', '2', '3' or '4' : " << std::endl;
				std::cin >> plot;
				if (plot!=1 and plot!=2 and plot!=3 and plot !=4)
				{
					throw 0;
				}
			}
			catch (unsigned int i)
			{
				std::cout << "Please enter only '1', '2', '3' or '4' to choose the wanted plot: " << std::endl;
			}
		} while (plot!=1 and plot!=2 and plot!=3 and plot !=4);
		
		//Simulation leading to plot 1
		if (plot == 1)
		{
			std::cout << "PLOT 1: " << std::endl;
			experiment plotUno;
			std::ofstream fileUno("fileUno.csv");
			
			if (fileUno.fail())
			{
				std::cout << "Impossible to open the file for plot 1." << std::endl;
			}
			else
			{
				plotUno.setSimulation(3, 2, 600, fileUno);
			}
			fileUno.close();
		}
		
		//Simulation leading to plot 2
		if (plot == 2)
		{
			std::cout << "PLOT 2: " << std::endl;
			experiment plotDuo;
			std::ofstream fileDuo("fileDuo.csv");
			if (fileDuo.fail())
			{
				std::cout << "Impossible to open the file for plot 2." << std::endl;
			}
			else
			{
				plotDuo.setSimulation(6, 4, 1200, fileDuo);
			}
			fileDuo.close();
		}		
			
		//Simulation leading to plot 3
		if (plot == 3)
		{
			std::cout << "PLOT 3: " << std::endl;
			experiment plotTryo;
			std::ofstream fileTryo("fileTryo.csv");
			if (fileTryo.fail())
			{
				std::cout << "Impossible to open the file for plot 3." << std::endl;
			}
			else
			{
				plotTryo.setSimulation(5, 2, 1200, fileTryo);
			}
			fileTryo.close();
		}
		
		//Simulation leading to plot 4	
		if (plot == 4)
		{
			std::cout << "PLOT 4: " << std::endl;
			experiment plotFour;
			std::ofstream fileFour("fileFour.csv");
			if (fileFour.fail())
			{
				std::cout << "Impossible to open the file for plot 4." << std::endl;
			}
			else
			{
				plotFour.setSimulation(4.5, 0.9, 1200, fileFour);
			}
			fileFour.close();
		}
	}
	//PART 2: simulation run
	else if (alpha == 's')
	{	
		double a, b;
		
		//We check if the given time interval is correct
		do
		{
			try
			{
				std::cout << "Choose an interval [ms], from: ";
				std::cin >> a;
				std::cout << " to: ";
				std::cin >> b;
				if(a>=b or a<0 or b<0) { throw 42; }
			}
			catch(int x) 
			{
				std::cout << "Please enter a correct interval : " << std::endl;
			}
		} while (a>=b or a<0 or b<0);
		
		cortex coco(10000, 2500);	//we create the cortex holding all our neurons together
			
		unsigned int nit_ = (unsigned int) ((b-a)/coco.getH());		//number of iterations (or steps) of the simulation (double cast into int)
	
		coco.updateAll(nit_);		//we update our cortex on all our simulation time
		coco.timeOfTheSpikes();		//we create the file storing the spikes time
	}
	
	return 0;
} 
