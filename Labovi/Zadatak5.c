#include <stdio.h>
#include <stdlib.h>

typedef struct lista* pozicija;

struct lista {

	int broj;
	pozicija next;
};

typedef struct lista Lista;


int unesi(pozicija);
int ispisi(pozicija);
int sortiraj(pozicija);
int slozi_unija(pozicija, pozicija, pozicija);   // lista1, lista2 i rezultat
int slozi_presjek(pozicija, pozicija, pozicija);   // lista1, lista2 i rezultat


int main()
{
	Lista L1, L2, unija, presjek;

	L1.next = NULL;
	L2.next = NULL;
	unija.next = NULL;
	presjek.next = NULL;

	unesi(&L1);
	sortiraj(&L1);
	ispisi(&L1);
	

	unesi(&L2);
	sortiraj(&L2);
	ispisi(&L2);
	
	printf("\nLista koja se dobije unijom dviju listi je: \n");

	slozi_unija(L1.next, L2.next, &unija);
	ispisi(&unija);

	printf("\nLista koja se dobije presjekom dviju listi je: \n");
	
	slozi_presjek(L1.next, L2.next, &presjek);
	ispisi(&presjek);


	return 0;
}

int unesi(pozicija p) {

	FILE* fp;
	char imeliste[25];   //unosimo ime datoteke iz koje citamo liste
	pozicija temp;

	printf("\nUnesi ime datoteke iz koje zelis ucitati listu: \n");
	scanf("%s", imeliste);

	fp = fopen (imeliste, "r");							

	if (fp == NULL) {												//u slucaju da nije dobro otvorilo datoteku
		printf("\nGreska! Datoteka nije uspjesno otvorena!");
	}
	else {

		while (!feof(fp)) {

			temp = (pozicija)malloc(sizeof(Lista));
			fscanf(fp, "%d ", &temp->broj);				//zapisujemo iz datoteke brojeve 

			temp->next = p->next;
			p->next = temp;
			p = temp;

		}

	}

	fclose(fp);				//zatvaramo datoteku

	return 0;
}

int ispisi(pozicija p) {

	p = p->next;
	printf("\nLista je: ");

	while (p != NULL) {

		printf("%d ", p->broj);
		p = p->next;
	}

	puts("");

	return 0;
}

int sortiraj(pozicija p) {

	pozicija temp, end, q, q_pr;
	end = NULL;

	while (p->next != end) {
		q_pr = p;
		q = p->next;

		while (q->next != end) {

			if (q->broj > q->next->broj) {

				temp = q->next;
				q_pr->next = temp;
				q->next = temp->next;
				temp->next = q;

				q = temp;
			}

			q_pr = q;
			q = q->next;

		}

		end = q;
	}

	return 0;

}

slozi_unija(pozicija p1, pozicija p2, pozicija rez) {

	pozicija q, tmp;

	tmp = rez;

	while (p1 != NULL && p2 != NULL) {

		if (p1->broj < p2->broj) {

			q = (pozicija)malloc(sizeof(Lista));
			q->broj = p1->broj;

			q->next = rez->next;
			rez->next = q;

			p1 = p1->next;
			rez = rez->next;
		}

		else if (p1->broj > p2->broj) {

			q = (pozicija)malloc(sizeof(Lista));
			q->broj = p2->broj;

			q->next = rez->next;
			rez->next = q;

			p2 = p2->next;
			rez = rez->next;
		}

		else if (p1->broj == p2->broj) {

			q = (pozicija)malloc(sizeof(Lista));
			q->broj = p2->broj;

			q->next = rez->next;
			rez->next = q;

			p1 = p1->next;
			p2 = p2->next;
			rez = rez->next;
		}

	}

		if (p1 != NULL) {
			while (p1 != NULL) {
				q = (pozicija)malloc(sizeof(Lista));

				q->broj = p1->broj;


				q->next = rez->next;
				rez->next = q;

				p1 = p1->next;
				rez = rez->next;
			}

		}

		if (p2 != NULL) {
			while (p2 != NULL) {
				q = (pozicija)malloc(sizeof(Lista));

				q->broj = p2->broj;


				q->next = rez->next;
				rez->next = q;

				p2 = p2->next;
				rez = rez->next;
			}

		}

	

}

slozi_presjek(pozicija p1, pozicija p2, pozicija rez) {

	pozicija q, temp;

	temp = rez;

	while (p1 != NULL && p2 != NULL) {

		if (p1->broj < p2->broj) {

			p1 = p1->next;

		}

		else if (p1->broj > p2->broj) {

			p2 = p2->next;

		}

		else if (p1->broj == p2->broj) {

			q = (pozicija)malloc(sizeof(Lista));

			q->broj = p2->broj;

			q->next = rez->next;
			rez->next = q;

			p1 = p1->next;
			p2 = p2->next;

			rez = rez->next;
		}

	}


}
