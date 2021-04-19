#include "Motherboard.h"
#include <fstream>
#include <sstream>
#include "processor.h"
#include "memtrace.h"

std::string Motherboard::serializeObj() {
	std::ostringstream sStream;
	sStream << "\t" << this->Product::serializeObj();
	sStream << "\n\tMB_SPECIF\n\t{\n\t" << "chipset:" << chipset << ";socket:" << socketType << ";maxRam:" << maxRAM << ";maxFreq:" << maxRFreq
		<< ";usb:"<<usbPorts<<";sata:"<<sata<<";pcie:"<<pcie<<";\n\t}";
	return sStream.str();
}

std::ifstream& operator>>(std::ifstream& savefile, Motherboard& rhs) {
	if (!savefile.is_open())
	{
		savefile.open("savefile.txt");
	}
	savefile >> (Product&)rhs;
	std::string chipset;
	socket socketType;
	int maxRAM;
	int maxRFreq;
	int usbPorts;
	int sata;
	int pcie;
	std::string temp;
	std::getline(savefile, temp, '{');
	std::getline(savefile, chipset, ';');
	std::getline(savefile, temp, ':');
	savefile >> socketType;
	std::getline(savefile, temp, ':');
	savefile >> maxRAM;
	std::getline(savefile, temp, ':');
	savefile >> maxRFreq;
	std::getline(savefile, temp, ':');
	savefile >> usbPorts;
	std::getline(savefile, temp, ':');
	savefile >> sata;
	std::getline(savefile, temp, ':');
	savefile >> pcie;
	rhs = Motherboard(rhs.getName(),rhs.getPrice(),rhs.getManufacturer(),rhs.getDescription(),
		chipset, socketType, maxRAM,maxRFreq, usbPorts,sata,pcie);
	savefile.close();
	return savefile;
}
Motherboard::Motherboard(const Motherboard& m) :Product(m) {
	this->chipset = m.chipset;
	this->maxRAM = m.maxRAM;
	this->maxRFreq = m.maxRFreq;
	this->pcie = m.pcie;
	this->usbPorts = m.usbPorts;
	this->sata = m.sata;
	this->socketType = m.socketType;
	
}
Motherboard* Motherboard::clone() {
	Motherboard* m = new Motherboard(*this);
	return m;
}