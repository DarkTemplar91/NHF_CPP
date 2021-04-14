#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include <string>
#include "products.h"
#include "processor.h"
#include "Memory.h"
#include "Videocard.h"
#include "Motherboard.h"


class PC :public Product {
	GPU gpu;
	CPU cpu;
	Motherboard board;
	Product pcCase;
	Product psu;
	Storage* pcStorage;
	RAM ramslots[4];
public:
	PC();

};

#endif // !COMPUTER_H
