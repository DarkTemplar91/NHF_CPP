#ifndef MEMORY_H
#define MEMORY_H

#include "products.h"
#include <iostream>
#include <string>
#include "memtrace.h"

/// <summary>
/// Enumerator for multiples of byte
/// </summary>
enum ByteUnit{bit, byte, kilobyte, megabyte, gigabyte, terabyte};

/// <summary>
/// Base class for data storage/memory
/// </summary>
class Storage : public Product {
	size_t capacity;		///Capacity of storage
	ByteUnit notation;		///Unit of capacity
public:
	Storage(const Storage& m);
	Storage(size_t c = 1, ByteUnit bu = ByteUnit::gigabyte);
	Storage(std::string name, double price, std::string descript, std::string manuf, size_t c, ByteUnit bu);
	size_t getCapacity()const;			///Returns capacity
	ByteUnit getSizeType()const;		///Returns the unit type
	std::string getNotation()const;		///Return notation in string
	std::string serializeObj()const;	///Serializes object

	void print();

	virtual bool operator==(Storage& rhs);
	virtual bool operator!=(Storage& rhs);
	virtual Storage* clone();
	

};

/// <summary>
/// Enumerator for RAM types
/// </summary>
enum MemoryType{DDR,DDR2,DDR3,DDR4,DDR5,SO_DIMM,SO_DIMM2};
/// <summary>
/// Class for modelling Random Access Memory
/// Inheriting from storage
/// </summary>
class RAM : public Storage {
	MemoryType type;		///Memory type
	int clockSpeed;			///Clockspeed of RAM in Mhz
	int cl;					///Cas Latency
	double v;				///Voltage;
public:
	RAM() {}
	RAM(const RAM& r);
	RAM(MemoryType type, int clockSpeed, int cl, double v);
	RAM(size_t c, ByteUnit bu, MemoryType type, int clockSpeed, int cl, double v);
	RAM(std::string name, double price, std::string descript, std::string manuf, size_t c, ByteUnit bu, MemoryType type, int clockSpeed, int cl, double v);
	
	MemoryType getMemType();		///Returns memory type
	int getClockSpeed();			///Returns clockspeed of RAM
	int getlatency();				///Returns latency
	double getVoltage();			///Returns stock voltage
	
	std::string serializeObj()const;
	
	RAM* clone();
	void print();

	bool operator!=(RAM& rhs);
	bool operator==(RAM& rhs);
};
/// <summary>
/// Class for modelling Hard Drive Disks.
/// Inheriting from Storage
/// </summary>
class HDD :public Storage {
	unsigned int rpm;		///Round per minute
public:
	HDD() {}
	HDD(unsigned int rpm);
	HDD(std::string name, double price, std::string dscrpt, std::string manufacturer, size_t c = 1, ByteUnit bu = gigabyte,
		unsigned int rpm = 7200);
	HDD(const HDD& hdd);

	unsigned int getRPM();		///Returns RPM of HDD

	void print();

	std::string serializeObj()const;
	HDD* clone();
	bool operator==(HDD& rhs);
	bool operator!=(HDD& rhs);

};
/// <summary>
/// Class for modelling SSDs
/// Inheriting directly from Storage class
/// </summary>
class SSD : public Storage {
	unsigned int wSpeed;	///Write speed (MB/s)
	unsigned int rSpeed;	///Read speed (MB/s)
public:
	SSD() {}
	SSD(unsigned int wSpeed, unsigned int rSpeed);
	SSD(std::string name, double price, std::string dscrpt, std::string manufacturer, size_t c = 1,
		ByteUnit bu = gigabyte, unsigned int wSpeed = 0, unsigned int rSpeed = 0);
	SSD(const SSD& ssd);

	unsigned int getReadSpeed();	///Returns Read speed
	unsigned int getWriteSpeed();	///Returns write speed

	void print();

	std::string serializeObj()const;
	SSD* clone();
	bool operator==(SSD& rhs);
	bool operator!=(SSD& rhs);
};

std::ifstream& operator>>(std::ifstream& savefile, Storage& rhs);
std::ifstream& operator>>(std::ifstream& savefile, RAM& rhs);
std::ifstream& operator>>(std::ifstream& savefile, HDD& rhs);
std::ifstream& operator>>(std::ifstream& savefile, SSD& rhs);
#endif
