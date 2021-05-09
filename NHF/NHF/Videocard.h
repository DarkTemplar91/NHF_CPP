#ifndef VIDEOCARD_H
#define VIDEOCARD_H

#include <iostream>
#include <string>
#include "products.h"
#include "memtrace.h"


/// <summary>
/// Class for representing GPU
/// </summary>
class GPU : public Product {
	unsigned int portHDMI=0;		///Number of HDMI ports on GPU
	unsigned int portDisplay=0;		///Number of Display ports on GPU
	unsigned int gpuClock=0;		///GPU Clock in Mhz
	unsigned int memoryClock=0;		///Memory Clock in Mhz
	unsigned int vram=0;			///VRAM in GB
	unsigned int tdp=0;				///total power drawn
public:
	GPU() {}
	GPU(unsigned int portHDMI, unsigned int portDisplay,
		unsigned int gpuClock, unsigned int memoryClock, unsigned int vram, unsigned int tdp);
	GPU(std::string name, double price, std::string manuf, std::string descript, unsigned int portHDMI, unsigned int portDisplay,
		unsigned int gpuClock, unsigned int memoryClock, unsigned int vram, unsigned int tdp);
	GPU(const GPU& g);

	unsigned int getHDMIports()const;
	unsigned int getDisplayports()const;
	unsigned int getGPUclock()const;
	unsigned int getMemClock()const;
	unsigned int getVRAM()const;
	unsigned int getTDP()const;

	bool operator==(GPU& rhs)const;
	bool operator!=(GPU& rhs)const;
	std::string serializeObj()const;
	GPU* clone()const;

};
std::ifstream& operator>>(std::ifstream& savefile, GPU& rhs);

#endif // !VIDEOCARD_H
