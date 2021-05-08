#include "Memory.h"
#include <fstream>
#include <sstream>
#include "memtrace.h"

//Storage
//Storage constructors
Storage::Storage(size_t c, ByteUnit bu) :capacity(c), notation(bu) { t = obj_t::Storage; }
Storage::Storage(std::string name, double price, std::string descript, std::string manuf, size_t c, ByteUnit bu) :Product(name, price, manuf, descript),
capacity(c), notation(bu) {
	t = obj_t::Storage;
}
Storage::Storage(const Storage& m) : Product(m), capacity(m.capacity), notation(m.notation) { t = obj_t::Storage; }
//End of constructors

size_t Storage::getCapacity()const { return capacity; }
ByteUnit Storage::getSizeType()const { return notation; }
std::string Storage::getNotation()const {
	switch (notation) {
	case 0:
		return "bit";
		break;
	case 1:
		return "byte";
		break;
	case 2:
		return "KB";
		break;
	case 3:
		return "MB";
		break;
	case 4:
		return "GB";
		break;
	case 5:
		return "TB";
		break;
	default: return "NaN";
		break;
	}
}

bool Storage::operator==(Storage& rhs) {
	if (Product::operator==(rhs) && capacity == rhs.capacity)
		return true;
	return false;
}
bool Storage::operator!=(Storage& rhs) {
	return !(Storage::operator==(rhs));
}



//RAM
//RAM constructors
RAM::RAM(MemoryType type, int clockSpeed, int cl, double v) :type(type), clockSpeed(clockSpeed), cl(cl), v(v) { t = obj_t::RAM; }
RAM::RAM(size_t c, ByteUnit bu, MemoryType type, int clockSpeed, int cl, double v) :Storage(c, bu), type(type), clockSpeed(clockSpeed), cl(cl), v(v) { t = obj_t::RAM; }
RAM::RAM(std::string name, double price, std::string descript, std::string manuf, size_t c, ByteUnit bu, MemoryType type, int clockSpeed, int cl, double v)
	:Storage(name, price, descript, manuf, c, bu), type(type), clockSpeed(clockSpeed), cl(cl), v(v) {
	t = obj_t::RAM;
}
RAM::RAM(const RAM& r) : Storage(r), type(r.type), clockSpeed(r.clockSpeed), cl(r.cl), v(r.v) { t = obj_t::RAM; }
//End of RAM constructors

MemoryType RAM::getMemType() { return type; }
int RAM::getClockSpeed() { return clockSpeed; }
int RAM::getlatency() { return cl; }
double RAM::getVoltage() { return v; }
bool RAM::operator==(RAM& rhs) {
	if (Storage::operator==(rhs) &&
		rhs.cl == cl && rhs.clockSpeed == clockSpeed &&
		rhs.type == type && rhs.v == v)
		return true;
	return false;
}
bool RAM::operator!=(RAM& rhs) {
	return !(RAM::operator==(rhs));
}
//


//SSD
//SSD constructors
SSD::SSD(const SSD& s) :Storage(s) {
	this->rSpeed = s.rSpeed;
	this->wSpeed = s.wSpeed;
	t = obj_t::SSD;
}
SSD::SSD(unsigned int wSpeed, unsigned int rSpeed) :Storage(), wSpeed(wSpeed), rSpeed(rSpeed) { t = obj_t::SSD; }
SSD::SSD(std::string name, double price, std::string dscrpt, std::string manufacturer, size_t c,
	ByteUnit bu, unsigned int wSpeed, unsigned int rSpeed) :Storage(name, price, dscrpt, manufacturer, c, bu),
	wSpeed(wSpeed), rSpeed(rSpeed) {
	t = obj_t::SSD;
}

unsigned int SSD::getReadSpeed() { return rSpeed; }
unsigned int SSD::getWriteSpeed() { return wSpeed; }
bool SSD::operator==(SSD& rhs) {
	if (Storage::operator==(rhs) &&
		rhs.rSpeed == rSpeed && rhs.wSpeed == wSpeed)
		return true;
	return false;
}
bool SSD::operator!=(SSD& rhs) {
	return!(SSD::operator==(rhs));
}
//


//HDD
//HDD constructors
HDD::HDD(unsigned int rpm) :Storage(), rpm(rpm) { t = obj_t::HDD; }
HDD::HDD(std::string name, double price, std::string dscrpt, std::string manufacturer, size_t c, ByteUnit bu,
	unsigned int rpm) :
	Storage(name, price, dscrpt, manufacturer, c, bu), rpm(rpm) {
	t = obj_t::HDD;
}
unsigned int HDD::getRPM() { return rpm; }
HDD::HDD(const HDD& h) : Storage(h) {
	this->rpm = h.rpm;
	t = obj_t::HDD;
}
bool HDD::operator==(HDD& rhs) {
	if (Storage::operator==(rhs) &&
		rhs.rpm == rpm)
		return true;
	return false;
}
bool HDD::operator!=(HDD& rhs) {
	return !(HDD::operator==(rhs));
}

std::string Storage::serializeObj()const {
	std::ostringstream sStream;
	sStream << this->Product::serializeObj();
	sStream << "\n\tStorage_SPECIF\n\t{\n\t" << "\tCapacity:" << capacity << ";notation:" << notation<<";\n\t}\n";
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
		savefile.open("savefile.txt", std::ios_base::app);
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

std::string RAM::serializeObj() const{
	std::ostringstream sStream;
	sStream << this->Storage::serializeObj();
	sStream << "\n\tRAM_SPECIF\n\t{\n\t" << "\ttype:" << type << ";clockspeed:" << clockSpeed << ";cl:"
		<< cl<<";v:"<<v << ";\n\t}\n";
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
		savefile.open("savefile.txt", std::ios_base::app);
	savefile >> (Storage&)rhs;
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
	std::getline(savefile, temp, '}');
	rhs = RAM(rhs.getName(), rhs.getPrice(), rhs.getDescription(), rhs.getManufacturer(),
		rhs.getCapacity(), rhs.getSizeType(), type, clockSpeed, cl, v);
	return savefile;
}

std::string SSD::serializeObj() const{
	std::ostringstream sStream;
	sStream << this->Storage::serializeObj();
	sStream << "\n\tSSD_SPECIF\n\t{\n\t" << "\twSpeed:" << wSpeed << ";rSpeed:" << rSpeed << ";\n\t}\n";
	return sStream.str();
}
std::ifstream& operator>>(std::ifstream& savefile, SSD& rhs) {
	if (!savefile.is_open())
		savefile.open("savefile.txt", std::ios_base::app);
	savefile >> (Storage&)rhs;
	std::string temp;
	unsigned int wSpeed;
	unsigned int rSpeed;
	std::getline(savefile, temp, ':');
	savefile >> wSpeed;
	std::getline(savefile, temp, ':');
	savefile >> rSpeed;
	std::getline(savefile, temp, '}');
	rhs = SSD(rhs.getName(), rhs.getPrice(), rhs.getDescription(), rhs.getManufacturer(),
		rhs.getCapacity(), rhs.getSizeType(), wSpeed, rSpeed);
	return savefile;
}

std::string HDD::serializeObj()const {
	std::ostringstream sStream;
	sStream  << this->Storage::serializeObj();
	sStream << "\n\tHDD_SPECIF\n\t{\n\t" << "\trpm:" << rpm<<";\n\t}\n";
	return sStream.str();
}
std::ifstream& operator>>(std::ifstream& savefile, HDD& rhs) {
	if (!savefile.is_open())
		savefile.open("savefile.txt", std::ios_base::app);
	savefile >> (Storage&)rhs;
	std::string temp;
	unsigned int rpm;
	std::getline(savefile, temp, ':');
	savefile >> rpm;
	std::getline(savefile, temp, '}');
	rhs = HDD(rhs.getName(), rhs.getPrice(), rhs.getDescription(), rhs.getManufacturer(),
		rhs.getCapacity(), rhs.getSizeType(), rpm);
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

void Storage::print() {
	std::cout << "Storage:"<<std::endl;
	std::cout << this->serializeObj();
}
void HDD::print() {
	std::cout << "HDD:"<<std::endl;
	std::cout << this->serializeObj();
}
void SSD::print() {
	std::cout << "SSD:"<<std::endl;
	std::cout << this->serializeObj();
}
void RAM::print() {
	std::cout << "RAM:" << std::endl;
	std::cout << this->serializeObj();
}