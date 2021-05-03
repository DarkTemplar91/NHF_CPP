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
	Product(const Product& p);
	Product(std::string name, double price, std::string manuf, std::string descript = "There is no description for this item!");
	Product();

	std::string getManufacturer() const;
	std::string getName() const;
	std::string getDescription() const;
	double getPrice() const;

	void setName(std::string s);
	void setDescription(std::string s);
	void setManuf(std::string s);
	void setPrice(double p);
	///Prints out basic data of a product
	virtual void print();
	virtual std::string serializeObj()const;
	
	virtual Product* clone();
	virtual std::string getObjType() const;

	virtual bool operator==(Product& rhs);
	virtual bool operator!=(Product& rhs);

	virtual ~Product() {}

};


 ///Overloads the >> to save the object to file
std::ifstream& operator>>(std::ifstream& savefile, Product& rhs);

 
 
 


#endif