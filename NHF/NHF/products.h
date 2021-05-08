#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "memtrace.h"

/// <summary>
/// Enumerator for the object types
/// </summary>
enum class obj_t{Product,Storage, RAM, HDD, SSD,MB,CPU,GPU,PC, NONE};
std::ifstream& operator>>(std::ifstream& s,obj_t& rhs);

//Template for writing the serialized object to file

/// <summary>
/// Template for writing the serialized object to file
/// </summary>
/// <typeparam name="T"></typeparam>	The object type being saved
/// <param name="savefile"></param>		The  output file stream used for writing to file
/// <param name="rhs"></param>			rhs is the reference to the object being saved
/// <returns></returns>
template<class T>
inline std::ofstream& operator<<(std::ofstream& savefile, T& rhs) {
	//If the file is not opened yet, the function will open/create a default file
	if (!savefile.is_open())
		savefile.open("savefile.txt", std::ios_base::app);
	savefile << rhs.getObjType();
	//Const char[] type does not have a .getObjType function, so I have to use .write,
	//as << would cause unwanted recursion with char[] type
	savefile.write("\n{", 2);
	savefile.write("\n",1);
	savefile << rhs.serializeObj();		//Saves the object to file
	savefile.write("\n}\n",3);
	savefile.close();
	
	return savefile;
}



class Product {
	std::string name;			///Name of the product
	double price;				///Price of the product
	std::string dscrpt;		    ///Description
	std::string manufacturer;   ///The manufacturer
	size_t inv;					///The amount of Product in stock
protected:
	obj_t t;					///The type of the object. Used when reading/writing from/to file.
public:
	/// <summary>
	/// Multiple constructors with different parameters
	/// </summary>
	Product(const Product& p);
	Product(std::string name, double price, std::string manuf, std::string descript = "There is no description for this item!", size_t inventory=1);
	Product();

	std::string getManufacturer() const;	///MAnufacturer getter
	std::string getName() const;			///Name getter
	std::string getDescription() const;		///Description getter
	double getPrice() const;				///Price getter
	size_t getAmount()const;				///Returns tha available stock
	obj_t getObj_t()const;					///Returns the obj_t enum type
	std::string getObjType() const;	///Returns a string with the object type for serialization

	void setName(std::string s);			///Change name
	void setDescription(std::string s);     ///Change description
	void setManuf(std::string s);			///Change Manufacturer
	void setPrice(double p);				///Change price

	
	/// Increases the stock by i
	void increaseStock(size_t i=1);
	/// Decreases the stock by i
	void decreaseStock(size_t i=1);
	
	///Prints out basic data of a product to the output stream
	virtual void print();
	/// Serializes object
	virtual std::string serializeObj()const;
	
	virtual Product* clone();


	virtual bool operator==(Product& rhs);		///Virtual Overloaded == operator for comparison (used when adding to catalogue)
	virtual bool operator!=(Product& rhs);		///Virtual Overloaded != operator (used when adding to catalogue)
	
	/// Virtal destructor
	virtual ~Product() {}

};


 ///Overloads the >> to save the object to file
std::ifstream& operator>>(std::ifstream& savefile, Product& rhs);

 
 
 


#endif