#include "catalogue.h"
#include "memtrace.h"

Catalogue::Catalogue() :size(0) {}
Catalogue::Catalogue(Product** list,size_t s) : list(list), size(s) {}


void Catalogue::Add(Product* p) {
	Product** temp = new Product * [++size];
	for (size_t i = 0; i < size - 1; i++) {
		temp[i] = list[i]->clone();
		delete list[i];
	}
	temp[size - 1] = p->clone();
	delete[] list;
	delete p;
	list = temp;
}

template<class T>
void Catalogue::Add(T& p) {
	Product** temp = new Product * [++size];
	for (size_t i = 0; i < size - 1; i++) {
		temp[i] = list[i]->clone();
		delete list[i];
	}
	T* pc = new T(p.clone());
	temp[size - 1] = pc;
	list = temp;
}




//Have to overload == operator for this to work!
//TODO...
void Catalogue::Remove(Product* p) {
	Product** temp = new Product * [--size];
	for (size_t i = 0; i < size +1; i++) {
		if (p == list[i]) {
			delete p;
			Product* t = list[i];
			list[i] = list[size];
			list[size] = t;
			break;
		}
	}
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = list[i]->clone();
		delete list[i];
	}
	list = temp;
		
}
void Catalogue::Clear() {
	for (size_t i = 0; i < size; i++) {
		if (list[i] != nullptr) {
			delete list[i];
			list[i] = nullptr;
		}
	}
}
Catalogue::~Catalogue() {
	Clear();
	if(list!=nullptr)
		delete[] list;
}
Product* Catalogue::operator[](size_t idx){
	if (idx >= this->size)
		throw "Over indexed";
	return list[idx];
}