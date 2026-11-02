#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    double coeff;
    int exp;
    struct Node* next;
} Node;


void umetni(Node** poly, double coeff, int exp) {
    if (coeff == 0) return;

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;

    if (*poly == NULL || (*poly)->exp < exp) {
        newNode->next = *poly;
        *poly = newNode;
        return;
    }

    Node* current = *poly;
    Node* prev = NULL;

    while (current != NULL && current->exp > exp) {
        prev = current;
        current = current->next;
    }

    if (current != NULL && current->exp == exp) {
        current->coeff += coeff;
        free(newNode);
        if (current->coeff == 0) {
            if (prev == NULL) {
                *poly = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
        }
    }
    else {
        newNode->next = current;
        if (prev == NULL) {
            *poly = newNode;
        }
        else {
            prev->next = newNode;
        }
    }
}


Node* citaj(FILE* file) {
    int n, i;
    double coeff;
    int exp;
    Node* poly = NULL;

    if (fscanf(file, "%d", &n) != 1) return NULL;

    for (i = 0; i < n; i++) {
        fscanf(file, "%lf %d", &coeff, &exp);
        umetni(&poly, coeff, exp);
    }
    return poly;
}

Node* zbroji(Node* p1, Node* p2) {
    Node* zbr = NULL;
    Node* curr = p1;
    while (curr != NULL) {
        umetni(&zbr, curr->coeff, curr->exp);
        curr = curr->next;
    }
    curr = p2;
    while (curr != NULL) {
        umetni(&zbr, curr->coeff, curr->exp);
        curr = curr->next;
    }
    return zbr;
}


Node* pomnozi(Node* p1, Node* p2) {
    Node* umn = NULL;
    for (Node* i = p1; i != NULL; i = i->next) {
        for (Node* j = p2; j != NULL; j = j->next) {
            double c = i->coeff * j->coeff;
            int e = i->exp + j->exp;
            umetni(&umn, c, e);
        }
    }
    return umn;
}


void ispisi(Node* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    Node* curr = poly;
    int first = 1;
    while (curr != NULL) {
        if (!first) {
            if (curr->coeff > 0) printf(" + ");
            else printf(" - ");
        }
        else {
            if (curr->coeff < 0) printf("-");
            first = 0;
        }

        double absCoeff = curr->coeff < 0 ? -curr->coeff : curr->coeff;

        if (curr->exp == 0) {
            printf("%.2f", absCoeff);
        }
        else if (curr->exp == 1) {
            printf("%.2fx", absCoeff);
        }
        else {
            printf("%.2fx^%d", absCoeff, curr->exp);
        }
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    FILE* file = fopen("polinomi.txt", "r");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke polinomi.txt!\n");
        return 1;
    }

    Node* p1 = citaj(file);
    Node* p2 = citaj(file);
    fclose(file);

    printf("Prvi polinom:    ");
    ispisi(p1);

    printf("Drugi polinom:   ");
    ispisi(p2);

    Node* zbr = zbroji(p1, p2);
    printf("Zbroj     ");
    ispisi(zbr);

    Node* umn = pomnozi(p1, p2);
    printf("Produkt    ");
    ispisi(umn);

   
    Node* tmp;

    while (p1 != NULL) { tmp = p1; p1 = p1->next; free(tmp); }
    while (p2 != NULL) { tmp = p2; p2 = p2->next; free(tmp); }
    while (zbr != NULL) { tmp = zbr; zbr = zbr->next; free(tmp); }
    while (umn != NULL) { tmp = umn; umn = umn->next; free(tmp); }

    return 0;
}