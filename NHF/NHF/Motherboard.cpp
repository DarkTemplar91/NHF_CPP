#include "Motherboard.h"
#include <fstream>
#include <sstream>
#include "processor.h"
#include "memtrace.h"


Motherboard::Motherboard(std::string chip, socket s, int maxRam, int maxFreq, int usbPorts, int sata, int pcie) :Product(),
chipset(chip), socketType(s), maxRAM(maxRam), maxRFreq(maxFreq), usbPorts(usbPorts), sata(sata), pcie(pcie) {
	t = obj_t::MB;
}
Motherboard::Motherboard(std::string name, double price, std::string manuf, std::string descript,
	std::string chip, socket s, int maxRam, int maxFreq, int usbPorts, int sata, int pcie)
	:Product(name, price, manuf, descript),
	chipset(chip), socketType(s), maxRAM(maxRam), maxRFreq(maxFreq), usbPorts(usbPorts), sata(sata), pcie(pcie) {
	t = obj_t::MB;
}
Motherboard::Motherboard(const Motherboard& m):Product(m), chipset(m.chipset),socketType(m.socketType), maxRAM(m.maxRAM),
maxRFreq(m.maxRFreq), usbPorts(m.usbPorts), sata(m.sata), pcie(m.pcie) {
	t = obj_t::MB;
}


std::string Motherboard::getChip() { return chipset; }
socket Motherboard::getSocket() { return socketType; }
int Motherboard::getRAM() { return maxRAM; }
int Motherboard::getPorts() { return usbPorts; }
int Motherboard::getSata() { return sata; }
int Motherboard::getPCIE() { return pcie; }
std::string Motherboard::getObjType() {
	return "MB_OBJ";
}


std::string Motherboard::serializeObj() {
	std::ostringstream sStream;
	sStream << "\t" << this->Product::serializeObj();
	sStream << "\n\tMB_SPECIF\n\t{\n\t" << "chipset:" << chipset << ";socket:" << socketType << ";maxRam:" << maxRAM << ";maxFreq:" << maxRFreq
		<< ";usb:"<<usbPorts<<";sata:"<<sata<<";pcie:"<<pcie<<";\n\t}\n";
	return sStream.str();
}

std::ifstream& operator>>(std::ifstream& savefile, Motherboard& rhs) {
	if (!savefile.is_open())
	{
		savefile.open("savefile.txt", std::ios_base::app);
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

Motherboard* Motherboard::clone() {
	Motherboard* m = new Motherboard(*this);
	return m;
}