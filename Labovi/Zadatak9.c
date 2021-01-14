#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node;
typedef struct node* Position;
typedef struct node Node;

struct node {
	int number;
	Position left;
	Position right;
};

Position findMax(Position current) {
	if (NULL == current) return NULL;

	while (current->right != NULL) {
		current = current->right;
		return current;
	}
}
Position findMin(Position current) {
	if (NULL == current) return NULL;

	while (current->left != NULL) {
		current = current->left;
		return current;
	}
}
Position insert(Position current, Position el) {
	if (current == NULL) return el;

	if (current->number > el->number) {
		current->left = insert(current->left, el);
	}
	else if (current->number < el->number) {
		current->right = insert(current->right, el);
	}
	else free(el);

	return current;
}
Position find(Position current, int number) {
	if (NULL == current) return NULL;

	if (current->number > number) {
		return find(current->left, number);
	}
	else if (current->number < number) {
		return find(current->right, number);
	}
	else return current;
}
void printInOrder(Position current) {
	if (NULL == current) return;

	printInOrder(current->left); //moguce minjat redoslijed za drugacije ispise
	printf("%d ", current->number);
	printInOrder(current->right);
}
Position deleteNode(Position current, int number) {
	if (NULL == current) return NULL; //ili return current;

	if (current->number == number) {
		/*if (current->left == NULL && current->right == NULL) {
			free(current); return NULL;
		}*/ //dodali smo na zadnji else

		if (current->left != NULL) {
			Position temp = findMax(current->left);
			current->number = temp->number;
			current->left = deleteNode(current->left, temp->number);
		}
		else if (current->right != NULL) {
			Position temp = findMin(current->right);
			current->number = temp->number;
			current->right = deleteNode(current->right, temp->number);
		}
		else free(current); return NULL;
	}
	else if (current->number > number) {
		current->left = deleteNode(current->left, number);
	}
	else /* if(current->number < number) */ {
		current->right = deleteNode(current->right, number);
	}
}
Position createNode(int number) {
	Position p = NULL;

	p = (Position)malloc(sizeof(Node));

	if (p == NULL) {
		printf("Alokacija nije uspijela\n");
		return NULL;
	}
	p->number = number;
	p->left = NULL;
	p->right = NULL;
}


int main() {
	Position root = NULL;
	Position el = NULL;
	char izbor;
	int int_root;
	int broj;
	int wantednumber;

	printf("Unesi pocetni broj stabla: \n");
	scanf("%d", &int_root);
	el = createNode(int_root);
	root = insert(root, el);

	while (1) {
		printf("Unesite nardedbu: \n");
		printf("I - insert\nF - find\nP - print\nD - delete\nE - izlaz\n");
		scanf(" %c", &izbor);
		switch (toupper(izbor)) {
		case 'I':
			printf("Unesite broj koji zelite dodati u stablo: ");
			scanf("%d", &broj);
			root = insert(root, createNode(broj));
			printf("Uneseno!\n");
			break;
		case 'F':
			printf("Unesite broj koji zelite potraziti: ");
			scanf("%d", &broj);
			puts("\n");
			wantednumber = find(root, broj);
			if (wantednumber != NULL) printf("Trazeni broj %d je pronaden!\n",broj);
			break;
			
		case 'P':
			printf("Ispis: ");
			printInOrder(root);
			break;

		case 'D':
			printf("Unesite koji broj zelite izbristai: ");
			scanf("%d", &broj);
			root = deleteNode(root, broj);
			printf("Izbrisano!\n");
			break;

		case 'E': return 0;

		default: printf("Unesena je kriva naredba!\n");	break;
		}
	}



	return EXIT_SUCCESS;

}
