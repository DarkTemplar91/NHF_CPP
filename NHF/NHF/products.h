#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "memtrace.h"

//TODO: Change to append
//Saves the object to a file.
template<class T>
inline std::ofstream& operator<<(std::ofstream& savefile, T& rhs) {
	if (!savefile.is_open())
		savefile.open("savefile.txt");
	savefile << rhs.getObjType();
	//Const char[] type does not have a .getObjType function, so I have to use .write,
	//as << would cause an error!
	savefile.write("\n{", 2);
	savefile.write("\n",1);
	savefile << rhs.serializeObj();
	savefile.write("\n}",2);
	savefile.close();
	
	return savefile;
}



class Product {
	std::string name;
	double price;
	std::string dscrpt;
	std::string manufacturer;
public:
	Product(const Product& p) :name(p.name), price(p.price), dscrpt(p.dscrpt), manufacturer(p.manufacturer) {};
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
	virtual std::string serializeObj() const{
		std::ostringstream sStream;
		sStream <<"name:" <<name << ";price:" << price << ";description:" << dscrpt << ";manufacturer:" << manufacturer<<";";
		return sStream.str();
	}
	
	virtual Product* clone() {
		Product* p = new Product(*this);
		return p;
	}
	virtual std::string getObjType() const{
		return "PRODUCT_OBJ";
	}


};


 ///Overloads the >> to save the object to file
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
	 rhs = Product(name,price, manuf, desc);
	 return savefile;
 }

 
 
 


#endif