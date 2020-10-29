#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct osoba* p_osoba;

typedef struct osoba {
	char ime[30];
	char prezime[30];
	int godina;
	p_osoba next;
}_osoba;

int ispis(p_osoba);
int unosPocetak(p_osoba); 
int unosKraj(p_osoba);    
int traziPrezime(p_osoba);    
int traziUkloni(p_osoba);

int main()
{
	_osoba head;
	head.next = NULL;
	unosPocetak(&head);
	unosPocetak(&head);
	unosKraj(&head);
	unosPocetak(&head);
	ispis(head.next);
	traziUkloni(&head);
	ispis(head.next);

	return 0;
}

int unosPocetak(p_osoba p)
{
	p_osoba q = (p_osoba)malloc(sizeof(_osoba));

	if (q == NULL) {
		puts("GREŠKA! Memorija nije alocirana");
		return -1;
	}

	puts("Unesi ime:"); //unos podataka
	scanf("%s", q->ime);
	puts("Unesi prezime:");
	scanf("%s", q->prezime);
	puts("Unesi godinu rodenja:");
	scanf("%d", &q->godina);

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

	puts("Unesi ime:"); //unos podataka
	scanf("%s", q->ime);
	puts("Unesi prezime:");
	scanf("%s", q->prezime);
	puts("Unesi godinu rodenja:");
	scanf("%d", &q->godina);

	while (p->next != NULL) {   //trazenje zadnjeg clana
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

int traziPrezime(p_osoba p) 
{
	char prezime[20];   

	puts("Upisi prezime koje trazite:");
	scanf("%s", prezime);   

	while (p->next != NULL && strcmp(prezime, p->prezime) != 0)
	{
		p = p->next;   
	}

	if (strcmp(prezime, p->prezime) == 0)  
		printf("p_osoba je pronaden: %s\t%s\t%d\n", p->ime, p->prezime, p->godina); 

	else if (strcmp(prezime, p->prezime) != 0)  
		puts("Trazeno prezime ne postoji u listi"); 

	return 0;
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
