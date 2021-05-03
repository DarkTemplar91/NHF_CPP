#ifndef VIDEOCARD_H
#define VIDEOCARD_H

#include <iostream>
#include <string>
#include "products.h"
#include "memtrace.h"

class GPU : public Product {
	unsigned int portHDMI;
	unsigned int portDisplay;
	unsigned int gpuClock;
	unsigned int memoryClock;
	unsigned int vram;
	unsigned int tdp;
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
