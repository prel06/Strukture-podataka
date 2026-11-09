#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Element* position;
typedef struct Element {
    double num;
    position next;
} Element;

int Push(position Head, double N) {
    position q = (position)malloc(sizeof(Element));
    if (q == NULL) {
        return -1;
    }

    q->num = N;
    q->next = Head->next;
    Head->next = q;
    return 0;
}

int Pop(position Head, double* out) {
    position q = Head->next;
    if (q == NULL) {
        return -1;
    }
    *out = q->num;
    Head->next = q->next;
    free(q);

    return 0;
}

int Postfix(const char* namedat, position Head, double* rez) {
    FILE* dat = fopen(namedat, "r");
    if (!dat) {
        return -1;
    }

    char buffer[100]; 

    
    while (fscanf(dat, "%s", buffer) == 1) {



        if (buffer[1] == '\0' && (buffer[0] == '+' || buffer[0] == '-' || buffer[0] == '*' || buffer[0] == '/')) {
            double a, b;
            if (Pop(Head, &b) != 0 || Pop(Head, &a) != 0) {
                printf("Neispravan izraz \n");
                fclose(dat);
                return -1;
            }

            if (buffer[0] == '+') Push(Head, a + b);
            else if (buffer[0] == '-') Push(Head, a - b);
            else if (buffer[0] == '*') Push(Head, a * b);
            else if (buffer[0] == '/') {
                if (b == 0) {
                    printf("Greska... Dijeljenje s nulom!\n");
                    fclose(dat);
                    return -1;
                }
                Push(Head, a / b);
            }
        }
        else {
            
            double broj;
            if (sscanf(buffer, "%lf", &broj) == 1) {
                Push(Head, broj);
            }
            else {
                printf("Nepoznat operator %s\n", buffer);
                fclose(dat);
                return -1;
            }
        }
    }

    fclose(dat);

    
    if (Pop(Head, rez) != 0) {
        return -1; 
    }

 
    if (Head->next != NULL) {
        printf("Greska: Neispravan izraz \n");
        return -1;
    }

    return 0;
}

int main() {
    Element Head = { 0, NULL };
    double rez;

    if (Postfix("postfix.txt", &Head, &rez) == 0) {
        printf("Rezultat je %.2f\n", rez);
    }
    else {
        printf("Greska\n");
    }
    return 0;
}