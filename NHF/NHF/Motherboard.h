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
	Motherboard(std::string chip, socket s, int maxRam = 64, int maxFreq = 2666, int usbPorts = 2, int sata = 1, int pcie = 1) :Product(),
		chipset(chip), socketType(s), maxRAM(maxRam), maxRFreq(maxFreq), usbPorts(usbPorts), sata(sata), pcie(pcie) {}
	Motherboard(std::string name, double price, std::string manuf, std::string descript,
		std::string chip, socket s, int maxRam = 64, int maxFreq = 2666, int usbPorts = 2, int sata = 1, int pcie = 1)
		:Product(name, price, manuf, descript),
		chipset(chip), socketType(s), maxRAM(maxRam), maxRFreq(maxFreq), usbPorts(usbPorts), sata(sata), pcie(pcie) {}
	Motherboard(const Motherboard& m);
	std::string getChip() { return chipset; }
	socket getSocket() { return socketType; }
	int getRAM() { return maxRAM; }
	int getPorts() { return usbPorts; }
	int getSata() { return sata; }
	int getPCIE() { return pcie; }
	std::string getObjType() {
		return "MB_OBJ";
	}
	std::string serializeObj();
	Motherboard* clone();
};

std::ifstream& operator>>(std::ifstream& savefile, Motherboard& rhs);


#endif // !MOTHERBOARD_H
