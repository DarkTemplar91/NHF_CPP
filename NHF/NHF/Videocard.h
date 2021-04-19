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
		unsigned int gpuClock, unsigned int memoryClock, unsigned int vram, unsigned int tdp) : Product(),
		portHDMI(portHDMI),portDisplay(portDisplay),gpuClock(gpuClock),memoryClock(memoryClock),vram(vram),tdp(tdp) {}
	GPU(std::string name, double price, std::string manuf, std::string descript,unsigned int portHDMI, unsigned int portDisplay,
		unsigned int gpuClock, unsigned int memoryClock, unsigned int vram, unsigned int tdp) :
		Product(name,price,manuf, descript),
		portHDMI(portHDMI), portDisplay(portDisplay), gpuClock(gpuClock), memoryClock(memoryClock), vram(vram), tdp(tdp) {}
	GPU(const GPU& g);

	unsigned int getHDMIports() { return portHDMI; }
	unsigned int getDisplayports() { return portDisplay; }
	unsigned int getGPUclock() { return gpuClock; }
	unsigned int getMemClock() { return memoryClock; }
	unsigned int getVRAM() { return vram; }
	unsigned int getTDP() { return tdp; }


	std::string getObjType() {
		return "GPU_OBJ";
	}
	std::string serializeObj();
	GPU* clone();

};
std::ifstream& operator>>(std::ifstream& savefile, GPU& rhs);

#endif // !VIDEOCARD_H
