#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

typedef struct cvor* Pozicija;

struct cvor {

	int br;
	Pozicija next;
	Pozicija last;
};

typedef struct cvor Cvor;

int randBr();
int push(Pozicija);
int pop(Pozicija);
int ispis(Pozicija);

int main()
{
	Cvor head;
	head.next = NULL;
	head.last = NULL;

	char izbor;

	srand(time(NULL));
	while (1) {
		printf("\n\tIZBORNIK:\n");
		printf("P - push\nK - pop\nI - ispis\nQ - izlaz iz programa");
		printf("Unesite svoj izbor: ");
		scanf(" %c", &izbor);

		switch (toupper(izbor)) {
		case 'P': push(&head); break;
		case 'K': pop(&head); break;
		case 'I': ispis(&head); break;
		case 'Q': return 0;
		default: printf("Unijeli ste krivu naredbu!\n"); break;
		}
	}
	return 0;
}

int pop(Pozicija P) {

	Pozicija prev;

	prev = P;
	P = P->next;

	while (P->next != NULL) {
		prev = P;
		P = P->next;
	}
	printf("Uklonjen %d\n", P->br);
	prev->next = P->next;

	free(P);
}

int push(Pozicija p)
{
	Pozicija novi;

	if (p == NULL) {
		puts("Neispravan argument, null pokazivac");
		return -1;
	}

	novi = (Pozicija)malloc(sizeof(Cvor));	//stvara se novi element
	novi->br = randBr();
	printf("Dodan %d\n", novi->br);

	novi->next = p->next;
	p->next = novi;

	return 0;
}

int randBr()
{
	int rand_br;
	rand_br = rand() % (100 - 1 + 1) + 1;   // "(b - a + 1) + a" za interval od <a,b>
	return rand_br;
}

int ispis(Pozicija p)
{
	if (p->next == NULL) {
		puts("Prazna lista!");
		return -1;
	}

	p = p->next;

	printf("Ispis reda: ");
	while (p != NULL) {
		printf("%d ", p->br);
		p = p->next;
	}
	puts("");

	return 0;
}
