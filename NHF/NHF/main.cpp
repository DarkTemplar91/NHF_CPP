#include <iostream>
#include "products.h"
#include "Memory.h"
#include "processor.h"
#include "Videocard.h"
#include "Computer.h"
#include "catalogue.h"
#include <fstream>

int main(){
	Product p1 = Product("PlayStation 5", 500, "Sony", "The newest member of the PlayStation family");
	std::ofstream savefile;
	savefile << p1;
	Product p2;
	std::ifstream inp;
	inp >> p2;
	
}