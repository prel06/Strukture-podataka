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

// OVO JE NEDOSTAJALO: Funkcija koja traži prethodni element
position findPrevious(char* LastN, position P) {
	position prev = P;
	position curr = P->next;

	while (curr != NULL) {
		if (strcmp(curr->sname, LastN) == 0) {
			return prev;
		}
		prev = curr;
		curr = curr->next;
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
int insertAfterSpc(char* targetSname, char* Name, char* Sname, int Date, position P) {
	position target = findLastN(targetSname, P);
	if (target == NULL) {
		printf("Element s prezimenom %s nije pronadjen.\n", targetSname);
		return -1;
	}

	position newPerson = (position)malloc(sizeof(Per));
	if (!newPerson) return -1;
	strcpy(newPerson->name, Name);
	strcpy(newPerson->sname, Sname);
	newPerson->date = Date;

	insertAfter(target, newPerson);
	return 0;
}


int insertBeforeSpc(char* targetSname, char* Name, char* Sname, int Date, position P) {
	position prev = findPrevious(targetSname, P);
	if (prev == NULL) {
		printf("Element s prezimenom %s nije valjan\n", targetSname);
		return -1;
	}

	position newPerson = (position)malloc(sizeof(Per));
	if (!newPerson) return -1;
	strcpy(newPerson->name, Name);
	strcpy(newPerson->sname, Sname);
	newPerson->date = Date;

	insertAfter(prev, newPerson); 
	return 0;
}


int sortList(position P) {
	if (P->next == NULL) return 0;

	

	position i, j, prev_j;
	int swapped;

	do {
		swapped = 0;
		prev_j = P;
		j = P->next;

		while (j->next != NULL) {
			position next_node = j->next;
			
			if (strcmp(j->sname, next_node->sname) > 0) {
				prev_j->next = next_node;
				j->next = next_node->next;
				next_node->next = j;

				j = next_node; 
				swapped = 1;
			}
			prev_j = j;
			j = j->next;
		}
	} while (swapped);

	return 0;
}


int printToFile(char* filename, position P) {
	FILE* file = fopen(filename, "w"); 
	if (!file) {
		printf("Greska pri otvaranju datoteke za upis\n");
		return -1;
	}

	position p = P->next;
	while (p != NULL) {
		fprintf(file, "%s %s %d\n", p->name, p->sname, p->date);
		p = p->next;
	}

	fclose(file);
	return 0;
}
	
	



	int readFromFile(char* filename, position P) {
		FILE* file = fopen(filename, "r"); 
		if (!file) {
			printf("Greska pri otvaranju datoteke za citanje!\n");
			return -1;
		}

		char name[30], sname[30];
		int date;

		while (fscanf(file, "%s %s %d", name, sname, &date) == 3) {
			insertEnd(name, sname, date, P);
		}

		fclose(file);
		return 0;
}

int main() {
	Per Head = { { 0 },{ 0 }, 0, NULL };
	position p = &Head;

	insertBegin("Ana", "Anic", 2006, p);
	insertBegin("Ivan", "Ivic", 1975, p);
	insertBegin("Petar", "Peric", 1972, p);
	insertBegin("Luka", "Lulic", 1972, p);
	insertEnd("Marko", "Markic", 2011, p);

	printf("pocetna lista\n\n");

	for (position q = p->next; q != NULL; q = q->next) {
		printf("%s ", q->name);
		printf("%s ", q->sname);
		printf("%d", q->date);
		printf("\n");
	}
	char prez[20];
	printf("\n\nUnesite prezime osobe koju zelite izbrisati\n\n Za nastavak bez brisanja pritisnite bilo koju tipku\n");
	scanf("%s", prez);


	if(strcmp(prez, "Ivic") == 0) {
		deletePerson("Ivic", p);
	}
else if (strcmp(prez, "Peric") == 0) {
	deletePerson("Peric", p);
}

else if (strcmp(prez, "Lulic") == 0) {
		deletePerson("Lulic", p);
	}
else if (strcmp(prez, "Anic") == 0) {
		deletePerson("Anic", p);
	}
else if (strcmp(prez, "Markic") == 0) {
		deletePerson("Markic", p);
	}
else {
	printf("Vasa nova lista nakon brisanja\n");
	}
	for (position q = p->next; q != NULL; q = q->next) {
		printf("%s ", q->name);
		printf("%s ", q->sname);
		printf("%d", q->date);
		printf("\n");
	}

	printf("Vasa lista nakon sortiranja po prezimenu\n");
	sortList(p);
	for (position q = p->next; q != NULL; q = q->next) {
		printf("%s %s %d\n", q->name, q->sname, q->date);
	}

	

	insertAfterSpc("Anic", "Maja", "Majic", 1995, p);
	insertBeforeSpc("Ivic", "Josip", "Josipovic", 1980, p); 

	printToFile("osobe.txt", p);

	return 0;
}