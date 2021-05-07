#include "Computer.h"
#include "memtrace.h"

PC::PC(){}
PC::PC(const PC& pc) :Product(pc) {
	this->board = pc.board;
	this->cpu = pc.cpu;
	this->gpu = pc.gpu;
	this->pcCase = pc.pcCase;
	this->pcStorage = pc.pcStorage;
	this->psu = pc.psu;
	for(size_t i=0;i<4;i++)
		this->ramslots[i] = pc.ramslots[i];
}
PC* PC::clone() {
	PC* newpc = new PC(*this);
	return newpc;
}