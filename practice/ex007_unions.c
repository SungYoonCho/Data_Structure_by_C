#include <stdio.h>

typedef struct {
	int month;
	int day;
	int year;
} date;

typedef struct {
	enum tagField {pitcher, hitter} role;
	union {
		int SO;
		int HR;
	} u;
} playerType;

typedef struct {
	char name[40];
	int age;
	float salary;
	date dob;
	playerType playerInfo;
} baseballPlayer;

void printPlayerInfo(baseballPlayer);

void main() {
	baseballPlayer person1, person2;

	strcpy(person1.name, "Hyun-Jin Ryu");
	person1.age = 32;
	person1.salary = 17900000.0;
	person1.dob.year = 1987;
	person1.dob.month = 3;
	person1.dob.day = 25;
	person1.playerInfo.role = pitcher;
	person1.playerInfo.u.SO = 163;

	strcpy(person2.name, "Shin-Soo Choo");
	person2.age = 37;
	person2.salary = 21000000.0;
	person2.dob.year = 1982;
	person2.dob.month = 7;
	person2.dob.day = 13;
	person2.playerInfo.role = hitter;
	person2.playerInfo.u.HR = 24;
	
	printPlayerInfo(person1);
	printPlayerInfo(person2);

}

void printPlayerInfo(baseballPlayer p) {
	printf("--------------------------------\n");
	printf(" name: %s\n", p.name);
	printf(" age : %d\n", p.age);
	printf(" salary: $ %.1f\n", p.salary);
	printf(" dob : %4d/%2d/%2d\n", p.dob.year, p.dob.month, p.dob.day);
	if (p.playerInfo.role == pitcher) {
		printf(" PITCHER SO: %d\n", p.playerInfo.u.SO);
	}
	else {
		printf(" HITTER  HR: %d\n", p.playerInfo.u.HR);
	}
	printf("--------------------------------\n");
}

