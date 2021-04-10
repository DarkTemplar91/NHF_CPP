#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <string>
#include <iostream>

class Product {
	std::string name;
	double price;
	std::string dscrpt;
	std::string manufacturer;
public:
	Product(std::string name, double price, std::string descript="There is no description for this item!") :name(name), price(price), dscrpt(descript) {}
	Product() : name("Unnamed Product"), price(0), dscrpt("There is no description for this item!") {}
	
	std::string getManufacturer() const { return manufacturer; }
	std::string getName() const { return name; }
	std::string getDescription() const { return dscrpt; }
	double getPrice() const{ return price; }

	void setName(std::string s) { name = s; }
	void setDescription(std::string s) { dscrpt = s; }
	void setManuf(std::string s) { manufacturer = s; }
	void setPrice(double p) { price = p; }

	
};

inline std::ostream& operator<<(std::ostream& os, Product& rhs) {
	return os << "Product Name: " << rhs.getName() << "\tPrice: " << rhs.getPrice() << 
		"\nDescription:" <<std::endl<<"\t"<<rhs.getDescription();
}

#endif