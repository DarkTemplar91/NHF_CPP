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
enum mbType { ATX, mATX, ITX };
class Motherboard :public Product {
	std::string chipset;	///Type of chipset (B550, Z490 etc.)
	socket socketType;		///Socket type of CPU
	int maxRAM;				///Max RAM capacity supported by MB
	int maxRFreq;			///Max frequecy of RAM supported
	int usbPorts;			///Number of USB ports
	int sata;				///Number of SATA connectors
	int pcie;				///Number of PCI-E slots
public:
	Motherboard() {}
	Motherboard(std::string chip, socket s, int maxRam = 64, int maxFreq = 2666, int usbPorts = 2, int sata = 1, int pcie = 1);
	Motherboard(std::string name, double price, std::string manuf, std::string descript,
		std::string chip, socket s, int maxRam = 64, int maxFreq = 2666, int usbPorts = 2, int sata = 1, int pcie = 1);
	Motherboard(const Motherboard& m);

	std::string getChip();  ///Returns type of chipset
	socket getSocket();		///Returns socket type
	int getRAM();			///Returns max RAM
	int getPorts();			///Returns number of USB ports
	int getSata();			///Returns number of SATA ports
	int getPCIE();			

	
	std::string serializeObj()const;
	Motherboard* clone();
};

std::ifstream& operator>>(std::ifstream& savefile, Motherboard& rhs);


#endif // !MOTHERBOARD_H
