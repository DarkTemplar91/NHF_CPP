#ifndef MEMORY_H
#define MEMORY_H

#include "products.h"
#include <iostream>
#include <string>
#include "memtrace.h"

/// <summary>
/// Enumerator for multiples of byte
/// </summary>
enum class ByteUnit{bit, byte, kilobyte, megabyte, gigabyte, terabyte};

/// <summary>
/// Base class for data storage/memory
/// </summary>
class Storage : public Product {
	size_t capacity=0;						///Capacity of storage
	ByteUnit notation=ByteUnit::gigabyte;	///Unit of capacity
public:
	Storage(const Storage& m);
	Storage(size_t c = 1, ByteUnit bu = ByteUnit::gigabyte);
	Storage(std::string name, double price, std::string descript, std::string manuf, size_t c, ByteUnit bu);
	size_t getCapacity()const;			///Returns capacity
	ByteUnit getSizeType()const;		///Returns the unit type
	std::string getNotation()const;		///Return notation in string
	std::string serializeObj()const;	///Serializes object

	void print()const;

	bool operator==(Storage& rhs)const;
	bool operator!=(Storage& rhs)const;
	virtual Storage* clone()const;
	

};

/// <summary>
/// Enumerator for RAM types
/// </summary>
enum class MemoryType{DDR,DDR2,DDR3,DDR4,DDR5,SO_DIMM,SO_DIMM2};
/// <summary>
/// Class for modelling Random Access Memory
/// Inheriting from storage
/// </summary>
class RAM : public Storage {
	MemoryType type=MemoryType::DDR4;		///Memory type
	int clockSpeed=0;							///Clockspeed of RAM in Mhz
	int cl=0;									///Cas Latency
	double v=0;								///Voltage;
public:
	RAM() {}
	RAM(const RAM& r);
	RAM(MemoryType type, int clockSpeed, int cl, double v);
	RAM(size_t c, ByteUnit bu, MemoryType type, int clockSpeed, int cl, double v);
	RAM(std::string name, double price, std::string descript, std::string manuf, size_t c, ByteUnit bu, MemoryType type, int clockSpeed, int cl, double v);
	
	MemoryType getMemType()const;		///Returns memory type
	int getClockSpeed()const;			///Returns clockspeed of RAM
	int getlatency()const;				///Returns latency
	double getVoltage()const;			///Returns stock voltage
	
	std::string serializeObj()const;
	
	RAM* clone()const;
	void print()const;

	bool operator!=(RAM& rhs)const;
	bool operator==(RAM& rhs)const;
};
/// <summary>
/// Class for modelling Hard Drive Disks.
/// Inheriting from Storage
/// </summary>
class HDD :public Storage {
	unsigned int rpm=0;		///Round per minute
public:
	HDD() {}
	HDD(unsigned int rpm);
	HDD(std::string name, double price, std::string dscrpt, std::string manufacturer, size_t c = 1, ByteUnit bu = ByteUnit::gigabyte,
		unsigned int rpm = 7200);
	HDD(const HDD& hdd);

	unsigned int getRPM()const;		///Returns RPM of HDD

	void print()const;

	std::string serializeObj()const;
	HDD* clone()const;
	bool operator==(HDD& rhs)const;
	bool operator!=(HDD& rhs)const;

};
/// <summary>
/// Class for modelling SSDs
/// Inheriting directly from Storage class
/// </summary>
class SSD : public Storage {
	unsigned int wSpeed=0;	///Write speed (MB/s)
	unsigned int rSpeed=0;	///Read speed (MB/s)
public:
	SSD() {}
	SSD(unsigned int wSpeed, unsigned int rSpeed);
	SSD(std::string name, double price, std::string dscrpt, std::string manufacturer, size_t c = 1,
		ByteUnit bu = ByteUnit::gigabyte, unsigned int wSpeed = 0, unsigned int rSpeed = 0);
	SSD(const SSD& ssd);

	unsigned int getReadSpeed()const;	///Returns Read speed
	unsigned int getWriteSpeed()const;	///Returns write speed

	void print()const;

	std::string serializeObj()const;
	SSD* clone()const;
	bool operator==(SSD& rhs)const;
	bool operator!=(SSD& rhs)const;
};

std::ifstream& operator>>(std::ifstream& savefile, Storage& rhs);
std::ifstream& operator>>(std::ifstream& savefile, RAM& rhs);
std::ifstream& operator>>(std::ifstream& savefile, HDD& rhs);
std::ifstream& operator>>(std::ifstream& savefile, SSD& rhs);
#endif
