#ifndef CATALOGUE_H
#define CATALOGUE_H

#include "products.h"
#include "memtrace.h"

class Catalogue {
	Product** list;
	size_t size = 0;
public:

	
	void Add(Product* p);

	template<class T>
	void Add(T& t);
	

	void Remove(Product* p);
	void Clear();
	void Save(const std::string path)const;
	void Load(const std::string path)const;
	Product* Search(std::string criteria)const;
	void OrderBy(std::string crieteria);
	size_t getSize() { return size; }
	Product* operator[](size_t idx);
	Catalogue();
	Catalogue(Product** list, size_t s);
	~Catalogue();

};

#endif // !CATALOGUE_H
