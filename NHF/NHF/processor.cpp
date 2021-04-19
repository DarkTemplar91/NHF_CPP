#include "processor.h"
#include "products.h"
#include <string>
#include <sstream>
#include <fstream>
#include "memtrace.h"

std::string CPU::serializeObj(){
	std::ostringstream sStream;
	sStream << "\t"<<this->Product::serializeObj();
	sStream << "\n\tCPU_SPECIF\n\t{\n\t" << "\tGenName:" << genName << ";tdp:" << tdp << ";SocketType:" << socketType << ";base:" << baseClock <<
		";core:" << coreCount << ";threads:" << threadCount << ";cache:" << L2_cache << ";ivga:" << iVGA << ";\n\t}";
	return sStream.str();
}



std::ifstream& operator>>(std::ifstream& is, socket& s) {
	int i;
	is >> i;
	s = socket(i);
	return is;
}
//Reads the object from file
std::ifstream& operator>>(std::ifstream& savefile, CPU& rhs) {
	if (!savefile.is_open())
		savefile.open("savefile.txt");
	savefile >> (Product&)rhs;
	//CPU specif
	std::string genName;
	int tdp;
	socket socketType;
	unsigned int baseClock; 
	unsigned int coreCount; 
	unsigned int threadCount;
	double L2_cache;
	bool iVGA = false;
	std::string temp;
	std::getline(savefile, temp, ':');
	std::getline(savefile, genName,';');
	std::getline(savefile, temp, ':');
	savefile >> tdp;
	std::getline(savefile, temp, ':');
	savefile >> socketType;
	std::getline(savefile, temp, ':');
	savefile >> baseClock;
	std::getline(savefile, temp, ':');
	savefile >> coreCount;
	std::getline(savefile, temp, ':');
	savefile >> threadCount;
	std::getline(savefile, temp, ':');
	savefile >> L2_cache;
	std::getline(savefile, temp, ':');
	savefile >> iVGA;
	savefile.close();
	rhs = CPU(rhs.getName(),rhs.getPrice(),rhs.getManufacturer(),rhs.getDescription(),genName, tdp, socketType, baseClock, coreCount, threadCount, L2_cache, iVGA);
	return savefile;
}
//Prints the basic properties of the object
void CPU::print() {
	//TODO
}


std::string CPU::getStringSocket() {
	switch (this->socketType)
	{
	case AMD_AM4:
		return "AMD AM4";
		break;
	case INTEL_1151:
		return "INTEL 1151";
		break;
	case INTEL_1151V2:
		return "INTEL 1151v2";
		break;
	case INTEL_1200:
		return "INTEL 1200";
		break;
	default:
		return "Unknown socket";
		break;
	}
}
CPU::CPU(const CPU& c) :Product(c) {
	this->baseClock = c.baseClock;
	this->coreCount = c.coreCount;
	this->genName = c.genName;
	this->iVGA = c.iVGA;
	this->L2_cache = c.L2_cache;
	this->socketType = c.socketType;
	this->tdp = c.tdp;
	this->threadCount = c.threadCount;
}
CPU* CPU::clone() {

	CPU* p = new CPU(*this);
	return p;

}
std::string CPU::getObjType(){
	return "CPU_OBJ";
}





