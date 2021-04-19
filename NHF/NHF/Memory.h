#ifndef MEMORY_H
#define MEMORY_H

#include "products.h"
#include <iostream>
#include <string>
#include "memtrace.h"

enum ByteUnit{bit, byte, kilobyte, megabyte, gigabyte, terabyte};

class Storage : public Product {
	size_t capacity;
	ByteUnit notation;
public:
	Storage(const Storage& m);
	Storage(size_t c=1, ByteUnit bu=ByteUnit::gigabyte) :capacity(c), notation(bu) {}
	Storage(std::string name, double price, std::string descript, std::string manuf, size_t c, ByteUnit bu) :Product(name, price, manuf, descript),
		capacity(c),notation(bu) {}
	size_t getCapacity()const { return capacity; }
	ByteUnit getSizeType()const { return notation; }
	std::string getSizeType_string()const;
	std::string getNotation()const;
	std::string serializeObj();

	virtual std::string getObjType() {
		return "STORAGE_OBJ";
	}
	virtual Storage* clone();
	

};
enum MemoryType{DDR,DDR2,DDR3,DDR4,DDR5,SO_DIMM,SO_DIMM2};
class RAM : public Storage {
	MemoryType type;
	int clockSpeed; //in Mhz
	int cl; //Cas Latency
	double v; //Voltage;
public:
	RAM() {}
	RAM(const RAM& r);
	RAM(MemoryType type, int clockSpeed, int cl, double v) :type(type), clockSpeed(clockSpeed), cl(cl), v(v) {}
	RAM(size_t c, ByteUnit bu, MemoryType type, int clockSpeed, int cl, double v) :Storage(c,bu),type(type), clockSpeed(clockSpeed), cl(cl), v(v) {}
	RAM(std::string name, double price, std::string descript, std::string manuf, size_t c, ByteUnit bu, MemoryType type, int clockSpeed, int cl, double v)
		:Storage(name, price, descript, manuf, c, bu), type(type), clockSpeed(clockSpeed), cl(cl), v(v) {}
	MemoryType getMemType() { return type; }
	int getClockSpeed() { return clockSpeed; }
	int getlatency() { return cl; }
	double getVoltage() { return v; }
	std::string getObjType() {
		return "RAM_OBJ";
	}

	std::string serializeObj();
	RAM* clone();
};

class HDD :public Storage {
	unsigned int rpm;
public:
	HDD() {}
	HDD(unsigned int rpm) :Storage(),rpm(rpm) {}
	HDD(std::string name, double price, std::string dscrpt, std::string manufacturer,size_t c=1, ByteUnit bu=gigabyte,
		unsigned int rpm=7200) :
		Storage(name, price, dscrpt, manufacturer,c,bu), rpm(rpm) {}
	HDD(const HDD& hdd);
	unsigned int getRPM() { return rpm; }
	std::string getObjType() {
		return "HDD_OBJ";
	}
	std::string serializeObj();
	HDD* clone();

};
class SSD : public Storage {
	unsigned int wSpeed;
	unsigned int rSpeed;
public:
	SSD() {}
	SSD(unsigned int wSpeed, unsigned int rSpeed) :Storage(), wSpeed(wSpeed), rSpeed(rSpeed) {}
	SSD(std::string name, double price, std::string dscrpt, std::string manufacturer, size_t c = 1,
		ByteUnit bu = gigabyte, unsigned int wSpeed = 0, unsigned int rSpeed = 0) :Storage(name, price, dscrpt, manufacturer, c, bu),
		wSpeed(wSpeed), rSpeed(rSpeed) {}
	SSD(const SSD& ssd);
	unsigned int getReadSpeed() { return rSpeed; }
	unsigned int getWriteSpeed() { return wSpeed; }
	std::string getObjType() {
		return "SSD_OBJ";
	}
	std::string serializeObj();
	SSD* clone();
};

std::ifstream& operator>>(std::ifstream& savefile, Storage& rhs);
std::ifstream& operator>>(std::ifstream& savefile, RAM& rhs);
std::ifstream& operator>>(std::ifstream& savefile, HDD& rhs);
std::ifstream& operator>>(std::ifstream& savefile, SSD& rhs);
#endif
