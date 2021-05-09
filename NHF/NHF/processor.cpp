#include "processor.h"
#include "products.h"
#include <string>
#include <sstream>
#include <fstream>
#include "memtrace.h"

std::ostream& operator<<(std::ostream& os,const socket& s) {
	os << static_cast<int>(s);
	return os;
}
std::string CPU::serializeObj()const{
	std::ostringstream sStream;
	sStream << "\t"<<this->Product::serializeObj();	///Calls base class's serialize fucntion
	sStream << "\n\tCPU_SPECIF\n\t{\n\t" << "\tGenName:" << genName << ";tdp:" << tdp << ";SocketType:" << socketType << ";base:" << baseClock <<
		";core:" << coreCount << ";threads:" << threadCount << ";cache:" << L2_cache << ";ivga:" << iVGA << ";\n\t}\n";
	return sStream.str();
}
CPU::CPU(std::string name, int tdp, socket type, unsigned int clock, unsigned int core, unsigned int thread, double c, bool vga) :Product(), genName(name), tdp(tdp),
socketType(type), baseClock(clock), coreCount(core), threadCount(thread), L2_cache(c), iVGA(vga) {
	oType = obj_t::CPU;
}
CPU::CPU(std::string pName, double price, std::string manuf, std::string descript, std::string name, int tdp,
	socket type, unsigned int clock, unsigned int core, unsigned int thread, double c, bool vga)
	:Product(pName, price, manuf, descript),
	genName(name), tdp(tdp),
	socketType(type), baseClock(clock), coreCount(core), threadCount(thread), L2_cache(c), iVGA(vga) {
	oType = obj_t::CPU;
}
CPU::CPU(const CPU& c):Product(c), genName(c.genName), tdp(c.tdp), socketType(c.socketType), baseClock(c.baseClock),
coreCount(c.coreCount), threadCount(c.threadCount), L2_cache(c.L2_cache), iVGA(c.iVGA) {
	oType = obj_t::CPU;
}

std::string CPU::getGenName()const { return genName; }
int CPU::getTDP()const { return tdp; }
socket CPU::getSocketType()const { return socketType; }
unsigned int CPU::getBaseClock()const { return baseClock; }
unsigned int CPU::getCoreCount()const { return coreCount; }
unsigned int CPU::getThreadCount()const { return threadCount; }
double CPU::getCacheSize()const { return L2_cache; }
bool CPU::ivga()const { return iVGA; }


std::ifstream& operator>>(std::ifstream& is, socket& s) {
	int i;
	is >> i;
	s = socket(i);
	return is;
}
//Reads the object from file
std::ifstream& operator>>(std::ifstream& savefile, CPU& rhs) {
	if (!savefile.is_open())
		savefile.open("savefile.txt", std::ios_base::app);
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
	std::getline(savefile, temp, '}');
	rhs = CPU(rhs.getName(),rhs.getPrice(),rhs.getManufacturer(),rhs.getDescription(),genName, tdp, socketType, baseClock, coreCount, threadCount, L2_cache, iVGA);
	return savefile;
}
//Prints the basic properties of the object
void CPU::print()const {
	std::cout << serializeObj();
}


std::string CPU::getStringSocket()const {
	switch (this->socketType)
	{
	case socket::AMD_AM4:
		return "AMD AM4";
		break;
	case socket::INTEL_1151:
		return "INTEL 1151";
		break;
	case socket::INTEL_1151V2:
		return "INTEL 1151v2";
		break;
	case socket::INTEL_1200:
		return "INTEL 1200";
		break;
	default:
		return "Unknown socket";
		break;
	}
}

CPU* CPU::clone()const {

	CPU* p = new CPU(*this);
	return p;

}


bool CPU::operator==(CPU& rhs) const{
	if (rhs.baseClock == baseClock && rhs.coreCount == coreCount && rhs.genName == genName &&
		rhs.iVGA == iVGA && rhs.L2_cache == L2_cache && rhs.threadCount == threadCount &&
		rhs.socketType == socketType && this->Product::operator==(rhs))
		return true;
	return false;
}
bool CPU::operator!=(CPU& rhs)const {
	return !(this->operator==(rhs));
}


