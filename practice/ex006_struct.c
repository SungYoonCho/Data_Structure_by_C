#include <stdio.h>

#define FALSE 0
#define TRUE 1

typedef struct {
	char name[10];
	int age;
	float salary;
} humanBeing;

int humans_equal(humanBeing person1, humanBeing person2) {
	if (strcmp(person1.name, person2.name))
		return FALSE;
	if (person1.age != person2.age)
		return FALSE;
	if (person1.salary != person2.salary)
		return FALSE;
	return TRUE;
}

void main() {
	humanBeing person1, person2;

	strcpy(person1.name, "James");
	person1.age = 10;
	person1.salary = 35000;

	strcpy(person2.name, "James");
	person2.age = 10;
	person2.salary = 35000;

	if (humans_equal(person1, person2))
		printf("The two human beings are the same.");
	else
		printf("The two human beings are not the same.");
}


