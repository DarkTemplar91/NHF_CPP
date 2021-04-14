#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "products.h"
#include <string>
#include <iostream>

/// This is an enum class for the socket types
/// Only for current desktop CPUs
enum socket{AMD_AM4,INTEL_1151,INTEL_1151V2,INTEL_1200};

class CPU : public Product {
	std::string genName;
	int tdp;
	socket socketType; ///Enum for socket type
	unsigned int baseClock; ///Base clock frequency given in GHz
	unsigned int coreCount; ///Number of cores
	unsigned int threadCount; ///Number of threads
	double L2_cache; ///size of cache in MB
	bool iVGA = false;
public:
	CPU(std::string name, int tdp, socket type, unsigned int clock, unsigned int core, unsigned int thread,double c,bool vga) :Product(), genName(name), tdp(tdp),
		socketType(type), baseClock(clock), coreCount(core), threadCount(thread),L2_cache(c),iVGA(vga) {}
	CPU(std::string pName, double price,std::string manuf, std::string descript , std::string name, int tdp,
		socket type, unsigned int clock, unsigned int core, unsigned int thread,double c,bool vga)
		:Product(pName,price,manuf,descript), 
		genName(name), tdp(tdp),
		socketType(type), baseClock(clock), coreCount(core), threadCount(thread),L2_cache(c),iVGA(vga) {}
	CPU(const CPU& c): genName(c.genName), tdp(c.tdp), socketType(c.socketType),baseClock(c.baseClock),
		coreCount(c.coreCount),L2_cache(c.L2_cache),iVGA(c.iVGA),
	threadCount(c.threadCount){
		(Product)*this = Product(c);
	}

	std::string getGenName() { return genName; }
	int getTDP() { return tdp; }
	socket getSocketType() { return socketType; }
	unsigned int getBaseClock() { return baseClock; }
	unsigned int getCoreCount() { return coreCount; }
	unsigned int getThreadCount() { return threadCount; }
	double getCacheSize() { return L2_cache; }
	bool ivga() { return iVGA; }

};

#endif
