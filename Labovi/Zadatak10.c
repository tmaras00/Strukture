#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define data_size 11

struct tree;
typedef struct tree* treePosition;

typedef struct tree {

	char data[data_size];
	treePosition left;
	treePosition right;

}Tree;


struct list;
typedef struct list* listPosition;

typedef struct list {

	treePosition treeNode;
	listPosition next;
}List;


treePosition create(char* data);
int pushFront(listPosition head, treePosition treeNode);
int pushBack(listPosition head, treePosition treeNode);
treePosition popFront(listPosition head);
treePosition ReadFromFile(char* fileName);
int isNumber(char* data);
void PrintInOrder(listPosition head, treePosition current);


int main(void) {

	char filename[1024] = { 0 };
	printf("Unesite ime datoteke: ");
	scanf(" %s", filename);

	treePosition test = ReadFromFile(filename);
	if (test == NULL)
	{
		return 1;
	}
	List head;
	head.next = NULL;
	PrintInOrder(&head, test);

	listPosition p;
	for (p = head.next, p != NULL; p = p->next;)
	{
		printf("%s ", p->treeNode->data);
	}
	printf("\n");
	return 0;
}


treePosition create(char* data) {

	treePosition node = NULL;
	node = (treePosition)malloc(sizeof(Tree));

	if (node == NULL) {
		printf("Greska! Nije alocirano!");
		return -1;
	}

	strcpy(node->data, data);
	node->left = NULL;
	node->right = NULL;
	return node;
}

int pushFront(listPosition head, treePosition treeNode)
{
	listPosition listNode = (listPosition)malloc(sizeof(List));

	if (listNode == NULL) {
		printf("Greska! Nije alocirano!");
		return -1;
	}

	listNode->treeNode = treeNode;
	listNode->next = head->next;
	head->next = listNode;

	//return 0;
}

int pushBack(listPosition head, treePosition treeNode)
{
	listPosition temp = head;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return pushFront(temp, treeNode);
}

treePosition popFront(listPosition head) {

	listPosition first = head->next;
	treePosition result = NULL;

	if (first == NULL)
	{
		return NULL;  //0
	}

	head->next = first->next;
	result = first->treeNode;
	free(first);

	return result;
}

treePosition ReadFromFile(char* fileName) {

	FILE* fp = NULL;
	List head;
	head.next = NULL;
	treePosition result = NULL;

	fp = fopen(fileName, "r");

	if (fp == NULL)
	{
		printf("Greska! Datoteka %s ne postoji!\n", fileName);
		return NULL;  //0
	}
	else {
		while (!feof(fp))
		{
			treePosition node = NULL;  //node je root?
			char data[256] = { 0 };
			fscanf(fp, " %s", &data);

			node = create(data);
			if (node == NULL)
			{
				printf("\nGreska! Zatvara se datoteka!");
				fclose(fp);
				return NULL;  //0
			}

			if (isNumber(data) != 0)			//isto je kao da pise if(isNumber(data))
			{
				pushFront(&head, node);
			}
			else
			{
				if (node == NULL)
				{
					printf("\nKrivi postfix zapis3!");
					return 0;
				}
				node->right = popFront(&head);  //?
				if (NULL == node->right)
				{
					printf("Krivi postfix zapis!\r\n", fileName);
					return NULL;
				}

				node->left = popFront(&head);
				pushFront(&head, node);
			}
		}

	}
	result = popFront(&head);
	if (result == NULL)
	{
		printf("\nKrivi postfix zapis1!");
	}
	if (popFront(&head) != NULL)
	{
		printf("\nKrivi postfix zapis2!");
	}
	else
	{
		return result;
	}
}

int isNumber(char* data) {

	int number = 0;

	if (sscanf(data, " %d", &number) == 1)
	{
		return 1;
	}

	return 0;
}

void PrintInOrder(listPosition head, treePosition current)
{
	if (current == NULL)
	{
		return;
	}
	else
	{
		PrintInOrder(head, current->left);

		pushBack(head, current);

		PrintInOrder(head, current->right);
	}
}
