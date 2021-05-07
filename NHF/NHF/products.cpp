#include "products.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "memtrace.h"

///Overloads the >> to load the object from file
std::ifstream& operator>>(std::ifstream& savefile, Product& rhs) {
	if (!savefile.is_open())
	{
		savefile.open("savefile.txt", std::ios_base::app);
	}
	std::string name; double price; std::string desc; std::string manuf;
	std::string temp;  //string used to throw away unwanted characters/lines
	size_t inv;
	std::getline(savefile, temp, ':');	//Reads until ':' after which an attribute follows
	std::getline(savefile, name, ';');	//Reads until ';' which denotes the end of the attribute
	std::getline(savefile, temp, ':');
	savefile >> price;
	std::getline(savefile, temp, ':');
	std::getline(savefile, desc, ';');
	std::getline(savefile, temp, ':');
	std::getline(savefile, manuf, ';');
	std::getline(savefile, temp, ':');
	savefile >> inv;
	rhs = Product(name, price, manuf, desc);
	return savefile;
}

void Product::print() {
	std::cout << serializeObj();
}
std::string Product::serializeObj() const {
	std::ostringstream sStream;
	sStream << "name:" << name << ";price:" << price << ";description:" << dscrpt << ";manufacturer:" << manufacturer << ";inventory:"<<inv<<";";
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
size_t Product::getAmount()const { return inv; }
obj_t Product::getObj_t()const { return t; }

void Product::setName(std::string s) { name = s; }
void Product::setDescription(std::string s) { dscrpt = s; }
void Product::setManuf(std::string s) { manufacturer = s; }
void Product::setPrice(double p) { price = p; }


void Product::increaseStock(size_t i) {
	this->inv += i;
}
void Product::decreaseStock(size_t i) {
	if (inv - i < 0)
		throw "Product in stock cannot be less than 0!";
	inv -= i;
}

Product::Product(const Product& p) :name(p.name), price(p.price), dscrpt(p.dscrpt), manufacturer(p.manufacturer), inv(1),t(obj_t::Product) {};
Product::Product(std::string name, double price, std::string manuf, std::string descript, size_t inv) :name(name), price(price), dscrpt(descript), manufacturer(manuf), inv(inv), t(obj_t::Product) {}
Product::Product() : name("Unnamed Product"), price(0), dscrpt("There is no description for this item!"), inv(0), t(obj_t::Product) {}

bool Product::operator==(Product& rhs) {
	if (rhs.price == price && rhs.manufacturer == manufacturer
		&& rhs.name == rhs.name)
		return true;
	return false;
}
bool Product::operator!=(Product& rhs) {
	return !(Product::operator==(rhs));
}