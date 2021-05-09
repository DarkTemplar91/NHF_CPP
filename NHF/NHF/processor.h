#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "products.h"
#include <string>
#include <iostream>
#include "memtrace.h"

/// This is an enum class for the socket types
/// Only for current desktop CPUs
enum class socket{AMD_AM4,INTEL_1151,INTEL_1151V2,INTEL_1200};

class CPU : public Product {
	std::string genName="";					///Name of the cpu generation
	int tdp=0;								///Total drawn power
	socket socketType=socket::AMD_AM4;		///Enum for socket type
	unsigned int baseClock=0;				///Base clock frequency given in Mhz
	unsigned int coreCount=0;				///Number of cores
	unsigned int threadCount=0;				///Number of threads
	double L2_cache=0;						///size of cache in MB
	bool iVGA = false;						///Included igpu
public:
	CPU() {}
	CPU(std::string name, int tdp, socket type, unsigned int clock, unsigned int core, unsigned int thread, double c, bool vga);
	CPU(std::string pName, double price, std::string manuf, std::string descript, std::string name, int tdp,
		socket type, unsigned int clock, unsigned int core, unsigned int thread, double c, bool vga);
	CPU(const CPU& c);

	std::string getGenName()const;
	int getTDP()const;
	socket getSocketType()const;
	std::string getStringSocket()const;
	unsigned int getBaseClock()const;
	unsigned int getCoreCount()const;
	unsigned int getThreadCount()const;
	double getCacheSize()const;
	bool ivga()const;
	
	CPU* clone()const;
	void print()const;
	std::string serializeObj()const;
	bool operator==(CPU& rhs)const;
	bool operator!=(CPU& rhs)const;
	

};
std::ifstream& operator>>(std::ifstream& is, socket& s);  ///overloaded enum for socket
std::ifstream& operator>>(std::ifstream& savefile, CPU& rhs);
std::ostream& operator<<(std::ostream& os, const socket& s);
#endif
