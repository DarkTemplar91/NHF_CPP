#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "products.h"
#include <string>
#include <iostream>
#include "memtrace.h"

/// This is an enum class for the socket types
/// Only for current desktop CPUs
enum socket{AMD_AM4,INTEL_1151,INTEL_1151V2,INTEL_1200};

class CPU : public Product {
	std::string genName;
	int tdp;
	socket socketType; ///Enum for socket type
	unsigned int baseClock; ///Base clock frequency given in Mhz
	unsigned int coreCount; ///Number of cores
	unsigned int threadCount; ///Number of threads
	double L2_cache; ///size of cache in MB
	bool iVGA = false;
public:
	CPU() {}
	CPU(std::string name, int tdp, socket type, unsigned int clock, unsigned int core, unsigned int thread,double c,bool vga) :Product(), genName(name), tdp(tdp),
		socketType(type), baseClock(clock), coreCount(core), threadCount(thread),L2_cache(c),iVGA(vga) {}
	CPU(std::string pName, double price,std::string manuf, std::string descript , std::string name, int tdp,
		socket type, unsigned int clock, unsigned int core, unsigned int thread,double c,bool vga)
		:Product(pName,price,manuf,descript), 
		genName(name), tdp(tdp),
		socketType(type), baseClock(clock), coreCount(core), threadCount(thread),L2_cache(c),iVGA(vga) {}
	CPU(const CPU& c);

	std::string getGenName() { return genName; }
	int getTDP() { return tdp; }
	socket getSocketType() { return socketType; }
	std::string getStringSocket();
	unsigned int getBaseClock() { return baseClock; }
	unsigned int getCoreCount() { return coreCount; }
	unsigned int getThreadCount() { return threadCount; }
	double getCacheSize() { return L2_cache; }
	bool ivga() { return iVGA; }
	
	CPU* clone();
	std::string getObjType();
	void print();
	std::string serializeObj();
	

};
std::ifstream& operator>>(std::ifstream& is, socket& s);
std::ifstream& operator>>(std::ifstream& savefile, CPU& rhs);
#endif
