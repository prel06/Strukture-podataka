#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct _Student {
    char name[20];
    char lastName[20];
    int bodovi;
} Stud;

int main() {
    float maxbod = 50;
    Stud* Student = NULL;
    int brojac = 0;
    char buffer[50] = { 0 };
    int i = 0;

    FILE* fp = fopen("popisi.txt", "r");
    if (!fp) {
        printf("ne valja\n");
        return -1;
    }

    while (fgets(buffer, 50, fp) != NULL) {
        brojac++;
    }

    fclose(fp);

    Student = (Stud*)malloc(brojac * sizeof(Stud));
    if (!Student) {
        printf("ne valja\n");
        return -2;
    }

    fp = fopen("popisi.txt", "r");
    if (!fp) {
        printf("ne valja\n");
        free(Student);
        return -1;
    }

    while (i < brojac && fscanf(fp, "%s %s %d", Student[i].name, Student[i].lastName, &Student[i].bodovi) == 3) {
        i++;
    }

    fclose(fp);

    for (int j = 0; j < brojac; j++) {
        float RelBbrBd = ((float)Student[j].bodovi / maxbod) * 100;
        printf("Ime: %s  Prezime: %s  Bodovi: %d  Relativno: %.2f%%\n",
            Student[j].name, Student[j].lastName, Student[j].bodovi, RelBbrBd);
    }

    free(Student);
    return 0;
}