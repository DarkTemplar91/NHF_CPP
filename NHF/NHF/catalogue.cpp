#include "catalogue.h"
#include "memtrace.h"
#include <string>

Catalogue::Catalogue() :size(0){}
Catalogue::Catalogue(Product** list,size_t s) : list(list), size(s){}
size_t Catalogue::getSize() {
	return size;
}

void Catalogue::Add(Product* p) {
	Product** temp = new Product *[++size];
	for (size_t i = 0; i < size - 1; i++) {
		temp[i] = list[i]->clone();
		delete list[i];
	}
	temp[size - 1] = p->clone();
	delete[] list;
	delete p;
	list = temp;
}





//Have to overload == operator for this to work!
//TODO...
void Catalogue::Remove(Product* p) {
	Product** temp = new Product * [--size];
	for (size_t i = 0; i < size +1; i++) {
		if (*p == *list[i]) {
			delete p;
			Product* t = list[i];
			list[i] = list[size];
			list[size] = t;
			delete list[size];
			break;
		}
	}
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = list[i]->clone();
		delete list[i];
	}
	delete[] list;
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
	if(list!=NULL)
		delete[] list;
	
}
Product* Catalogue::operator[](size_t idx){
	if (idx >= this->size)
		throw "Over indexed";
	return list[idx];
}
//case insensitive find function for finding substring
bool insFind(const std::string& sourceStr, const std::string& subStr);
//Return an array of pointers that meet the criteria
//Pointer must be deleted manually!
Product** Catalogue::Search(std::string criteria) {
	Product** searchRes=0;
	size_t rSize = 0;
	for (size_t i = 0; i < size; i++) {
		if (insFind(list[i]->getName(),criteria)) {
			Product** temp = 0;
			bool copied = false;
			if (rSize > 0) {
				temp = new Product * [rSize];
				for (size_t j = 0; j < rSize; j++) {
					temp[j] = searchRes[j];
				}
				copied = true;
			}
			if (rSize != 0)
				delete[] searchRes;
			searchRes = new Product * [++rSize];
			if (rSize > 1 && copied) {
				for (size_t j = 0; j < rSize - 1; j++) {
					searchRes[j] = temp[j];
				}
				delete[] temp;
			}
			
			searchRes[rSize - 1] = list[i];
			
		}
		
	}
	return searchRes;
	
}
void Catalogue::OrderBy(OrderReq r, bool reversed) {
	switch (r)
	{
	case Price:
		std::sort(&list[0], &list[size], [&r = reversed](Product* lhs, Product* rhs) {return r ? lhs->getPrice() > rhs->getPrice() : lhs->getPrice() < rhs->getPrice(); });
		break;
	case Name:
		std::sort(&list[0], &list[size], [&r = reversed](Product* lhs, Product* rhs) {return r ? (lhs->getName() > rhs->getName()) : (lhs->getName() < rhs->getName()); });
		break;
	default:
		throw "Rossz rendezési kritérium!";
		break;
	}
}



Catalogue::Iterator Catalogue::begin()const {
	return Catalogue::Iterator(list);
}
Catalogue::Iterator Catalogue::end()const {
	return Catalogue::Iterator(&list[size]);
}

//Iterator
Catalogue::Iterator& Catalogue::Iterator::operator++() {
	++pointer;
	return *this;
}
Catalogue::Iterator& Catalogue::Iterator::operator++(int) {
    Iterator tmp(*this);
	operator++();
	return tmp;
}
bool Catalogue::Iterator::operator==(const Iterator& rhs) {
	return rhs.pointer == pointer;
}
bool Catalogue::Iterator::operator!=(const Iterator& rhs) {
	return !(operator==(rhs));
}
Product& Catalogue::Iterator::operator*() {
	return **pointer;
}


//Case insensitive string::find
bool insFind(const std::string& sourceStr, const std::string& subStr)
{
	//iterates through the two strings using the lambda function
	auto it = std::search(
		sourceStr.begin(), sourceStr.end(),
		subStr.begin(), subStr.end(),
		[](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
	);
	return (it != sourceStr.end());
}