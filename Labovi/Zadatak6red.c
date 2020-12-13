#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

typedef struct cvor* Pozicija;

struct cvor {

	int br;
	Pozicija next;
	Pozicija last;
};

typedef struct cvor Cvor;


int push(Pozicija last);			//stavi u red
int pop(Pozicija prvi);				//izvadi iz reda


int main()
{
	Cvor head;
	head.next = NULL;
	head.last = NULL;

	srand(time(0));

	push(&head);
	push(&head);
	push(&head);

	printf("\nIspis reda: %d %d %d", pop(&head), pop(&head), pop(&head));

	return 0;
}


int push(Pozicija last) {			//salje se head element!

	Pozicija p, q = NULL;
	p = last;

	while (p->next != NULL)
		p = p->next;

	q = (Pozicija)malloc(sizeof(Cvor));

	q->br = rand() % (100 - 10 + 1) + 10;
	printf("%d\n", q->br);

	q->next = p->next;
	p->next = q;

	return 0;
}

int pop(Pozicija prvi) {

	Pozicija temp, p;
	p = prvi;
	int x;

	temp = p->next;
	x = temp->br;
	p->next = temp->next;
	free(temp);

	return x;
} 
