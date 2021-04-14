#include <iostream>
#include "products.h"
#include "Memory.h"
#include "processor.h"
#include "Videocard.h"
#include "Computer.h"
#include "catalogue.h"

int main(){
	Product t = Product("Car", 12, "Nooooo");
	t.print();
}