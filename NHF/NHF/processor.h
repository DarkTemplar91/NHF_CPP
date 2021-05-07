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
	std::string genName;		///Name of the cpu generation
	int tdp;					///Total drawn power
	socket socketType;			///Enum for socket type
	unsigned int baseClock;		///Base clock frequency given in Mhz
	unsigned int coreCount;		///Number of cores
	unsigned int threadCount;	///Number of threads
	double L2_cache;			///size of cache in MB
	bool iVGA = false;			///Included igpu
public:
	CPU() {}
	CPU(std::string name, int tdp, socket type, unsigned int clock, unsigned int core, unsigned int thread, double c, bool vga);
	CPU(std::string pName, double price, std::string manuf, std::string descript, std::string name, int tdp,
		socket type, unsigned int clock, unsigned int core, unsigned int thread, double c, bool vga);
	CPU(const CPU& c);

	std::string getGenName();
	int getTDP();
	socket getSocketType();
	std::string getStringSocket();
	unsigned int getBaseClock();
	unsigned int getCoreCount();
	unsigned int getThreadCount();
	double getCacheSize();
	bool ivga();
	
	CPU* clone();
	std::string getObjType();
	void print();
	std::string serializeObj();
	

};
std::ifstream& operator>>(std::ifstream& is, socket& s);  ///overloaded enum for socket
std::ifstream& operator>>(std::ifstream& savefile, CPU& rhs);
#endif
