#include"compaction.h"
void skiptotable(SkipList a) {
	std::ifstream m("metadata" + std::to_string(0));
	int i = -1;
	int j;
	while (m >> j) m >> i;
	m.close();
	table *k = new(table);
	SkipListnode *n;
	n = a.head;
	i++;
	while (n->nextnode[0] != NULL) {

		if (k->add(n->key, n->value) == 1) {
		}
		else {
			k->tablelevel = 0;
			k->num = i;
			k->save();
			delete k;
			k = new(table);
			i++;
			k->add(n->key, n->value);
		}
		n = n->nextnode[0];
	}
	k->tablelevel = 0;
	k->num = i;
	if (k != NULL)  k->save();
	delete(k);
}



std::string readdisk(int level, int key) {
	std::ifstream r("metadata" + std::to_string(level));
	int k, num = 0;
	std::string value;
	while (r >> k) {
		r >> num;
		if (k == key) {
			break;
		}
	}
	r.close();

	std::ifstream r2("table_" + std::to_string(level) + "_" + std::to_string(num));
	while (r2 >> k) {
		r2 >> value;
		if (k == key) {
			return value;
		}
	}
	return "#";
}

void compaction(int level) {
	int nu = 0;
	int i, j = 0, j2 = 0;
	std::ifstream m("metadata" + std::to_string(level + 1));

	while (m >> i) m >> j;
	m.close();

	std::ifstream m2("metadata" + std::to_string(level));
	while (m2 >> i)  m2 >> j2;
	m2.close();


	table *k = new(table);
	for (;; nu++) {
		int key;
		std::string value;
		std::ifstream r("table_" + std::to_string(level) + "_" + std::to_string(nu));
		if (!r) { break; }

		k->num = j;
		k->tablelevel = level + 1;
		while (r >> key) {
			r >> value;
			if (k->add(key, value) == 0) {
				k->save();
				delete(k);
				k = new(table);
				j++;
				k->num = j;
				k->tablelevel = level + 1;
				k->add(key, value);
			}
		}

		r.close();
	}
	k->save();

	delete(k);

	for (int del = 0; del <= j2; del++) {
		DeleteFileA(("table_" + std::to_string(level) + "_" + std::to_string(del)).c_str());
	}

	std::ofstream d("metadata" + std::to_string(level));
	d.close();


}