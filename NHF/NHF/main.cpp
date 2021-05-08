#include <iostream>
#include "products.h"
#include "Memory.h"
#include "processor.h"
#include "Videocard.h"
#include "Computer.h"
#include "catalogue.h"
#include <fstream>
#include "gtest_lite.h"
#include "memtrace.h" 


int main() {
	//Inventory management
	TEST(PRODUCTS_H, inv){
		Product p = Product(); //inv=0
		EXPECT_EQ(0, p.getAmount());
		p.increaseStock(12);	//inv=12
		EXPECT_EQ(p.getAmount(), 12) << "Nem jó a mennyiség!";
		EXPECT_ANY_THROW(p.decreaseStock(20)) << "Hibát vártunk.";	//Product at stock cannot be less than zero
		Product pClone = p; 
		EXPECT_TRUE(pClone == p);
		Product pc = Product("Termkék", 100, "Cég", "Leírás", 5);
		EXPECT_EQ(5, pc.getAmount());
	}END
	//Testing the basic constructors and assignment operators
	TEST(PRODUCTS_H, ) {
		Product pc = Product("Termkék", 100, "Cég", "Leírás", 5);
		Product eq;
		eq = pc;
		EXPECT_EQ(pc.getName(), eq.getName());
		GPU g1 = GPU("GPU", 300, "Manuf", "gpu", 5, 5, 2000, 1000, 12, 300);
		GPU g2;
		g2 = g1;
		EXPECT_TRUE(g1 == g2);
		GPU g3 = GPU("GPU3",600,"Different manuf", "different gpu",2,2,1000,500,12,300);
		g3 = g2;
		EXPECT_TRUE(g3 == g1);
	}END
	//Saving the product to a file and reading it back.
	//Only checks individual objects.
	//For loading in multiple products, see later.
	TEST(Product, Read/Write_file) {
		std::remove("savefile.txt");
		Product p1 = Product("PlayStation 5", 500, "Sony", "The newest member of the PlayStation family");
		std::ofstream savefile;
		savefile << p1;
		if (savefile.is_open())
			savefile.close();
		Product p2;
		std::ifstream inp;
		inp >> p2;
		if (inp.is_open())
			inp.close();
		EXPECT_EQ(p1.getName(), p2.getName()) << "Név hibás!";
		EXPECT_EQ(p1.getDescription(), p2.getDescription()) << "Leírás hibás!";
		EXPECT_EQ(p1.getManufacturer(), p2.getManufacturer()) << "Gyártó hibás!";
		EXPECT_EQ(p1.getPrice(), p1.getPrice());
		std::remove("savefile.txt");	//File has to be removed, because << appends to the file, but >> starts from the beggining.

	}END
	//Saving and reading in derived class objects
	TEST(PROCESSOR_H, READ) {
		CPU c1 = CPU("Ryzen 5", 300, "6 core powerful gaming processor.", "AMD", "5600X", 120, socket::AMD_AM4, 3700, 6, 12, 3, false);
		std::ofstream savefile;
		savefile << c1;
		std::ifstream inp;
		CPU c2;
		inp >> c2;
		EXPECT_EQ(c1.getName(), c2.getName()) << "Hiba az öröklődésnél!";
		EXPECT_EQ(c1.getCoreCount(), c2.getCoreCount());
		if (inp.is_open()) //inp has to be closed so the file can be deleted. The catalogue's load function handle's this on its own
			inp.close();
		std::remove("savefile.txt");

	}END

	RAM r1, r2;
	Motherboard m1,m2;
	GPU g1,g2;
	//Tests multiple inheritance and file I/O funcs
		TEST(CLASSES, cons) {
		r1 = RAM("HyperX Fury 2x8GB", 100, "HyperX RAM", "Kingston", 16, ByteUnit::gigabyte, MemoryType::DDR4, 3200, 14, 1.2);
		m1 = Motherboard("MSI B550 Tomahawk", 120,"MSI","B550 motherboard from MSI","B550",socket::AMD_AM4,64, 4000, 6, 4, 3);
		g1 = GPU("EVGA RTX2060 KO", 300, "EVGA", "Gaming GPU", 1, 1, 2400, 7000, 6, 300);
		std::ofstream savefile;
		std::ifstream inp;
		savefile << r1;
		RAM r2;
		inp >> r2;
		if (inp.is_open())
			inp.close();
		std::remove("savefile.txt");
		EXPECT_EQ(r1.getlatency(), r2.getlatency());
		Motherboard m2;
		savefile << m1;
		inp >> m2;
		if (inp.is_open())
			inp.close();
		std::remove("savefile.txt");
		EXPECT_EQ(m1.getPorts(), m2.getPorts());
		GPU g2;
		savefile << g1;
		inp >> g2;
		EXPECT_EQ(g1.getHDMIports() , g2.getHDMIports());
	}END

	TEST(CATALOGUE_H, create) {
		Catalogue c = Catalogue();
		c.Add(r1.clone());
		c.Add(r2.clone());
		c.Add(g2.clone());
		EXPECT_ANY_THROW(c[5]) <<"Hibát várt!";
		EXPECT_EQ(c.getSize(), (size_t)3);
		c.Remove(g2.clone());
		EXPECT_EQ(c.getSize(), (size_t)2);
		
	}END
	
	TEST(CATALOGUE_H, .search) {
		Catalogue c = Catalogue();
		c.Add(new GPU("ASUS Strix RTX 3090 OC", 1200, "ASUS", "Extremely powerful gaming GPU", 2, 2, 23, 42421, 45123, 300));
		c.Add(Product("RTX GPU Bracket", 100, "").clone());
		GPU g = GPU("Asus GTX 1650ti", 150, "Asus", "labla", 2, 3, 4532, 654, 6, 8);
		c.Add(g.clone());
		Product** s1 = c.Search("Asus"); //Searching for products with "Asus" in their name 
		Product** s2 = c.Search("RTX");  //...with "RTX" in their name
		EXPECT_EQ(s1[0]->getName(), c[0]->getName());
		EXPECT_EQ(s2[1]->getName(), c[1]->getName());
		delete[] s1; //Search results have to be deleted manually!
		delete[] s2;

	}END
	TEST(CATALOGUE_H, Iterators) {
		Catalogue c = Catalogue();
		int sum = 0;
		srand(0);
		//Creates 30 products with random price
		//Adds them to the catalogue
		for (size_t i = 0; i < 30; i++) {
			std::string s = "Product" + std::to_string(i);
			int price = rand() % 980 + 20;
			c.Add(new Product(s,price,"-"));
			sum += price;
		}
		//Iterates through the catalogue and adds up the price
		int fs = 0;
		for (auto x : c) {
			fs += (int)x.getPrice();
		}
		EXPECT_EQ(sum, fs);
	}END
	//Tests the Catalogue save/load functions
	TEST(CATALOGUE_H, save / load) {
		Catalogue cSave = Catalogue();
		cSave.Add(new Product("Prod1", 100, "-"));
		cSave.Add(new GPU("GPU1", 300, "BrandName", "-", 2, 2, 3000, 7000, 12, 300));
		cSave.Add(new HDD("HDD1", 60, "hard drive", "Kingston",2,ByteUnit::terabyte,5400));
		cSave.Add(new CPU("Ryzen 9 5900x", 500, "cpu", "AMD", "Zen 3", 200, socket::AMD_AM4, 3600, 16, 32, 20, false));
		cSave.Save("stock.txt"); //Saves the catalogue to a .txt file
		Catalogue cLoad = Catalogue(); 
		cLoad.Load("stock.txt"); //Loads the catalogue from file
		EXPECT_EQ(cSave.getSize(), cLoad.getSize());
		EXPECT_EQ(cSave[0]->getName(), cLoad[0]->getName());
		EXPECT_TRUE(*cSave[2] == *cLoad[2]);
		cSave[2]->print();
		std::cout << std::endl;
		cLoad[2]->print();

	}END
	TEST(PC, ) {
		GPU g = GPU("RTX 3090", 1500, "EVGA", "Gaming GPU", 1, 2, 3000, 8000, 24, 400);
		CPU c = CPU("Ryzen 9 5900x",600,"AMD","cpu","Zen 3", 200, socket::AMD_AM4, 4.2, 16, 32, 4, false);
		Product case1 = Product("Generic pc case", 60, "Generic manuf");
		Product psu = Product("1200W PSU", 300, "manuf");
		SSD* s=new SSD("Samsung 970 EVO", 300, "", "Samsung",2,ByteUnit::terabyte);
		RAM r = RAM("HyperX 16 GB 3200 Mhz",200,"Kingston","RAM",16,ByteUnit::gigabyte,DDR4,3200,14,1.3);
		Motherboard mb = Motherboard("MSI B550 Tomahawk", 120, "MSI", "mb", "B550", socket::AMD_AM4, 64, 4200);
		PC pc = PC(g,c,mb,case1,psu,s,r);
		std::ofstream of;
		of.open("pc.txt");
		of << pc;
		if (of.is_open())
			of.close();
		PC p2;
		std::ifstream is;
		is.open("pc.txt");
		is >> p2;
		std::cout << "";

	}END
}