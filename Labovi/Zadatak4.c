#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct clan* p_clan;

typedef struct clan {
	int koef;
	int exp;
	p_clan next;

};

typedef struct clan _clan;

int citaj_iz_dat(FILE*, p_clan, p_clan);
int ispis(p_clan);	//ispis liste polinoma
int bufferVel(FILE*);	//racunamo velicinu buffera
int ucitaj_pol(char*, p_clan, p_clan);  //ucitavamo polinom
int sortirani_unos(p_clan);	//sortirani unos u listu!
int zbroji_pol(p_clan, p_clan, p_clan);  //zbrajamo polinome
int mnozi_pol(p_clan, p_clan, p_clan);  // mnozimo polinome
int zbr_iste_exp(p_clan);	//zbraja sve clanove polinoma sa istim eksponentom
int ukloni(p_clan);	//funkcija uklanja listu iz memorije

int main()
{
	FILE* fp;

	_clan p1_HEAD, p2_HEAD, rez_HEAD;	//prvi pol, drugi pol, rezultatni pol

	p1_HEAD.next = NULL;
	p2_HEAD.next = NULL;
	rez_HEAD.next = NULL;

	fp = fopen("polinomi.txt", "r");

	if (fp == NULL) {
		printf("\nGRESKA! Datoteka nije uspjesno otvorena!\n");
		return -1;
	}

	citaj_iz_dat(fp, &p1_HEAD, &p2_HEAD);

	printf("Ispis prvog polinoma: ");
	ispis(p1_HEAD.next);

	printf("Ispis drugog polinoma: ");
	ispis(p2_HEAD.next);

	//zakomentirat oni koji se ne koristi
	//zbrojiPol(p1_HEAD.next, p2_HEAD.next, &rez_HEAD);
	mnozi_pol(p1_HEAD.next, p2_HEAD.next, &rez_HEAD);
	printf("Ispis prije sredivanja: ");
	ispis(rez_HEAD.next);

	zbr_iste_exp(&rez_HEAD);
	printf("Ispis konacnog rezultata: ");
	ispis(rez_HEAD.next);

	//oslobadanje memorije
	ukloni(&p1_HEAD);
	ukloni(&p2_HEAD);
	ukloni(&rez_HEAD);

	return 0;
}



int sortirani_unos(p_clan novi_el, p_clan p)
{
	p_clan head = NULL;
	head = p;

	if (p->next == NULL) {
		novi_el->next = p->next;
		p->next = novi_el;
	}

	else {
		while (p->next != NULL && p->next->exp < novi_el->exp) {
			p = p->next;
		}

		novi_el->next = p->next;
		p->next = novi_el;
	}
	p = head;

	return 0;
}

int ispis(p_clan p)
{
	if (p == NULL) {
		printf("\nLista je prazna!\n");
		return -1;
	}

	while (p != NULL)   //petlja radi dok ne dodemo do zadnjeg clana, koji pokazuje na NULL/nista jer nema svog sljedbenika unutar liste
	{
		if (p->next == NULL) {	//ako je zadnji clan u listi
			printf("%dx^%d", p->koef, p->exp);
		}

		else {	//opci slucaj
			printf("%dx^%d + ", p->koef, p->exp); //ispis podataka trenutnog clana liste
		}

		p = p->next;    //prebaci na sljedeci clan u listi
	}

	puts("");

	return 0;
}

int ukloni(p_clan p)	//head element liste
{
	p_clan prev;

	p = p->next;

	while (p != NULL) {
		prev = p;
		p = p->next;

		free(prev);
	}

	return 0;
}

int ucitaj_pol(char* buffer, p_clan p, p_clan novi_el)
{
	int koef, exp, n, r;
	int offset = 0;	//pomak u stringu
	p_clan head = p;

	while (buffer != EOF) {   //dok ne dodemo do kraja datoteke
		r = sscanf(buffer, "%d %d%n", &koef, &exp, &n);

		if (r == EOF) {		//end of file/kraj datoteke
			printf("\nKraj datoteke!\n");
			return -1;
		}

		if (r == 0) {	//nije u formatu
			printf("\nGreska! Pogresan format!");
			break;
		}

		offset += n;

		buffer = (buffer + n);	//pomicemo pokazivac buffera na ono mjesto do kojeg smo obavili sscanf


		novi_el = (p_clan)malloc(sizeof(_clan)); //stvaramo novu strukturu

		novi_el->koef = koef;	//unos podataka u novi (element) clan
		novi_el->exp = exp;

		sortirani_unos(novi_el, p);

		if (*buffer == '\n') {	//ako smo ucitali cijeli prvi redak tj.polinom, odnosno dosli do kraja retka
			break;
		}

	}

	offset += 1;	//kod cita 1 offset viska

	return offset;
}

int zbroji_pol(p_clan p1, p_clan p2, p_clan rez) {

	p_clan novi_el, rez_HEAD;

	rez_HEAD = rez;

	while (p1 != NULL && p2 != NULL) {

		if (p1->exp < p2->exp) {
			novi_el = (p_clan)malloc(sizeof(_clan));	//dinamicki stvaramo novi clan

			novi_el->exp = p1->exp;	//unos podataka
			novi_el->koef = p1->koef;

			novi_el->next = rez->next;	//dodaje se u listu
			rez->next = novi_el;

			p1 = p1->next;

			rez = rez->next;
		}

		else if (p1->exp > p2->exp) {
			novi_el = (p_clan)malloc(sizeof(_clan));	//takoder dinamicki stvaramo novi clan

			novi_el->exp = p2->exp;	//unos podataka
			novi_el->koef = p2->koef;

			novi_el->next = rez->next;	//dodaje se u listu
			rez->next = novi_el;

			p2 = p2->next;
			rez = rez->next;
		}

		else if (p1->exp == p2->exp) {
			novi_el = (p_clan)malloc(sizeof(_clan));

			novi_el->exp = p2->exp;
			novi_el->koef = p2->koef + p1->koef;

			novi_el->next = rez->next;
			rez->next = novi_el;

			p1 = p1->next;
			p2 = p2->next;

			rez = rez->next;
		}

	}

	//ako smo dosli na kraj polinoma, tada na kraj liste unosimo preostale clanove polinoma jer su sortirani vec

	if (p1 != NULL) {
		while (p1 != NULL) {
			novi_el = (p_clan)malloc(sizeof(_clan));

			novi_el->koef = p1->koef;
			novi_el->exp = p1->exp;

			novi_el->next = rez->next;	//dodaje se u listu
			rez->next = novi_el;

			p1 = p1->next;
			rez = rez->next;
		}

	}

	if (p2 != NULL) {
		while (p2 != NULL) {
			novi_el = (p_clan)malloc(sizeof(_clan));

			novi_el->koef = p2->koef;
			novi_el->exp = p2->exp;

			novi_el->next = rez->next;	//dodaje se u listu
			rez->next = novi_el;

			p2 = p2->next;
			rez = rez->next;
		}

	}

	return 0;
}

int mnozi_pol(p_clan p1, p_clan p2, p_clan rez)
{
	p_clan novi_el, rez_HEAD, p2_start;

	rez_HEAD = rez;
	p2_start = p2;


	if (p1 == NULL || p2 == NULL || rez == NULL) {	   //uvjeti!
		printf("\nGreska! Jedan od pokazivaca na polinom je NULL\n");
		return -1;
	}

	while (p1 != NULL)
	{

		while (p2 != NULL)
		{
			novi_el = (p_clan)malloc(sizeof(_clan));

			novi_el->exp = (p1->exp + p2->exp);	   // eksponenti se zbrajaju kod mnozenja polinoma, a baze mnoze
			novi_el->koef = (p1->koef * p2->koef);

			sortirani_unos(novi_el, rez_HEAD);   // sortiramo

			p2 = p2->next;
		}

		p1 = p1->next;
		p2 = p2_start;
	}

	return 0;
}

int zbr_iste_exp(p_clan p_HEAD)
{
	p_clan prev, tren, sljed;	//prethodni, trenutni, sljedeci

	prev = p_HEAD;
	tren = p_HEAD->next;
	sljed = tren->next;

	while (sljed != NULL)
	{
		if (tren->exp == sljed->exp) {	//ako su eksponenti jednaki trenutnom i sljedecem
			sljed->koef += tren->koef;	//zbroj koeficijenata unosimo u sljedeci

			prev->next = sljed;	//trenutni se iskljucuje iz liste
			free(tren);	//oslobada se memorija trenutnog

			tren = sljed;	//sljedeci postaje trenutni
			sljed = sljed->next;	//novi element je sljedeci element
			prev = prev;	//prethodni ostaje isti
		}
		else {
			prev = tren;	//trenutni postaje prethodni
			tren = sljed;	//novi element je trenutni
			sljed = sljed->next; //novi element je sljedeci
		}
	}
	return 0;
}

int citaj_iz_dat(FILE* fp, p_clan p1, p_clan p2)
{
	int buffer_vel = 0;
	p_clan novi_el = NULL;
	char* buffer = NULL;
	int offset = 0, exp = 0, koef = 0, r = 0;	

	buffer_vel = bufferVel(fp);	//odredujemo velicinu buffera

	buffer = (char*)calloc(buffer_vel, sizeof(char));	//alokacija buffera
	fread(buffer, buffer_vel, 1, fp);	//sadrzaj iz datoteke upisujemo u buffer!

	fclose(fp);

	printf("Ispis buffera:\n%s\n", buffer);	//ispis sadrzaja buffera

	//funkcija vraca pomak pokazivaca u stringu nakon citanja prvog polinoma
	offset = ucitaj_pol(buffer, p1, novi_el);	//prvi polinom se upisuje u listu	

	buffer = (buffer + offset);	//pomice se pokazivac buffera

	ucitaj_pol(buffer, p2, novi_el);	//ucitavanje drugog polinoma u listu

	return 0;
}

int bufferVel(FILE* fp) {	//racuna se velicina buffera
	int buffer_vel = 0;

	fseek(fp, 0, SEEK_END);	//stavljamo file pointer na kraj
	buffer_vel = ftell(fp);	// funkcija vraca kolicinu bajtova od pocetka do trenutne pozicije
	rewind(fp);	//pokazivac datoteke se vraca na pocetak

	printf("DULJINA BUFFERA JE %d\n", buffer_vel);	//provjera

	return buffer_vel;
}
