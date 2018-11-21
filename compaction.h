#pragma once
#include"table.h"
#include"skiplist.h"
#include"windows.h"
#include"fstream"
#ifndef COMPACTION_H
#define COMPACTION_H
void skiptotable(SkipList a);

std::string readdisk(int level, int key);

void compaction(int level);
#endif
//void compaction(int level k);