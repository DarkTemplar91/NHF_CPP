#ifndef VIDEOCARD_H
#define VIDEOCARD_H

#include <iostream>
#include <string>
#include "products.h"

class GPU : public Product {
	unsigned int portHDMI;
	unsigned int portDisplay;
	unsigned int gpuClock;
	unsigned int memoryClock;
	unsigned int vram;

	unsigned int tdp;
public:
	GPU(unsigned int portHDMI, unsigned int portDisplay,
		unsigned int gpuClock, unsigned int memoryClock, unsigned int vram, unsigned int tdp) : Product(),
		portHDMI(portHDMI),portDisplay(portDisplay),gpuClock(gpuClock),memoryClock(memoryClock),vram(vram),tdp(tdp) {}
	GPU(std::string name, double price, std::string manuf, std::string descript,unsigned int portHDMI, unsigned int portDisplay,
		unsigned int gpuClock, unsigned int memoryClock, unsigned int vram, unsigned int tdp) :
		Product(name,price,manuf, descript),
		portHDMI(portHDMI), portDisplay(portDisplay), gpuClock(gpuClock), memoryClock(memoryClock), vram(vram), tdp(tdp) {}
	GPU(const GPU& g):portHDMI(g.portHDMI),portDisplay(g.portDisplay),gpuClock(g.gpuClock),memoryClock(g.memoryClock),
	vram(g.vram),tdp(g.tdp){
		(Product)*this = Product(g);
	}

};

#endif // !VIDEOCARD_H
