#ifndef CATALOGUE_H
#define CATALOGUE_H

#include "products.h"
#include "Memory.h"
#include "Motherboard.h"
#include "Videocard.h"
#include "processor.h"
#include "Computer.h"
#include "memtrace.h"

/// <summary>
/// Enumerator used for ordering the catalogue
/// </summary>
enum class OrderReq{Price, Name};

/// <summary>
/// Catalogue class
/// An instance of Catalogue stores and manages severak Products
/// The Products are stored in a dynamically allocated array using a Product pointer array.
/// </summary>
class Catalogue {
	Product** list{};		///The dynamically allocated array of Product pointers
	size_t size = 0;	///Size of the array

public:
	/// <summary>
	/// Adds Product to the catalogue.
	/// If the product is already in the catalogue, it throws an error
	/// </summary>
	/// <param name="p"></param> Product pointer pointing to product that needs to be added
	void Add(Product* p);

	/// <summary>
	/// Removes the product from the catalogue if it has the same attributes
	/// as the Product passed as a pointer.
	/// Alternatively, if the pointer is actually included, it removes it. 
	/// </summary>
	/// <param name="p"></param> Pointer to the product that need removing
	void Remove(Product* p);

	/// <summary>
	/// Clears the catalogue, freeing all the allocated pointers
	/// and resetting the size to 0.
	/// </summary>
	void Clear();

	/// <summary>
	/// Saves the catalogue to a file given by the 'path' variable.
	/// It uses the classes' overloaded serializeObj method
	/// </summary>
	/// <param name="path"></param> Path of save file
	void Save(const std::string path)const;

	/// <summary>
	/// Loads the catalogue from a file by creting objects from the data read
	/// and placing them into the catalogue
	/// </summary>
	/// <param name="path"></param> Path to the file to read from
	void Load(const std::string path);

	/// <summary>
	/// Searches the catalogue and returns with an array of pointers
	/// pointing to the products that meet the criteria.
	/// It searches by name, substring included, case insensitive
	/// </summary>
	/// <param name="criteria"></param> Criteria: the substring to search for
	/// <returns></returns> Array of Product pointers with product that met the criteria
	Product** Search(std::string criteria)const;

	/// <summary>
	/// Orders the catalogue by name or price.
	/// Price can be sorted by high to low
	/// Name can be sorted alphabetically or reversed
	/// </summary>
	/// <param name="r"></param>   Type to sort by.
	/// <param name="rev"></param> Reverse order?
	void OrderBy(OrderReq r, bool rev)const;
	
	size_t getSize()const;	///Return the size of the catalogue

	/// <summary>
	/// Overloads the [] operator for Catalogue.
	/// It returns the n-th element of the list enwrapped in the Catalogue
	/// Throws error if it is out of bounds
	/// </summary>
	/// <param name="idx"></param> The index of the element to return
	/// <returns></returns> The n-th element of the catalogue
	Product* operator[](size_t idx)const;
	
	Catalogue();
	Catalogue(Product** list, size_t s);
	~Catalogue();

	//Iterator class pre-declaration
	class Iterator;

	/// <summary>
	/// Returns an iterator pointing to the first element of the list
	/// </summary>
	/// <returns></returns> Iterator type
	Iterator begin()const;
	/// <summary>
	/// Returns an iterator pointing to the memory place after the last element of the list
	/// </summary>
	/// <returns></returns> Iterator
	Iterator end()const;

	class Iterator {
		Product** pointer; ///Pointer to the pointer of the list's element
	public:
		Iterator(Product** p) :pointer(p) {}
		/// <summary>
		/// Overloaded preincrement operator for incrementing the stored pointer.
		/// </summary>
		/// <returns></returns> Returns an Iterator (itself) pointing to the next element
		Iterator& operator++();

		
		bool operator==(const Iterator& rhs)const;	///Overloaded equality operator so it can be used for foreach
		bool operator!=(const Iterator& rhs)const;   ///Inverse of equality operator. Used for the loop's stop condition
		Product& operator*();					///Dereferences the pointer, and returns the element which it points to

	};

};

#endif // !CATALOGUE_H
