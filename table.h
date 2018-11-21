#pragma once
#include<string>
#include<cmath>
#include"skiplist.h"
#include<map>
#ifndef TABLE_H
#define TABLE_H
class table {

public:
	std::map<int, std::string> meta;
	int KeyList[10000];
	table();
	bool add(int key, std::string value);
	void save();
	int tablelevel;
	int num;

private:
	int size;
};

#endif
