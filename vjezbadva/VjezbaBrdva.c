#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct _person* position;
typedef struct _person {
	char name[30];
	char sname[30];
	int date;
	position next;
} Per;

int insertAfter(position P, position newP) {
	newP->next = P->next;
	P->next = newP;
	return 0;
}

int insertBegin(char* Name, char* Sname, int Date, position P) {
	position newPerson = NULL;
	newPerson = (position)malloc(sizeof(Per));
	newPerson->date = Date;
	strcpy(newPerson->name, Name);
	strcpy(newPerson->sname, Sname);
	newPerson->next = NULL;

	insertAfter(P, newPerson);
	return 0;
}

int insertEnd(char* Name, char* Sname, int Date, position P) {
	position newPerson = NULL;
	newPerson = (position)malloc(sizeof(Per));
	newPerson->date = Date;
	strcpy(newPerson->name, Name);
	strcpy(newPerson->sname, Sname);
	newPerson->next = NULL;

	position p = P;
	while (p->next != NULL) {
		p = p->next;
	}
	insertAfter(p, newPerson);
	return 0;
}

position findLastN(char* LastN, position P) {
	position q = NULL;
	for (q = P->next; q != NULL; q = q->next) {
		if (strcmp(q->sname, LastN) == 0) {
			return q;
		}
	}
	return NULL;
}

int deletePerson(char* LastN, position P) {
	position prev = P;
	position curr = prev->next;

	while (curr != NULL) {
		if (strcmp(curr->sname, LastN) == 0) {
			prev->next = curr->next;
			free(curr);
			break;
		}
		prev = curr;
		curr = curr->next;
	}
	return 0;
}

int main() {
	Per Head = { {0}, {0}, 0, NULL };
	position p = &Head;

	insertBegin("Ana", "Anic", 2006, p);
	insertBegin("Ivan", "Ivic", 1975, p);
	insertBegin("Petar", "Peric", 1972, p);
	insertBegin("Luka", "Lulic", 1972, p);
	insertEnd("Marko", "Markic", 2011, p);

	for (position q = p->next; q != NULL; q = q->next) {
		printf("%s ", q->name);
		printf("%s ", q->sname);
		printf("%d", q->date);
		printf("\n");
	}

	deletePerson("Ivic", p);

	return 0;
}