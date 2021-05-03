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
	Storage(size_t c = 1, ByteUnit bu = ByteUnit::gigabyte);
	Storage(std::string name, double price, std::string descript, std::string manuf, size_t c, ByteUnit bu);
	size_t getCapacity()const;
	ByteUnit getSizeType()const;
	std::string getSizeType_string()const;
	std::string getNotation()const;
	std::string serializeObj();

	virtual bool operator==(Storage& rhs);
	virtual bool operator!=(Storage& rhs);
	virtual std::string getObjType();
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
	RAM(MemoryType type, int clockSpeed, int cl, double v);
	RAM(size_t c, ByteUnit bu, MemoryType type, int clockSpeed, int cl, double v);
	RAM(std::string name, double price, std::string descript, std::string manuf, size_t c, ByteUnit bu, MemoryType type, int clockSpeed, int cl, double v);
	MemoryType getMemType();
	int getClockSpeed();
	int getlatency();
	double getVoltage();
	std::string getObjType();
	std::string serializeObj();
	RAM* clone();

	bool operator!=(RAM& rhs);
	bool operator==(RAM& rhs);
};

class HDD :public Storage {
	unsigned int rpm;
public:
	HDD() {}
	HDD(unsigned int rpm);
	HDD(std::string name, double price, std::string dscrpt, std::string manufacturer, size_t c = 1, ByteUnit bu = gigabyte,
		unsigned int rpm = 7200);
	HDD(const HDD& hdd);
	unsigned int getRPM();
	std::string getObjType();
	std::string serializeObj();
	HDD* clone();
	bool operator==(HDD& rhs);
	bool operator!=(HDD& rhs);

};
class SSD : public Storage {
	unsigned int wSpeed;
	unsigned int rSpeed;
public:
	SSD() {}
	SSD(unsigned int wSpeed, unsigned int rSpeed);
	SSD(std::string name, double price, std::string dscrpt, std::string manufacturer, size_t c = 1,
		ByteUnit bu = gigabyte, unsigned int wSpeed = 0, unsigned int rSpeed = 0);
	SSD(const SSD& ssd);
	unsigned int getReadSpeed();
	unsigned int getWriteSpeed();
	std::string getObjType();
	std::string serializeObj();
	SSD* clone();
	bool operator==(SSD& rhs);
	bool operator!=(SSD& rhs);
};

std::ifstream& operator>>(std::ifstream& savefile, Storage& rhs);
std::ifstream& operator>>(std::ifstream& savefile, RAM& rhs);
std::ifstream& operator>>(std::ifstream& savefile, HDD& rhs);
std::ifstream& operator>>(std::ifstream& savefile, SSD& rhs);
#endif
