#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct cvor Cvor;
typedef struct cvor* Pozicija;

struct cvor {
	int el;
	Pozicija next;
};

int push(Pozicija, int);
Pozicija pop(Pozicija);
int ispis(Pozicija);
int velicina(FILE*);
char* stvori_izraz(FILE*, int);
int provjera_izraza(Pozicija, char*);
int racunaj_izraz(Pozicija, char);

int main()
{
	FILE* fp;
	char imedatoteke[32];
	int velicina_byte;
	int velicina_niz;
	int rez;
	char* izraz;

	Cvor head;
	head.next = NULL;

	printf("Unesite ime datoteke (ime_datoteke.txt):\n");
	scanf(" %s", imedatoteke);
	fp = fopen(imedatoteke, "r");
	if (fp == NULL) {
		printf("Datoteka se ne moze otvoriti!\n");
		return -1;
	}

	velicina_byte = velicina(fp);
	izraz = stvori_izraz(fp, velicina_byte);
	printf("Postfix izraz je: %s\n", izraz);
	provjera_izraza(&head, izraz);
	ispis(head.next);

	return 0;
}

int push(Pozicija p, int br) {
	Pozicija temp;

	if (p == NULL) {
		printf("Greska!\n");
		return -1;
	}

	temp = (Pozicija)malloc(sizeof(Cvor));
	temp->el = br;
	temp->next = p->next;
	p->next = temp;
	return 0;
}

Pozicija pop(Pozicija p) {
	Pozicija temp;

	if (p == NULL) {
		printf("Stog je prazan!\n");
		return -1;
	}
	else {
		temp = p->next;
		p->next = temp->next;
		printf("Element %d je maknut sa stoga!\n", temp->el);
		free(temp);
	}
	return temp;
}

int ispis(Pozicija p) {
	if (p == NULL) {
		printf("Stog je prazan!\n");
		return -1;
	}
	else {
		printf("Rezultat postfix izraza je: ");
		while (p != NULL) {
			printf("%d\n", p->el);
			p = p->next;
		}
	}
	return 0;
}

int velicina(FILE* fp) {
	int buffer_vel = 0;

	fseek(fp, 0, SEEK_END);
	buffer_vel = ftell(fp) + 1;
	rewind(fp);
	printf("Velicina buffera: %d\n", buffer_vel);
	return buffer_vel;
}

char* stvori_izraz(FILE* fp, int sizeOfFile) {
	char* izraz;

	izraz = (char*)calloc(sizeOfFile, sizeof(char));
	fread(izraz, sizeOfFile, 1, fp);
	return izraz;
}

int provjera_izraza(Pozicija p, char* izraz) {
	char* trenutni;

	trenutni = strtok(izraz, " ");
	while (trenutni != NULL) {
		if (isdigit(*trenutni)) {
			printf("%c je stavljen na stog!\n", *trenutni);
			push(p, atoi(trenutni));
		}
		else {
			printf("%c je operator\n", *trenutni);
			racunaj_izraz(p, *trenutni);
		}
		trenutni = strtok(NULL, " ");
	}
}

int racunaj_izraz(Pozicija p, char operation) {
	int rez, var1, var2;
	var1 = p->next->el;
	var2 = p->next->next->el;

	switch (operation) {
	case'+':
		rez = var1 + var2;
		printf("Rezultat operacije %d + %d je %d\n", var1, var2, rez);
		break;
	case '-':
		rez = var1 - var2;
		printf("Rezultat operacije %d - %d je %d\n", var1, var2, rez);
		break;
	case '*':
		rez = var1 * var2;
		printf("Rezultat operacije %d * %d je %d\n", var1, var2, rez);
		break;
	case '/':
		rez = var1 / var2;
		printf("Rezultat operacije %d / %d je %d\n", var1, var2, rez);
		break;
	}
	pop(p);
	pop(p);
	printf("Rezultat %d je stavljen na stog!\n", rez);
	push(p, rez);
	return rez;
}
