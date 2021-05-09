#include "Videocard.h"
#include <string>
#include <sstream>
#include <fstream>
#include "memtrace.h"


GPU::GPU(unsigned int portHDMI, unsigned int portDisplay,
	unsigned int gpuClock, unsigned int memoryClock, unsigned int vram, unsigned int tdp) : Product(),
	portHDMI(portHDMI), portDisplay(portDisplay), gpuClock(gpuClock), memoryClock(memoryClock), vram(vram), tdp(tdp) {
	oType = obj_t::GPU;
}
GPU::GPU(std::string name, double price, std::string manuf, std::string descript, unsigned int portHDMI, unsigned int portDisplay,
	unsigned int gpuClock, unsigned int memoryClock, unsigned int vram, unsigned int tdp) :
	Product(name, price, manuf, descript),
	portHDMI(portHDMI), portDisplay(portDisplay), gpuClock(gpuClock), memoryClock(memoryClock), vram(vram), tdp(tdp) {
	oType = obj_t::GPU;
}
GPU::GPU(const GPU& g) : Product(g) {
	this->gpuClock = g.gpuClock;
	this->memoryClock = g.memoryClock;
	this->portDisplay = g.portDisplay;
	this->portHDMI = g.portHDMI;
	this->tdp = g.tdp;
	this->vram = g.vram;
}
GPU* GPU::clone()const {
	GPU* g = new GPU(*this);
	g->oType = obj_t::GPU;
	return g;
}

unsigned int GPU::getHDMIports()const { return portHDMI; }
unsigned int GPU::getDisplayports()const { return portDisplay; }
unsigned int GPU::getGPUclock()const { return gpuClock; }
unsigned int GPU::getMemClock()const { return memoryClock; }
unsigned int GPU::getVRAM()const { return vram; }
unsigned int GPU::getTDP()const { return tdp; }


std::string GPU::serializeObj()const {
	std::ostringstream sStream;
	sStream << "\t" << this->Product::serializeObj();	///Calls base class's
	sStream << "\n\tGPU_SPECIF\n\t{\n\t" << "hdmi:" << portHDMI << ";display:" << portDisplay << 
		";gpuClock:"<<gpuClock<<";memoryClock:"<<memoryClock<<";vram:"<<vram<<";tdp:"<<tdp
		<<";\n\t}\n";
	return sStream.str();
}
std::ifstream& operator>>(std::ifstream& savefile, GPU& rhs) {
	if (!savefile.is_open())
		savefile.open("savefile.txt", std::ios_base::app);
	savefile >> (Product&)rhs;
	std::string temp;
	unsigned int portHDMI;
	unsigned int portDisplay;
	unsigned int gpuClock;
	unsigned int memoryClock;
	unsigned int vram;
	unsigned int tdp;
	std::getline(savefile, temp, ':');
	savefile >> portHDMI;
	std::getline(savefile, temp, ':');
	savefile >> portDisplay;
	std::getline(savefile, temp, ':');
	savefile >> gpuClock;
	std::getline(savefile, temp, ':');
	savefile >> memoryClock;
	std::getline(savefile, temp, ':');
	savefile >> vram;
	std::getline(savefile, temp, ':');
	savefile >> tdp;
	std::getline(savefile, temp, '}');
	rhs = GPU(rhs.getName(), rhs.getPrice(), rhs.getManufacturer(), rhs.getDescription(),
		portHDMI,portDisplay,gpuClock,memoryClock,vram,tdp);
	return savefile;
}

bool GPU::operator==(GPU& rhs) const{
	if (rhs.vram == vram && rhs.gpuClock == gpuClock && rhs.memoryClock == memoryClock &&
		rhs.portDisplay == portDisplay && rhs.portHDMI == portHDMI &&
		rhs.tdp == tdp && this->Product::operator==(rhs))
		return true;
	return false;
}
bool GPU::operator!=(GPU& rhs)const {
	return !(this->operator==(rhs));
}