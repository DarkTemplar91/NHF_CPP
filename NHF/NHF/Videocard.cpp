#include "Videocard.h"
#include <string>
#include <sstream>
#include <fstream>
#include "memtrace.h"

std::string GPU::serializeObj() {
	std::ostringstream sStream;
	sStream << "\t" << this->Product::serializeObj();
	sStream << "\n\tGPU_SPECIF\n\t{\n\t" << "\hdmi:" << portHDMI << ";display:" << portDisplay << 
		";gpuClock:"<<gpuClock<<";memoryClock:"<<memoryClock<<";vram:"<<vram<<";tdp:"<<tdp
		<<";\n\t}";
	return sStream.str();
}
std::ifstream& operator>>(std::ifstream& savefile, GPU& rhs) {
	if (!savefile.is_open())
		savefile.open("savefile.txt");
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
	rhs = GPU(rhs.getName(), rhs.getPrice(), rhs.getDescription(), rhs.getManufacturer(),
		portHDMI,portDisplay,gpuClock,memoryClock,vram,tdp);
	savefile.close();
	return savefile;
}
GPU::GPU(const GPU& g):Product(g) {
	this->gpuClock = g.gpuClock;
	this->memoryClock = g.memoryClock;
	this->portDisplay = g.portDisplay;
	this->portHDMI = g.portHDMI;
	this->tdp = g.tdp;
	this->vram = g.vram;
}
GPU* GPU::clone() {
	GPU* g = new GPU(*this);
	return g;
}