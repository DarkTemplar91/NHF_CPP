#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include <string>
#include "products.h"
#include "processor.h"
#include "Memory.h"
#include "Videocard.h"
#include "Motherboard.h"
#include "memtrace.h"

/// <summary>
/// Prebuilt pc class
/// </summary>
class PC :public Product {
	GPU gpu; 
	CPU cpu;
	Motherboard board;
	Product pcCase;
	Product psu;
	Storage* pcStorage;
	RAM ramslots;	//The RAM sticks corresponding to the usual 4 slots
public:
	PC();
	PC(const PC& pc);
	PC(GPU& gpu, CPU& cpu, Motherboard& mb, Product& pcCase, Product& psu, Storage* s, RAM& ram);
	PC* clone();
	void print();
	std::string serializeObj()const;
	~PC();

	void assignGPU(GPU&);
	void assignCPU(CPU&);
	void assignMB(Motherboard&);
	void assignCase(Product&);
	void assignPSU(Product&);
	void assignStorage(Storage*);
	void assignRAM(RAM&);

};
std::ifstream& operator>>(std::ifstream& fs, PC& rhs);

#endif // !COMPUTER_H
