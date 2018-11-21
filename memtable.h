#pragma once
#include <cstdlib> 
#include<iostream>
#include "skiplist.h"

#ifndef MEMTABLE_H
#define MEMTABLE_H


#define newnode(n)((SkipListnode*)malloc(sizeof(SkipListnode)+n*sizeof(SkipListnode*)))

class memtable {

public:

	memtable *next;
	memtable *prev;
	memtable();
	std::string getvalue(int key);
	bool putvalue(int key, std::string value);
	void deletevalue(int key);
	int  fresh;
	SkipList *List;

private:
	std::mutex mtx;

};
void writeoperation(memtable** current, int key, std::string value);
std::string readoperation(memtable* current, int key);
#endif
