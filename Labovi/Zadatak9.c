#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node* Position;
typedef struct node Node;

struct node {
	int number;
	Position left;
	Position right;
};

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

int main() {
	Position root = NULL;

	root = insert(root, el);

	return EXIT_SUCCESS;

}
