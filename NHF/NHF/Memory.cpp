#include "Memory.h"
#include <fstream>
#include <sstream>
#include "memtrace.h"

std::string Storage::getSizeType_string()const {
	switch (notation) {
	case 0:
		return "bit";
		break;
	case 1:
		return "byte";
		break;
	case 2:
		return "kilobyte";
		break;
	case 3:
		return "megabyte";
		break;
	case 4:
		return "gigabyte";
		break;
	case 5:
		return "terabyte";
		break;
	default:
		return "NaN";
		break;
	}
}
std::string Storage::getNotation()const {
	switch (notation) {
	case 0:
		return "bit";
		break;
	case 1:
		return "B";
		break;
	case 2:
		return "kB";
		break;
	case 3:
		return "mB";
		break;
	case 4:
		return "gB";
		break;
	case 5:
		return "tB";
		break;
	default: return "NaN";
		break;
	}
}
Storage::Storage(const Storage& m):Product(m) {
	this->capacity = m.capacity;
	this->notation = m.notation;
}
RAM::RAM(const RAM& r):Storage(r) {
	this->cl = r.cl;
	this->clockSpeed = r.clockSpeed;
	this->type = r.type;
	this->v = r.v;
}
SSD::SSD(const SSD& s) :Storage(s) {
	this->rSpeed = s.rSpeed;
	this->wSpeed = s.wSpeed;
}
HDD::HDD(const HDD& h) : Storage(h) {
	this->rpm = h.rpm;
}

std::string Storage::serializeObj() {
	std::ostringstream sStream;
	sStream << "\t" << this->Product::serializeObj();
	sStream << "\n\tStorage_SPECIF\n\t{\n\t" << "\tCapacity:" << capacity << ";notation" << notation<<";\n\t}";
	return sStream.str();
}
std::ifstream& operator>>(std::ifstream& is, ByteUnit& b) {
	int i;
	is >> i;
	b = ByteUnit(i);
	return is;
}
std::ifstream& operator>>(std::ifstream& savefile, Storage& rhs) {
	if (!savefile.is_open())
		savefile.open("savefile.txt");
	savefile >> (Product&)rhs;
	size_t capacity;
	ByteUnit notation;
	std::string temp;
	std::getline(savefile, temp, ':');
	savefile >> capacity;
	std::getline(savefile, temp, ':');
	savefile >> notation;
	rhs = Storage(rhs.getName(), rhs.getPrice(), rhs.getDescription(), rhs.getManufacturer(), capacity, notation);
	return savefile;
}

std::string RAM::serializeObj() {
	std::ostringstream sStream;
	sStream << this->Storage::serializeObj();
	sStream << "\n\tRAM_SPECIF\n\t{\n\t" << "\ttype" << type << ";clockspeed:" << clockSpeed << ";cl:"
		<< cl<<";v:"<<v << ";\n\t}";
	return sStream.str();
}

std::ifstream& operator>>(std::ifstream& is, MemoryType& m) {
	int i;
	is >> i;
	m = MemoryType(i);
	return is;
}

std::ifstream& operator>>(std::ifstream& savefile, RAM& rhs) {
	if (!savefile.is_open())
		savefile.open("savefile.txt");
	savefile >> (Product&)rhs;
	MemoryType type;
	int clockSpeed; 
	int cl; 
	double v; 
	std::string temp;
	std::getline(savefile, temp, ':');
	savefile >> type;
	std::getline(savefile, temp, ':');
	savefile >> clockSpeed;
	std::getline(savefile, temp, ':');
	savefile >> cl;
	std::getline(savefile, temp, ':');
	savefile >> v;

	rhs = RAM(rhs.getName(), rhs.getPrice(), rhs.getDescription(), rhs.getManufacturer(),
		rhs.getCapacity(), rhs.getSizeType(), type, clockSpeed, cl, v);
	savefile.close();
	return savefile;
}

std::string SSD::serializeObj() {
	std::ostringstream sStream;
	sStream << "\t" << this->Storage::serializeObj();
	sStream << "\n\tSSD_SPECIF\n\t{\n\t" << "\twSpeed" << wSpeed << ";rSpeed" << rSpeed << ";\n\t}";
	return sStream.str();
}
std::ifstream& operator>>(std::ifstream& savefile, SSD& rhs) {
	if (!savefile.is_open())
		savefile.open("savefile.txt");
	savefile >> (Storage&)rhs;
	std::string temp;
	unsigned int wSpeed;
	unsigned int rSpeed;
	std::getline(savefile, temp, ':');
	savefile >> wSpeed;
	std::getline(savefile, temp, ':');
	savefile >> rSpeed;
	rhs = SSD(rhs.getName(), rhs.getPrice(), rhs.getDescription(), rhs.getManufacturer(),
		rhs.getCapacity(), rhs.getSizeType(), wSpeed, rSpeed);
	savefile.close();
	return savefile;
}

std::string HDD::serializeObj() {
	std::ostringstream sStream;
	sStream << "\t" << this->Storage::serializeObj();
	sStream << "\n\tHDD_SPECIF\n\t{\n\t" << "\trpm" << rpm<<";\n\t}";
	return sStream.str();
}
std::ifstream& operator>>(std::ifstream& savefile, HDD& rhs) {
	if (!savefile.is_open())
		savefile.open("savefile.txt");
	savefile >> (Storage&)rhs;
	std::string temp;
	unsigned int rpm;
	std::getline(savefile, temp, ':');
	savefile >> rpm;
	rhs = HDD(rhs.getName(), rhs.getPrice(), rhs.getDescription(), rhs.getManufacturer(),
		rhs.getCapacity(), rhs.getSizeType(), rpm);
	savefile.close();
	return savefile;
}
RAM* RAM::clone() {
	RAM* newram = new RAM(*this);
	return newram;
}
Storage* Storage::clone() {
	Storage* s = new Storage(*this);
	return s;
}
SSD* SSD::clone() {
	SSD* s = new SSD(*this);
	return s;
}
HDD* HDD::clone() {
	HDD* h = new HDD(*this);
	return h;
}