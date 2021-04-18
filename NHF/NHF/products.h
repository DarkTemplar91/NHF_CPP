#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Product {
	std::string name;
	double price;
	std::string dscrpt;
	std::string manufacturer;
public:
	Product(std::string name, double price, std::string manuf, std::string descript = "There is no description for this item!") :name(name), price(price), dscrpt(descript), manufacturer(manuf) {}
	Product() : name("Unnamed Product"), price(0), dscrpt("There is no description for this item!") {}

	std::string getManufacturer() const { return manufacturer; }
	std::string getName() const { return name; }
	std::string getDescription() const { return dscrpt; }
	double getPrice() const { return price; }

	void setName(std::string s) { name = s; }
	void setDescription(std::string s) { dscrpt = s; }
	void setManuf(std::string s) { manufacturer = s; }
	void setPrice(double p) { price = p; }
	///Prints out basic data of a product
	virtual void print() {
		std::cout << "Product Name: " << name << "\tPrice: " << price <<
			"\nDescription:" << std::endl << "\t" << dscrpt;
	}
	virtual std::string serializeObj() {
		std::ostringstream sStream;
		sStream <<"name:" <<name << ";price:" << price << ";description:" << dscrpt << ";manufacturer:" << manufacturer<<";";
		return sStream.str();
	}
	
	virtual Product* clone() {
		Product* p = new Product(*this);
		return p;
	}


};
///Overloads the << operator to save the product
 inline std::ofstream& operator<<(std::ofstream& savefile, Product& rhs){
	//Maybe append later instead?
	if(!savefile.is_open())
		savefile.open("savefile.txt");
	savefile << "PRODUCT_OBJ" << "\n{";
	savefile << "\n" << rhs.serializeObj();
	savefile << "\n}";
	savefile.close();
	return savefile;
}
 ///Overloads the >> to load the serialized product
 
 inline std::ifstream& operator>>(std::ifstream& savefile, Product& rhs) {
	 if (!savefile.is_open())
	 {
		 savefile.open("savefile.txt");
	 }
	 std::string name; double price; std::string desc; std::string manuf;
	 std::string temp;
	 std::getline(savefile, temp, ':');
	 std::getline(savefile,name ,';');
	 std::getline(savefile, temp, ':');
	 savefile >> price;
	 std::getline(savefile, temp, ':');
	 std::getline(savefile, desc, ';');
	 std::getline(savefile, temp, ':');
	 std::getline(savefile, manuf, ';');
	 std::getline(savefile, temp, '}');
	 rhs = Product(name,price, manuf, desc);
	 return savefile;
 }
#endif