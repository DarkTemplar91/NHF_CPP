#include "Memory.h"

std::string Memory::getSizeType_string()const {
	switch (notation) {
	case 0:
		return "bit";
		break;
	case 1:
		return "byte";
		break;
	case 2:
		return "kilobyte";
		break;
	case 3:
		return "megabyte";
		break;
	case 4:
		return "gigabyte";
		break;
	case 5:
		return "terabyte";
		break;
	default:
		return "NaN";
		break;
	}
}
std::string Memory::getNotation()const {
	switch (notation) {
	case 0:
		return "bit";
		break;
	case 1:
		return "B";
		break;
	case 2:
		return "kB";
		break;
	case 3:
		return "mB";
		break;
	case 4:
		return "gB";
		break;
	case 5:
		return "tB";
		break;
	default: return "NaN";
		break;
	}
}
Memory::Memory(const Memory& m) {
	(Product)*this = Product(m);
	this->capacity = m.capacity;
	this->notation = m.notation;
}
RAM::RAM(const RAM& r) {
	(Memory)*this = Memory(r);
	this->cl = r.cl;
	this->clockSpeed = r.clockSpeed;
	this->type = r.type;
	this->v = r.v;
}