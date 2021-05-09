#include "catalogue.h"
#include <string>
#include <algorithm>
#include "memtrace.h"

Catalogue::Catalogue() :size(0){}
Catalogue::Catalogue(Product** list,size_t s) : list(list), size(s){}
size_t Catalogue::getSize()const {
	return size;
}


/// <summary>
/// Adds the clone of the object to the list.
/// If the product is already in the catalogue, then throws an error!
/// </summary>
/// <param name="p"></param> Product to store.
void Catalogue::Add(Product* p) {
	
	//Checking if the list already containt the product.
	for (size_t i = 0; i < size; i++) {
		if (*p == *list[i])
		{
			delete p;
			throw "The catalogue already contains the given product. Try incrementing instead!";
		}
	}

	Product** temp = new Product *[++size];
	//temp array for storing the values,
	//so they are not lost after resizing the array.
	//The size is +1 than the original
	for (size_t i = 0; i < size - 1; i++) {
		//Places the clone into the array
		temp[i] = list[i]->clone();
		//deletes the object after cloning it.
		delete list[i];
	}
	//Storing the new product in a the end of a new array.
	temp[size - 1] = p->clone();
	delete[] list;
	delete p;
	list = temp;
}
/// <summary>
/// Iterates through the list and saves all the objects to a file
/// </summary>
/// <param name="path"></param> Path to save to
void Catalogue::Save(std::string path)const {
	std::ofstream savefile;
	savefile.open(path);
	

	for (size_t i = 0; i < size; i++) {
		if (!savefile.is_open())
			savefile.open(path, std::ios_base::app);

		//casts the object to the appropriate type
		//Otherwise it would call the Product::SerializeObj() in the << function
		switch (list[i]->getObj_t())
		{
		case obj_t::Product:
			savefile << *list[i];
			break;
		case obj_t::Storage:
			savefile << (Storage&)*list[i];
			break;

		case obj_t::RAM:
			savefile << (RAM&)*list[i];
			break;

		case obj_t::HDD:
			savefile << (HDD&)*list[i];
			break;
		case obj_t::SSD:
			savefile << (SSD&)*list[i];
			break;

		case obj_t::MB:
			savefile << (Motherboard&)*list[i];
			break;
		case obj_t::CPU:
			savefile << (CPU&)*list[i];
			break;
		case obj_t::GPU:
			savefile << (GPU&)*list[i];
			break;
		case obj_t::PC:
			savefile << (PC&)*list[i];
			break;
		case obj_t::NONE:
			throw "Nem megfelelő objektum típus!";
				break;
		default:
			throw "Valami elromlott!";
			break;
		
		}
		
	}
	savefile.close();
}
/// <summary>
/// Loads the objects into the catalogue from file
/// </summary>
/// <param name="path"></param>
void Catalogue::Load(std::string path) {
	obj_t type=obj_t::GPU;
	std::ifstream s;
	s.open(path);
	s >> type;
	std::string temp;
	//At each iteration, it reads in a obj_t variable, that determines what the following object is
	//Depending on the value, it calls the appropriate class's >> function.
	while (type!=obj_t::NONE) {
		if(!s.is_open())
			s.open(path);
		switch (type)
		{
		case obj_t::Product:
		{
			Product p;
			s >> p;
			std::getline(s, temp, '}');
			std::getline(s, temp, '\n');
			Add(p.clone());
			break;
		}
		case obj_t::Storage:
		{
			Storage st;
			s >> st;
			Add(st.clone());
			break;
		}
		case obj_t::RAM:
		{	RAM r;
		s >> r;
		std::getline(s, temp, '}');
		Add(r.clone());
		break;
		}
		case obj_t::HDD:
		{
			HDD hdd;
			s >> hdd;
			std::getline(s, temp, '}');
			Add(hdd.clone());
			break;
		}
		case obj_t::SSD:
		{
			SSD ssd;
			s >> ssd;
			std::getline(s, temp, '}');
			Add(ssd.clone());
			break;
		}
		case obj_t::MB:
		{
			Motherboard mb;
			s >> mb;
			std::getline(s, temp, '}');
			Add(mb.clone());
			break;
		}
		case obj_t::CPU:
		{
			CPU cpu;
			s >> cpu;
			std::getline(s, temp, '}');
			Add(cpu.clone());
			break;
		}
		case obj_t::GPU:
		{
			GPU gpu;
			s >> gpu;
			std::getline(s, temp, '}');
			Add(gpu.clone());
			break;
		}
		case obj_t::PC:
		{
			PC pc;
			s >> pc;
			Add(pc.clone());
		}
			break;
		case obj_t::NONE:
			break;
		default:
			type = obj_t::NONE;
			break;
		}
		if(type!=obj_t::NONE)
			s >> type;

	}
	
}



/// <summary>
/// Removes the object from the list if the two objects' attributes are identical
/// </summary>
/// <param name="p"></param> Pointer to the product to compare with.
void Catalogue::Remove(Product* p) {
	Product** temp = new Product * [--size];
	bool found = false;
	for (size_t i = 0; i < size + 1; i++) {
		if (*p == *list[i]) {
			found = true;
			delete p;
			Product* t = list[i];
			list[i] = list[size];
			list[size] = t;
			delete list[size];
			break;
		}
	}
	if (!found)
	{
		//If there were no object found then the temp array is not needed.
		//Terminates the object earlier.
		delete[] temp;
		return;
	}

	//Copies the array's element to the new array.
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = list[i]->clone();
		delete list[i];
	}
	delete[] list;
	list = temp;
}

/// <summary>
/// Clears the catalogue by freeing up all of the allocated memory
/// </summary>
void Catalogue::Clear() {
	for (size_t i = 0; i < size; i++) {
		if (list[i] != nullptr) {
			delete list[i];
			list[i] = nullptr;
		}
	}
	size = 0;
	
}
Catalogue::~Catalogue() {
	Clear();
	if(list!=NULL)
		delete[] list;
	
}
/// <summary>
/// Overloaded [] operator
/// Return the element in the Catalogue at the given index.
/// </summary>
/// <param name="idx"></param>
/// <returns></returns>
Product* Catalogue::operator[](size_t idx)const{
	if (idx >= this->size)
		throw std::out_of_range("Over indexed");
	return list[idx];
}


//case insensitive find function for finding substring
bool insFind(const std::string& sourceStr, const std::string& subStr);

//Return an array of pointers that meet the criteria
//Pointer must be deleted manually!
Product** Catalogue::Search(std::string criteria)const {
	Product** searchRes=0;
	size_t rSize = 0;
	for (size_t i = 0; i < size; i++) {
		if (insFind(list[i]->getName(),criteria)) {
			Product** temp = 0;
			bool copied = false;
			if (rSize > 0) {
				temp = new Product * [rSize];
				for (size_t j = 0; j < rSize; j++) {
					temp[j] = searchRes[j];
				}
				copied = true;
			}
			if (rSize != 0)
				delete[] searchRes;
			searchRes = new Product * [++rSize];
			if (rSize > 1 && copied) {
				for (size_t j = 0; j < rSize - 1; j++) {
					searchRes[j] = temp[j];
				}
				delete[] temp;
			}
			
			searchRes[rSize - 1] = list[i];
			
		}
		
	}
	return searchRes;
	
}
/// <summary>
/// Functor for comparison
/// </summary>
struct lessOrMore {
	bool reversed;
	OrderReq req;
	lessOrMore(bool reversed, OrderReq r) :reversed(reversed), req(r) {}
	template<class T>
	bool operator()(T* p1, T* p2)const {
		if (req == OrderReq::Price)
		{
			if (reversed)
				return p1->getPrice() > p2->getPrice();
			return p1->getPrice() < p2->getPrice();
		}
		else {
			if (reversed)
				return p1->getName() > p2->getName();
			return p1->getName() < p2->getName();
		}
	
	}
};
/// <summary>
/// Sorts the Catalogue with std::sort
/// Uses functor
/// </summary>
/// <param name="r"></param>
/// <param name="reversed"></param>
void Catalogue::OrderBy(OrderReq r, bool reversed)const {
	lessOrMore comp = lessOrMore(reversed, r);
	std::sort(&list[0], &list[size], comp);
}



Catalogue::Iterator Catalogue::begin()const {
	return Catalogue::Iterator(list);
}
Catalogue::Iterator Catalogue::end()const {
	return Catalogue::Iterator(&list[size]);
}

//Iterator
Catalogue::Iterator& Catalogue::Iterator::operator++() {
	++pointer;
	return *this;
}
bool Catalogue::Iterator::operator==(const Iterator& rhs)const {
	return rhs.pointer == pointer;
}
bool Catalogue::Iterator::operator!=(const Iterator& rhs)const {
	return !(operator==(rhs));
}
Product& Catalogue::Iterator::operator*() {
	return **pointer;
}


/// <summary>
/// Help function for case insensitive find
/// Returns true if the string includes the given substring
/// </summary>
/// <param name="sourceStr"></param> String to search in
/// <param name="subStr"></param> String searched
/// <returns></returns>	Returns if it includes the substring
bool insFind(const std::string& sourceStr, const std::string& subStr)
{
	//iterates through the two strings using the lambda function
	//The lambda function just converts all characters to capital case, so it can compare them
	auto it = std::search(
		sourceStr.begin(), sourceStr.end(),
		subStr.begin(), subStr.end(),
		[](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
	);
	return (it != sourceStr.end());
}