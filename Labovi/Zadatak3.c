#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct osoba* p_osoba;

typedef struct osoba {
	char ime[20];
	char prezime[20];
	int godina;
	p_osoba next;
}_osoba;

void unosPodataka(p_osoba);
int ispis(p_osoba); 
int unosPocetak(p_osoba); 
int unosKraj(p_osoba);    
p_osoba traziPrezime(p_osoba);    //funkcija trazi clan u listi po prezimenu
p_osoba traziPrethodni(p_osoba);    //funkcija trazi clan u listi po koji se nalazi ispred trazenog prezimena
int traziUkloni(p_osoba); 
int dodajIza(p_osoba);
int dodajIspred(p_osoba);
void sortiraj(p_osoba);
int uDatoteku(p_osoba);
int izDatoteke(p_osoba);

int main()
{
	_osoba head;
	_osoba ucitano;
	head.next = NULL;
	ucitano.next = NULL;
	char izbor;

	while (1) {
		printf("\nIZBORNIK:\n");
		printf("P - unos na pocetak liste\nK - unos na kraj liste\nT - trazi po prezimenu\nD - ukloni po prezimenu\nI - ispis liste\nL - izlaz iz programa\nA - unos ispred odredenog elementa\nB - unos iza odredenog elementa\nS - sortiranje liste\nE - upis u datoteku\nH - cita iz datoteke\n");
		printf("Unesite naredbu:");
		scanf(" %c", &izbor);

		switch (toupper(izbor)) {
		case 'P': unosPocetak(&head); break;
		case 'K': unosKraj(&head); break;
		case 'T': traziPrezime(head.next); break;
		case 'D': traziUkloni(&head); break;
		case 'I': ispis(head.next); break;
		case 'B': dodajIza(&head); break;
		case 'A': dodajIspred(&head); break;
		case 'S': sortiraj(&head); printf("Sortirarnje je gotovo!\n"); break;
		case 'E': uDatoteku(head.next); break;
		case 'H': izDatoteke(&ucitano); break;
		case 'L': return 1; break;
		default: printf("Unili ste krivu komandu!\n"); break;

		}

	}

	return 0;
}

int unosPocetak(p_osoba p)
{
	p_osoba q = (p_osoba)malloc(sizeof(_osoba));

	if (q == NULL) {
		puts("GREŠKA! Memorija nije alocirana");
		return -1;
	}

	unosPodataka(q);

	q->next = p->next;
	p->next = q;  

	return 0;
}

int unosKraj(p_osoba p)
{
	p_osoba q = (p_osoba)malloc(sizeof(_osoba));

	if (q == NULL) {
		puts("GREŠKA! Memorija nije alocirana");
		return -1;
	}

	unosPodataka(q);

	while (p->next != NULL) {
		p = p->next;
	}
	p->next = q;
	q->next = NULL;

	return 0;
}

int ispis(p_osoba p)
{
	puts("Ispis popisa ljudi:\n");

	while (p != NULL)
	{
		printf("%s\t%s\t%d\n", p->ime, p->prezime, p->godina);
		p = p->next;
	}

	return 0;
}

p_osoba traziPrezime(p_osoba p)
{
	char prezime[20];

	puts("Upisi prezime koje trazite:");
	scanf("%s", prezime);

	while (p->next != NULL && strcmp(prezime, p->prezime) != 0)
	{
		p = p->next;
	}

	if (strcmp(prezime, p->prezime) == 0) {
		printf("Osoba je pronadena: %s\t%s\t%d\n", p->ime, p->prezime, p->godina);
		return p;
	}
	else if (strcmp(prezime, p->prezime) != 0)
	{
		puts("Trazeno prezime ne postoji u listi");
		return NULL;
	}

}

int traziUkloni(p_osoba p)
{
	char prezime[20];
	p_osoba temp = (p_osoba)malloc(sizeof(_osoba));

	if (temp == NULL) {
		puts("GREŠKA! Memorija nije alocirana");
		return -1;
	}

	puts("Upisi prezime osobe koju zelis ukloniti:");
	scanf("%s", prezime);

	while (p->next != NULL && strcmp(prezime, p->prezime) != 0)
	{
		temp = p;
		p = p->next;
	}

	if (strcmp(prezime, p->prezime) == 0) {
		temp->next = p->next;
		free(p);
	}

	else if (strcmp(prezime, p->prezime) != 0)
		puts("Trazeno prezime ne postoji u listi");

	return 0;
}

int dodajIza(p_osoba p)
{
	p_osoba novi = (p_osoba*)malloc(sizeof(_osoba));

	if (novi == NULL) {
		return -1;
	}

	p_osoba trazeni = traziPrezime(p);

	if (trazeni == NULL) {
		return -1;
	}

	novi->next = trazeni->next;
	trazeni->next = novi;

	unosPodataka(novi);

	return 0;
}

p_osoba traziPrethodni(p_osoba p)
{
	char prezime[20];

	p_osoba prethodni = p;

	puts("Upisi prezime koje trazite:");
	scanf("%s", prezime);

	while (p->next != NULL && strcmp(prezime, p->prezime) != 0)
	{
		prethodni = p;
		p = p->next;
	}

	if (strcmp(prezime, p->prezime) == 0) {
		printf("p_osoba je pronaden: %s\t%s\t%d\n", p->ime, p->prezime, p->godina);
		return prethodni;
	}

	else if (strcmp(prezime, p->prezime) != 0)
	{
		puts("Trazeno prezime ne postoji u listi");
		return NULL;
	}

}

int dodajIspred(p_osoba p)
{
	p_osoba prethodni, novi;

	prethodni = traziPrethodni(p);

	if (prethodni == NULL) {
		return -1;
	}

	novi = (p_osoba*)malloc(sizeof(_osoba));

	if (novi == NULL) {
		puts("GRESKA!!! Alokacija memorije za novi clan nije uspjela");
		return -1;
	}

	unosPodataka(novi);

	novi->next = prethodni->next;
	prethodni->next = novi;

	return 0;
}

void unosPodataka(p_osoba p)
{
	puts("Unesi ime:");
	scanf("%s", p->ime);
	puts("Unesi prezime:");
	scanf("%s", p->prezime);
	puts("Unesi godinu rodenja:");
	scanf("%d", &p->godina);

}

void sortiraj(p_osoba p)
{
	p_osoba  j, prev, temp, end;

	end = NULL;

	while (p->next != end)
	{
		prev = p;
		j = p->next;

		while (j->next != end)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0) {

				temp = j->next;
				prev->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}
			prev = j;
			j = j->next;
		}
		end = j;
	}
}

int uDatoteku(p_osoba p)
{
	FILE* fp = NULL;

	fp = fopen("osobe.txt", "w");

	if (fp == NULL) {
		puts("GRESKA!!! Datoteka nije otvorena!");
		return -1;
	}

	while (p != NULL) {
		if (p->next == NULL) {
			fprintf(fp, "%s\t%s\t%d", p->ime, p->prezime, p->godina);
			break;
		}
		fprintf(fp, "%s\t%s\t%d\n", p->ime, p->prezime, p->godina);

		p = p->next;
	}

	puts("Upis u datoteku je zavrsen");
	fclose(fp);
	return 0;
}

int izDatoteke(p_osoba p)
{
	p_osoba novi, temp;
	FILE* fp = NULL;

	fp = fopen("osobe.txt", "r");

	if (fp == NULL) {
		puts("GRESKA!!! Datoteka nije otvorena!");
		return -1;
	}

	temp = p;
	temp->next = p->next;

	while (!feof(fp)) {

		novi = (p_osoba)malloc(sizeof(_osoba));
		fscanf(fp, "%s%s%d", novi->ime, novi->prezime, &novi->godina);

		novi->next = temp->next;    //unos na kraj liste
		temp->next = novi;
		temp = novi;
	}

	puts("Unos iz datoteke je zavrsen");
	fclose(fp);
	return 0;
}
