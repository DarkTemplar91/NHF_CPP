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
	Product(std::string name, double price, std::string manuf, std::string descript="There is no description for this item!") :name(name), price(price), dscrpt(descript),manufacturer(manuf) {}
	Product() : name("Unnamed Product"), price(0), dscrpt("There is no description for this item!") {}
	
	std::string getManufacturer() const { return manufacturer; }
	std::string getName() const { return name; }
	std::string getDescription() const { return dscrpt; }
	double getPrice() const{ return price; }

	void setName(std::string s) { name = s; }
	void setDescription(std::string s) { dscrpt = s; }
	void setManuf(std::string s) { manufacturer = s; }
	void setPrice(double p) { price = p; }
	///Prints out basic data of a product
	virtual void print() {
		std::cout << "Product Name: " << name << "\tPrice: " << price <<
			"\nDescription:" << std::endl << "\t" << dscrpt;
	}
	///Overloads the << operator to save the product
	virtual std::ostream& operator<<(std::ostream& os) {

	}
	///Overloads the >> to load the serialized product
	virtual std::istream& operator>>(std::istream& is) {

	}
	virtual Product* clone() {
		Product* p = new Product(*this);
		return p;
	}
	
};
#endif