#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct lista* pozicija;
typedef struct lista Lista;

struct lista {

	int broj;
	pozicija next;
};

int unesi(pozicija p) {

	FILE* fp;
	char imeliste[25];   
	pozicija temp;
	static int brojac=1;
	printf("\nUnesi ime datoteke iz koje zelite ucitati %d. listu: \n",brojac);
	scanf("%s", imeliste);

	fp = fopen(imeliste, "r");

	if (fp == NULL) {												
		printf("\nGreska! Datoteka nije uspjesno otvorena!");
	}
	else {

		while (!feof(fp)) {

			temp = (pozicija)malloc(sizeof(Lista));
			fscanf(fp, "%d ", &temp->broj);				

			temp->next = p->next;
			p->next = temp;
			p = temp;
		}
	}

	fclose(fp);	
	brojac++;
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

Unija(pozicija p1, pozicija p2, pozicija rez) {

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

Presjek(pozicija p1, pozicija p2, pozicija rez) {

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


int main()
{
	Lista L1, L2, unija, presjek;

	L1.next = NULL;
	L2.next = NULL;
	unija.next = NULL;
	presjek.next = NULL;

	char izbor;

	unesi(&L1);
	sortiraj(&L1);
	ispisi(&L1);

	unesi(&L2);
	sortiraj(&L2);
	ispisi(&L2);

	printf("\nIZBORNIK:\n");
	printf("U - unija lista\nP - presjek lista\nQ - izlaz iz programa\n");
	scanf(" %c", &izbor);

	switch (toupper(izbor)) {
	case 'U':printf("\nLista koja se dobije unijom dviju listi je: \n");
			 Unija(L1.next, L2.next, &unija);
			 ispisi(&unija); break;
	case 'P':printf("\nLista koja se dobije presjekom dviju listi je: \n");
			 Presjek(L1.next, L2.next, &presjek);
			 ispisi(&presjek); break;
	case 'Q': return 0; 
	default: printf("Unijeli ste krivu komandu!\n"); return 0;
	}
	return 0;
}


