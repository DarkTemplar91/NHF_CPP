#ifndef CATALOGUE_H
#define CATALOGUE_H

#include "products.h"

class Catalogue {
	Product** list;
	size_t size = 0;
public:
	void Add(Product* p);
	void Remove(Product* p);
	void Clear();
	void Save(const std::string path)const;
	void Load(const std::string path)const;
	Product* Search(std::string criteria)const;
	void Order(std::string crieteria);
	
	Product* operator[](size_t idx);
	Catalogue();
	Catalogue(Product** list, size_t s);
	~Catalogue();

};

#endif // !CATALOGUE_H
