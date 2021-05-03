#include "products.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "memtrace.h"

///Overloads the >> to save the object to file
std::ifstream& operator>>(std::ifstream& savefile, Product& rhs) {
	if (!savefile.is_open())
	{
		savefile.open("savefile.txt");
	}
	std::string name; double price; std::string desc; std::string manuf;
	std::string temp;
	std::getline(savefile, temp, ':');
	std::getline(savefile, name, ';');
	std::getline(savefile, temp, ':');
	savefile >> price;
	std::getline(savefile, temp, ':');
	std::getline(savefile, desc, ';');
	std::getline(savefile, temp, ':');
	std::getline(savefile, manuf, ';');
	rhs = Product(name, price, manuf, desc);
	return savefile;
}

void Product::print() {
	std::cout << "Product Name: " << name << "\tPrice: " << price <<
		"\nDescription:" << std::endl << "\t" << dscrpt;
}
std::string Product::serializeObj() const {
	std::ostringstream sStream;
	sStream << "name:" << name << ";price:" << price << ";description:" << dscrpt << ";manufacturer:" << manufacturer << ";";
	return sStream.str();
}

Product* Product::clone() {
	Product* p = new Product(*this);
	return p;
}
std::string Product::getObjType() const {
	return "PRODUCT_OBJ";
}

std::string Product::getManufacturer() const { return manufacturer; }
std::string Product::getName() const { return name; }
std::string Product::getDescription() const { return dscrpt; }
double Product::getPrice() const { return price; }

void Product::setName(std::string s) { name = s; }
void Product::setDescription(std::string s) { dscrpt = s; }
void Product::setManuf(std::string s) { manufacturer = s; }
void Product::setPrice(double p) { price = p; }


Product::Product(const Product& p) :name(p.name), price(p.price), dscrpt(p.dscrpt), manufacturer(p.manufacturer) {};
Product::Product(std::string name, double price, std::string manuf, std::string descript) :name(name), price(price), dscrpt(descript), manufacturer(manuf) {}
Product::Product() : name("Unnamed Product"), price(0), dscrpt("There is no description for this item!") {}

bool Product::operator==(Product& rhs) {
	if (rhs.price == price && rhs.manufacturer == manufacturer
		&& rhs.name == rhs.name)
		return true;
	return false;
}
bool Product::operator!=(Product& rhs) {
	return !(Product::operator==(rhs));
}