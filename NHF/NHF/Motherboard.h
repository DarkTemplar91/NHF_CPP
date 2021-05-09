#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H

#include<iostream>
#include<string>
#include "products.h"
#include "processor.h"
#include "memtrace.h"

/// <summary>
/// enumerator for (a few) motherboard form factors
/// </summary>
enum class mbType { ATX, mATX, ITX };
class Motherboard :public Product {
	std::string chipset="";				///Type of chipset (B550, Z490 etc.)
	socket socketType=socket::AMD_AM4;	///Socket type of CPU
	int maxRAM=0;						///Max RAM capacity supported by MB
	int maxRFreq=0;						///Max frequecy of RAM supported
	int usbPorts=0;						///Number of USB ports
	int sata=0;							///Number of SATA connectors
	int pcie=0;							///Number of PCI-E slots
public:
	Motherboard() {}
	Motherboard(std::string chip, socket s, int maxRam = 64, int maxFreq = 2666, int usbPorts = 2, int sata = 1, int pcie = 1);
	Motherboard(std::string name, double price, std::string manuf, std::string descript,
		std::string chip, socket s, int maxRam = 64, int maxFreq = 2666, int usbPorts = 2, int sata = 1, int pcie = 1);
	Motherboard(const Motherboard& m);

	std::string getChip()const;  ///Returns type of chipset
	socket getSocket()const;	///Returns socket type
	int getRAM()const;			///Returns max RAM
	int getPorts()const;		///Returns number of USB ports
	int getSata()const;			///Returns number of SATA ports
	int getPCIE()const;			

	bool operator==(Motherboard& mb)const;
	bool operator!=(Motherboard& mb)const;
	std::string serializeObj()const;
	Motherboard* clone()const;
};

std::ifstream& operator>>(std::ifstream& savefile, Motherboard& rhs);


#endif // !MOTHERBOARD_H
