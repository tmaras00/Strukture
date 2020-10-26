#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BODOVI 80

typedef struct Student student;
struct Student {
	char ime[50];
	char prezime[50];
	int bodovi;
};

int main() {
	int brojac = 0;
	int ch = 0;

	FILE * fajl;
	fajl = fopen("studenti.txt", "r");

	if (fajl == NULL) {
		printf("Nije se otvoria .txt!\n");
		return -1;
	}
	//Brojac studenata (mora biti stisnut Enter na kraju tekstualne datoteke nakon broja bodova zadnjeg studenta)
	while (!feof(fajl))
	{
		ch = fgetc(fajl);
		if (ch == '\n')
			brojac++;
	}
	//Provjera brojaca
	printf("%d\n", brojac);
	fclose(fajl);
	fopen("studenti.txt", "r");
	//Alociranje memorije za niz strukture
	student* niz = (student*)malloc(sizeof(student)*brojac);
	if (niz == NULL){
		printf("Memorija NIJE alocirana!\n");
		return -2;
	}
	//Ucitavanje podataka iz .txt
	//Redak mora izgledat ovako: Ime Prezime BrBodova
	int i = 0;
	while (!feof(fajl)) {
		fscanf(fajl, "%s %s %d", niz[i].ime, niz[i].prezime, &niz[i].bodovi);
		i++;
	}
	//Ispis podataka
	for (i = 0; i < brojac; i++) {
		printf("%s %s %d %.2f\n", niz[i].ime, niz[i].prezime, niz[i].bodovi, (float)niz[i].bodovi/MAX_BODOVI*100);
	}
	
	fclose(fajl);
	return 0;
}
