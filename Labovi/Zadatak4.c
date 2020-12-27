#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct polinom polinom;
typedef struct polinom* ppol;
struct polinom {
	int koef;
	int eksp;
	ppol next;
};

int unosFILE(ppol p) {
	FILE* fp;
	char imedatoteke[32];
	ppol temp = NULL;
	static int brojac = 1;

	printf("Unesite naziv datoteke gdje se nalazi %d. polinom! (ime_datoteke.txt)\n", brojac);
	scanf(" %s", imedatoteke);

	fp = fopen(imedatoteke, "r");
	if (fp == NULL) {
		printf("Datoteka nije uspjesno otvorena!\n");
		return -1;
	}
	rewind(fp);
	while (!feof(fp)) {
		temp = (ppol)malloc(sizeof(polinom));
		fscanf(fp, "%d %d ", &temp->koef, &temp->eksp);
		temp->next = p->next;
		p->next = temp;
		p = temp;
	}
	if (temp != NULL) {
		printf("Polinom je uspjesno ucitan!\n");
	}
	fclose(fp);
	brojac++;
	return 0;
}

int ispis(ppol p) {
	p = p->next;

	while (p != NULL) {
		if (p->eksp == 0) {
			printf("%d + ", p->koef);
		}
		else if (p->eksp == 1) {
			printf("%dx + ", p->koef);
		}
		else if (p->next == NULL) {
			printf("%dx^%d", p->koef, p->eksp);
		}
		else {
			printf("%dx^%d + ", p->koef, p->eksp);
		}
		p = p->next;
	}
	printf("\n");

	return 0;
}

int sortiranje(ppol p) {
	ppol q, q_prije, temp, kraj;
	kraj = NULL;

	while (p->next != kraj) {
		q_prije = p;
		q = p->next;

		while (q->next != kraj) {
			if (q->eksp > q->next->eksp) {
				temp = q->next;
				q_prije->next = temp;
				q->next = temp->next;
				temp->next = q;
				q = temp;
			}
			q_prije = q;
			q = q->next;
		}
		kraj = q;
	}
	return 0;
}

int zbrajanje(ppol poli1, ppol poli2, ppol suma) {
	ppol q, temp;
	temp = suma;

	printf("\nZbroj polinoma je:\n");

	while (poli1 != NULL && poli2 != NULL) {
		if (poli1->eksp < poli2->eksp) {
			q = (ppol)malloc(sizeof(polinom));

			q->eksp = poli1->eksp;
			q->koef = poli1->koef;

			q->next = suma->next;
			suma->next = q;

			poli1 = poli1->next;
			suma = suma->next;
		}
		else if (poli1->eksp > poli2->eksp) {
			q = (ppol)malloc(sizeof(polinom));

			q->eksp = poli2->eksp;
			q->koef = poli2->koef;

			q->next = suma->next;
			suma->next = q;

			poli2 = poli2->next;
			suma = suma->next;
		}
		else if (poli1->eksp == poli2->eksp) {
			q = (ppol)malloc(sizeof(polinom));

			q->eksp = poli2->eksp;
			q->koef = poli2->koef + poli1->koef;


			q->next = suma->next;
			suma->next = q;

			poli1 = poli1->next;
			poli2 = poli2->next;

			suma = suma->next;
		}
		if (poli1 != NULL) {
			while (poli1 != NULL) {
				q = (ppol)malloc(sizeof(polinom));

				q->koef = poli1->koef;
				q->eksp = poli1->eksp;

				q->next = suma->next;
				suma->next = q;

				poli1 = poli1->next;
				suma = suma->next;
			}
		}
		if (poli2 != NULL) {
			while (poli2 != NULL) {
				q = (ppol)malloc(sizeof(polinom));

				q->koef = poli2->koef;
				q->eksp = poli2->eksp;

				q->next = suma->next;
				suma->next = q;

				poli2 = poli2->next;
				suma = suma->next;
			}
		}
	
	
	
	}


}

int mnozenje(ppol poli1, ppol poli2, ppol produkt) {
	ppol q, temp;
	ppol p2;

	temp = produkt;
	p2 = poli2;

	printf("\nUmnozak polinoma je: \n");

	while (poli1 != NULL) {

		while (poli2 != NULL) {

			q = (ppol)malloc(sizeof(polinom));

			q->eksp = poli1->eksp + poli2->eksp;
			q->koef = poli1->koef * poli2->koef;

			q->next = produkt->next;
			produkt->next = q;

			produkt = produkt->next;

			poli2 = poli2->next;
		}

		poli1 = poli1->next;
		poli2 = p2;
	}


}

int zbrajanje_clanova(ppol p) {
	ppol prije, q, posli;

	prije = p;
	q = p->next;
	posli = q->next;

	while (posli != NULL) {
		if (q->eksp == posli->eksp) {
			posli->koef = posli->koef + q->koef;

			prije->next = posli;

			free(q);

			q = posli;
			posli = posli->next;
			posli = prije;
		}
		else {

			prije = q;
			q = posli;
			posli = posli->next;
		}
				
	}
}







int main() {
	polinom prvipol, drugipol, suma, produkt;

	prvipol.next = NULL;
	drugipol.next = NULL;
	suma.next = NULL;
	produkt.next = NULL;

	char izbor;

	unosFILE(&prvipol);
	sortiranje(&prvipol);
	ispis(&prvipol);

	unosFILE(&drugipol);
	sortiranje(&drugipol);
	ispis(&drugipol);

	printf("\nIZBORNIK:\n");
	printf("Z - zbrajanje polinoma\nM - mnozenje polinoma\nQ - izlaz iz programa\n");
	scanf(" %c", &izbor);
	
	switch (toupper(izbor)) {
		case 'Z': zbrajanje(prvipol.next, drugipol.next, &suma);
			sortiranje(&suma);
			zbrajanje_clanova(&suma);
			ispis(&suma);
			break;

		case 'M': mnozenje(prvipol.next, drugipol.next, &produkt);
			sortiranje(&produkt);
			zbrajanje_clanova(&produkt);
			ispis(&produkt);
			break;
		case 'Q': return 0;

		default: printf("Unijeli ste krivu naredbu!\n"); return 0;
		}
	


	return 0;
}
