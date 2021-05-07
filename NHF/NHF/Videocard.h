#ifndef VIDEOCARD_H
#define VIDEOCARD_H

#include <iostream>
#include <string>
#include "products.h"
#include "memtrace.h"

class GPU : public Product {
	unsigned int portHDMI;			///Number of HDMI ports on GPU
	unsigned int portDisplay;		///Number of Display ports on GPU
	unsigned int gpuClock;			///GPU Clock in Mhz
	unsigned int memoryClock;		///Memory Clock in Mhz
	unsigned int vram;				///VRAM in GB
	unsigned int tdp;				///total power drawn
public:
	GPU() {}
	GPU(unsigned int portHDMI, unsigned int portDisplay,
		unsigned int gpuClock, unsigned int memoryClock, unsigned int vram, unsigned int tdp);
	GPU(std::string name, double price, std::string manuf, std::string descript, unsigned int portHDMI, unsigned int portDisplay,
		unsigned int gpuClock, unsigned int memoryClock, unsigned int vram, unsigned int tdp);
	GPU(const GPU& g);

	unsigned int getHDMIports();
	unsigned int getDisplayports();
	unsigned int getGPUclock();
	unsigned int getMemClock();
	unsigned int getVRAM();
	unsigned int getTDP();

	std::string getObjType();
	std::string serializeObj();
	GPU* clone();

};
std::ifstream& operator>>(std::ifstream& savefile, GPU& rhs);

#endif // !VIDEOCARD_H
