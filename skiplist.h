#pragma once
#include <cstdlib> 
#include<string>
#include<mutex>
#ifndef SKIPLIST_H
#define SKIPLIST_H
#define maxlevel  1000



#define newnode(n)((SkipListnode*)malloc(sizeof(SkipListnode)+n*sizeof(SkipListnode*)))

struct SkipListnode {

	int key;
	char value[512];
	SkipListnode *nextnode[1];
};

SkipListnode* create_node(int level, int key, std::string val);

class SkipList {

private:
	int depth;
	int randomVal();
public:
	SkipList();
	int size;
	SkipListnode *head;
	void insert(int key, std::string value);
	std::string search(int key);
	void remove(int key);
};

#endif // !

