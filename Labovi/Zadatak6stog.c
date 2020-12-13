#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

typedef struct cvor* Pozicija;

struct cvor {

	int br;
	Pozicija next;
};

typedef struct cvor Cvor;

int push(Pozicija);
int pop(Pozicija);


int main()
{
	srand(time(0));
	Cvor head;
	head.next = NULL;

	push(&head);
	push(&head);
	push(&head);
	printf("\nIspis stoga: %d %d %d\n", pop(&head), pop(&head), pop(&head));

	return 0;
}

int push(Pozicija stog) {

	Pozicija q;
	q = (Pozicija)malloc(sizeof(Cvor));

	q->br = rand() % (100 - 10 + 1) + 10;
	printf("%d\n", q->br);
	q->next = stog->next;
	stog->next = q;

	return 0;
}

int pop(Pozicija stog) {

	Pozicija temp;
	int x;

	if (stog->next == NULL)
		return -1;

	temp = stog->next;
	stog->next = temp->next;
	x = temp->br;
	free(temp);

	return x;
}
