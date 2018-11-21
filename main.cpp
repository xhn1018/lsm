#include<iostream>
#include<thread>
#include<time.h>
#include<thread>
#include"memtable.h"
#include <cstdlib> 
#include"table.h"
#include"skiplist.h"
#include"compaction.h"
#include<mutex>
std::mutex memtx;
void t1(SkipList *S) {
	srand (time(0));
	for (int i = 0; i < 10; i++)
	{
		int a = rand() % 100;
		std::cout<<a<<std::endl;
		S->insert(a, std::to_string(a));
	}
}
void t2(memtable *m) {
	srand(time(0));
	for (int i = 0; i < 10000;i++) {
		int a = rand() % 100;
		m->putvalue(a, std::to_string(a));

	}
}

void memtodisk( memtable ** k) {

	while (1) {
		memtable *fl;

		fl = *k;
		
		int menum = 0;
		while (fl->prev != NULL) {
			fl = fl->prev;
			menum++;
		}
		if (menum > 4) {
			
			
			skiptotable(*(fl->List));
			fl->next->prev = NULL;
			delete(fl);
			
		}

			for (int i = 0; i < 4; i++) {
				int j, k = 0;
				std::ifstream m2("metadata" + std::to_string(i));
				while (m2 >> j)  m2 >> k;
				m2.close();
				if (k > 100 / (i + 1)) {
					compaction(i);
					break;
				}
			}
	}
}
void write(memtable **b) {
	for (int i = 0; i < 500000; i++) {
		
		writeoperation(b, i, "123");
		
	}

}
void read(memtable **b) {
	for (int i = 0; i < 500000; i++) {
		std::string a=readoperation(*b, i);	
		if (a != "123") {
			std::cout << "error" << std::endl;
		}
	}

}
int main() {
	SkipList a;
	memtable *current;
	current = new(memtable);
	memtable *b;
	b = current;
	/*for (int i = 0; i < 70000; i++) {
		writeoperation(&b, i, "123");
	}*/
	std::thread t5(write, &b);
	std::thread t4(write, &b);
	std::thread t2 (write,&b);
	//std::thread t3(read, &b);
	std::thread t1(memtodisk,&b);
	t2.detach();
	t5.detach();
	t4.detach();
	//t3.detach();
	Sleep(1000);
	t1.join();
	std::cout << b->prev->List->search(56000) << std::endl;
	std::cout<<readoperation(b,4) << std::endl;
	system("pause");
}
