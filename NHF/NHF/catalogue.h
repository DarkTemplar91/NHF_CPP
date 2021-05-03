#ifndef CATALOGUE_H
#define CATALOGUE_H

#include "products.h"
#include "memtrace.h"

enum OrderReq{Price, Name};

class Catalogue {
	Product** list;
	size_t size = 0;

public:

	void Add(Product* p);
	void Remove(Product* p);
	void Clear();

	void Save(const std::string path)const;
	void Load(const std::string path)const;

	Product** Search(std::string criteria);
	void OrderBy(OrderReq r, bool rev);
	
	size_t getSize();
	Product* operator[](size_t idx);
	Catalogue();
	Catalogue(Product** list, size_t s);
	~Catalogue();

	class Iterator;

	Iterator begin()const;
	Iterator end()const;

	class Iterator {
		Product** pointer;
	public:
		Iterator(Product** p) :pointer(p) {}
		Iterator& operator++();
		Iterator& operator++(int);
		bool operator==(const Iterator& rhs);
		bool operator!=(const Iterator& rhs);
		Product& operator*();

	};

};

#endif // !CATALOGUE_H
