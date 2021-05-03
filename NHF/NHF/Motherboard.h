#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H

#include<iostream>
#include<string>
#include "products.h"
#include "processor.h"
#include "memtrace.h"

enum mbType { ATX, mATX, ITX };
class Motherboard :public Product {
	std::string chipset;
	socket socketType;
	int maxRAM;
	int maxRFreq;
	int usbPorts;
	int sata;
	int pcie;
public:
	Motherboard() {}
	Motherboard(std::string chip, socket s, int maxRam = 64, int maxFreq = 2666, int usbPorts = 2, int sata = 1, int pcie = 1);
	Motherboard(std::string name, double price, std::string manuf, std::string descript,
		std::string chip, socket s, int maxRam = 64, int maxFreq = 2666, int usbPorts = 2, int sata = 1, int pcie = 1);
	Motherboard(const Motherboard& m);
	std::string getChip();
	socket getSocket();
	int getRAM();
	int getPorts();
	int getSata();
	int getPCIE();
	std::string getObjType();
	std::string serializeObj();
	Motherboard* clone();
};

std::ifstream& operator>>(std::ifstream& savefile, Motherboard& rhs);


#endif // !MOTHERBOARD_H
