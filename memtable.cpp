
#include"memtable.h"
#include"compaction.h"
std::mutex mmtx;
memtable::memtable() {

	List = new(SkipList);
	fresh = 1;
	next = NULL;
	prev = NULL;
};


std::string memtable::getvalue(int key) {

	std::string k = List->search(key);

	/*if (k == "#"&&prev!=NULL) {
		k = prev->getvalue(key);
	}*/
	return k;
};

bool memtable::putvalue(int key, std::string value) {

	if (List->size < 10000) {

		List->insert(key, value);
		return 1;
	}
	else {
		return 0;
		next = new(memtable);
		next->List->insert(key, value);
		fresh = 0;

	}

}

void memtable::deletevalue(int key) {
	List->remove(key);
}
void writeoperation(memtable** current, int key, std::string value) {

	if ((*current)->putvalue(key, value) == 0) {
		mmtx.lock();
		if ((*current)->putvalue(key, value) == 0) {
			std::cout << "new memtable" << std::endl;
			//cout << key <<" "<<(*current)->List->size<<endl;
			(*current)->next = new(memtable);
			(*current)->next->List->insert(key, value);
			(*current)->next->prev = (*current);

			(*current) = (*current)->next;

		}
		mmtx.unlock();
	}
}

std::string readoperation(memtable* current, int key)
{
	std::string k = current->getvalue(key);
	memtable *a = current;
	while (k == "#"&&a->prev != NULL) {
		a = a->prev;
		k = a->getvalue(key);
	}
	if (k == "#") {
		k = readdisk(0, key);
	}
	if (k == "#") {
		k = readdisk(1, key);
	}
	if (k == "#") {
		k = readdisk(2, key);
	}
	if (k == "#") {
		k = readdisk(3, key);
	}
	if (k == "#") {
		k = readdisk(4, key);
	}
	return k;
}