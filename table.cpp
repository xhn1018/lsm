#include"table.h"
#include <fstream> 
#include<iostream>
table::table() {

	size = 0;

};
bool table::add(int key, std::string value) {                                                                                                     

	if (size >= pow(10, tablelevel) * 100) {
		std::cout << size << std::endl;
		return 0;
	}
	else {
		KeyList[size] = key;
		size = size + 1;
		meta.insert(std::pair<int, std::string>(key, value));
		return 1;
	}
}


void table::save() {

	std::ofstream of("table_" + std::to_string(tablelevel) + "_" + std::to_string(num));

	for (const auto &i : meta) {
		of << i.first << ' ' << i.second << std::endl;

	}

	of.close();

	std::ofstream of2("metadata" + std::to_string(tablelevel), std::ios::app);

	for (int i = 0; i < size; i++) {
		of2 << KeyList[i] << ' ' << num << std::endl;
	}

	of2.close();
}
