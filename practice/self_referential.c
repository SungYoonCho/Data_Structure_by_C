#include <stdio.h>

struct list {
	char data;
	struct list *link;
};

typedef struct list _list;

void main() {
	_list item1, item2, item3;

	item1.data = 'a';
	item2.data = 'b';
	item3.data = 'c';
	item1.link = item2.link = item3.link = NULL;

	item1.link = &item2;
	item2.link = &item3;

}