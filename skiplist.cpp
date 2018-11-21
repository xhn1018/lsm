#include "skiplist.h"
#include"time.h"
std::mutex mtx;
static unsigned int seed = NULL;
SkipList::SkipList() {

	depth = 0;
	size = 0;
	std::string m = "#";
	SkipListnode *h = create_node(maxlevel - 1, 0, m);
	head = h;
	int i;
	for (i = 0; i < maxlevel; ++i)
	{
		h->nextnode[i] = NULL;
	}
	srand(time(0));
}


std::string SkipList::search(int key) {

	SkipListnode *q, *p = head;
	q = NULL;
	int i = depth - 1;
	for (; i >= 0; --i)
	{
		while ((q = p->nextnode[i]) && q->key < key)
		{
			p = q;
		}
		if (q && key == q->key)
		{
			std::string k = q->value;
			return k;
		}
	}
	return "#";

}

SkipListnode* create_node(int level, int key, std::string val) {

	SkipListnode *p = newnode(level);
	p->key = key;
	for (int i = 0; i < val.size(); i++)
	{
		p->value[i] = *(val.c_str() + i);
	}
	p->value[val.size()] = '\0';
	return p;
};

void SkipList::insert(int key, std::string val) {

	SkipListnode *update[maxlevel];
	SkipListnode *q = NULL, *p = head;



	int i = depth;

	for (; i >= 0; --i)
	{

		while ((q = p->nextnode[i]) && (q->key < key))
			p = q;
		update[i] = p;

	}


	if (q && q->key == key)
	{

		for (int i = 0; i < val.size(); i++)
		{
			q->value[i] = *(val.c_str() + i);

		}

		q->value[val.size()] = '\0';

	}
	else {
		int level = randomVal();

		if (level > depth)
		{

			for (i = depth; i < level; ++i)
			{
				update[i] = head;
			}

			depth = level;

		}

		q = create_node(level, key, val);
		mtx.lock();
		for (i = 0; i < level; i++)
		{

			if (update[i] == NULL) update[i] = head;
			while (update[i]->nextnode[i] != NULL && update[i]->nextnode[i]->key < key) {
				//cout << 1 << endl;
				//cout << 1 << endl;
				update[i] = update[i]->nextnode[i];
			}
			if (update[i]->nextnode[i] != NULL && update[i]->nextnode[i]->key == key) {
				delete(q);
				q = update[i]->nextnode[i];
				for (int i = 0; i < val.size(); i++)
				{
					q->value[i] = *(val.c_str() + i);
				}
				q->value[val.size()] = '\0';
				break;
			}
			else {
				if (i == 0) size++;
				q->nextnode[i] = update[i]->nextnode[i];
				update[i]->nextnode[i] = q;
			}

		}
		mtx.unlock();
	}

};
void SkipList::remove(int key)
{
	SkipListnode *update[maxlevel];
	SkipListnode *q = NULL, *p = head;
	int i = depth - 1;
	for (; i >= 0; --i)
	{
		while ((q = p->nextnode[i]) && q->key < key)
		{
			p = q;
		}
		update[i] = p;
	}
	for (i = depth - 1; i >= 0; --i)
	{
		if (update[i]->nextnode[i] == q)
		{
			update[i]->nextnode[i] = q->nextnode[i];
			if (head->nextnode[i] == NULL)
				depth--;
		}
	}
	free(q);
	q = NULL;
}

int SkipList::randomVal() {
	int level = 1;
	while (rand() % 2)
		level++;
	level = (maxlevel > level) ? level : maxlevel;
	return level;
};