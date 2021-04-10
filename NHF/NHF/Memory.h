#ifndef MEMORY_H
#define MEMORY_H

#include "products.h"
#include <iostream>
#include <string>

enum ByteUnit{bit, byte, kilobyte, megabyte, gigabyte, terabyte};


class Memory : public Product {
	size_t capacity;
	ByteUnit notation;
public:
	Memory(const Memory& m);
	Memory(): capacity(0),notation(ByteUnit::bit){}
	Memory(size_t c, ByteUnit bu) :capacity(c), notation(bu) {}
	Memory(std::string name, double price, std::string descript, std::string manuf, size_t c, ByteUnit bu) :Product(name, price, descript),
		capacity(c),notation(bu) {}
	size_t getCapacity()const { return capacity; }
	ByteUnit getSizeType()const { return notation; }
	std::string getSizeType_string()const;
	std::string getNotation()const;
	

};
enum MemoryType{DDR,DDR2,DDR3,DDR4,DDR5,SO_DIMM,SO_DIMM2};
class RAM : public Memory {
	MemoryType type;
	int clockSpeed; //in Mhz
	int cl; //Cas Latency
	double v; //Voltage;
public:
	RAM(const RAM& r);
	RAM(MemoryType type, int clockSpeed, int cl, int v) :type(type), clockSpeed(clockSpeed), cl(cl), v(v) {}
	RAM(size_t c, ByteUnit bu, MemoryType type, int clockSpeed, int cl, int v) :Memory(c,bu),type(type), clockSpeed(clockSpeed), cl(cl), v(v) {}
	RAM(std::string name, double price, std::string descript, std::string manuf, size_t c, ByteUnit bu, MemoryType type, int clockSpeed, int cl, int v)
		:Memory(name, price, descript, manuf, c, bu), type(type), clockSpeed(clockSpeed), cl(cl), v(v) {}
};

#endif