#include "catalogue.h"

Catalogue::Catalogue() :size(0) {}
Catalogue::Catalogue(Product** list,size_t s) : list(list), size(s) {}

void Catalogue::Add(Product* p) {
	Product** temp = new Product*[++size];
	for (size_t i = 0; i < size - 1; i++) {
		temp[i] = list[i]->clone();
		delete list[i];
	}
	temp[size - 1] = p->clone();
	delete p;
	list = temp;
}
void Catalogue::Remove(Product* p) {
	Product** temp = new Product * [--size];
	int idx = -1;
	for (size_t i = 0; i < size +1; i++) {
		if (p == list[i]) {
			idx = i;
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
	delete[] list;
}