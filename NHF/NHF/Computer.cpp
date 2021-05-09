#include "Computer.h"
#include "memtrace.h"

PC::PC(){}
PC::PC(const PC& pc) :Product(pc) {
	this->board = pc.board;
	this->cpu = pc.cpu;
	this->gpu = pc.gpu;
	this->pcCase = pc.pcCase;
	this->pcStorage = pc.pcStorage->clone();
	this->psu = pc.psu;
	this->ramslots = pc.ramslots;
	this->increaseStock(1);
}
PC::PC(GPU& gpu, CPU& cpu, Motherboard& mb, Product& pcCase, Product& psu, Storage* s, RAM& ram) :gpu(gpu), cpu(cpu), board(mb), pcCase(pcCase), psu(psu), ramslots(ram) {
	pcStorage = s->clone();
	delete s;
	double price = gpu.getPrice() + cpu.getPrice() + mb.getPrice() + pcCase.getPrice() + psu.getPrice() + pcStorage->getPrice() + ram.getPrice();
	this->setPrice(price);
	std::stringstream ss;
	ss << "Pre-built PC: " << gpu.getName() << ", " << cpu.getName() <<", "<< ram.getCapacity()<<" GB RAM";
	this->setName(ss.str());
	this->increaseStock(1);
}
PC* PC::clone()const {
	PC* newpc = new PC(*this);
	return newpc;
}
std::string PC::serializeObj()const {
	std::stringstream ss;
	ss << "\n" << this->Product::serializeObj();
	ss << std::endl << gpu.serializeObj() << std::endl <<
		cpu.serializeObj() << std::endl
		<< board.serializeObj() << std::endl << pcCase.serializeObj() <<
		"\n" << psu.serializeObj() << "\n" << pcStorage->getObjType() << pcStorage->serializeObj() << std::endl << ramslots.serializeObj();
	ss << "\n}\n";
	return ss.str();
}
void PC::print()const {
	std::cout << serializeObj();
}
PC::~PC() {
	delete pcStorage;
}


void PC::assignCase(Product& c) {
	this->pcCase = c;
}
void PC::assignCPU(CPU& cpu) {
	this->cpu = cpu;
}
void PC::assignGPU(GPU& gpu) {
	this->gpu = gpu;
}
void PC::assignMB(Motherboard& mb) {
	this->board = mb;
}
void PC::assignPSU(Product& psu) {
	this->psu = psu;
}
void PC::assignRAM(RAM& r) {
	this->ramslots = r;
}
void PC::assignStorage(Storage* s) {
	this->pcStorage = s->clone();
	delete s;
}

GPU& PC::getGPU() { return gpu; }
CPU& PC::getCPU() { return cpu; };
Motherboard& PC::getMB() { return board; }
Product& PC::getCase() { return pcCase; }
Product& PC::getPSU() { return psu; }
RAM& PC::getRAM() { return ramslots; }
Storage* PC::getStorage() { return pcStorage; }

std::ifstream& operator>>(std::ifstream& fs, PC& rhs) {
	GPU g; CPU c; Motherboard mb; RAM r; Product p; Product case1;
	Product base;
	int t;
	fs >> base;
	fs >> g;
	fs >> c;
	fs >> mb;
	fs >> case1;
	fs >> p;
	std::string str;
	std::getline(fs,str , '\n');
	fs >> t;
	//t determines if the storage type is SSD or HDD. It correspondes to the enum value
	if (t == 4) {
		SSD* s = new SSD();
		fs >> *s;
		rhs.assignStorage(s);
	}
	else if (t == 3) {
		HDD* s = new HDD();
		fs >> *s;
		rhs.assignStorage(s);

	}
	fs >> r;
	rhs.assignCase(case1);
	rhs.assignCPU(c);
	rhs.assignGPU(g);
	rhs.assignMB(mb);
	rhs.assignPSU(p);
	rhs.assignRAM(r);
	rhs.setPrice(base.getPrice());
	rhs.setDescription(base.getDescription());
	rhs.setManuf(base.getManufacturer());
	rhs.setName(base.getName());
	int delta=(int)base.getAmount()-(int)rhs.getAmount();
	delta < 0 ? rhs.decreaseStock(delta) : rhs.increaseStock(delta);
	return fs;
}