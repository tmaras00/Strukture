#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VEL 256

typedef struct stablo* Pozicija;

struct stablo {
	char imeDir[MAX_VEL];
	Pozicija roditelj;
	Pozicija dijete;
	Pozicija brat; 
};

typedef struct stablo Stablo;

//stablo
Pozicija makeDir(char*);
int addDijete(Pozicija, char*);
int addBrat(Pozicija, char*);
int show(Pozicija);
int brisi(Pozicija);

//terminal
Pozicija checkCmd(char*, Pozicija);
Pozicija doCmd(char*, char*, Pozicija);
Pozicija changeDir(Pozicija, char*);
Pozicija lastDir(Pozicija);


int main() {

	char unos[MAX_VEL];
	char username[MAX_VEL];

	Pozicija tren_dir = NULL;  

	Stablo root;
	root.dijete = NULL;
	root.brat = NULL;
	root.roditelj = NULL;

	tren_dir = &root;     

	printf("\nUnesite ime root direktorija:\n");
	//scanf(" %s", username);
	gets(username);

	strcpy(root.imeDir, username);

	while (1) {

		printf("Komande su:     mkdir (dir)\n\t\tcd (dir)\n\t\tcd..\n\t\tls\n\t\texit\n");
		printf("\n%s/\n", tren_dir->imeDir);    //ispis otvorenog direktorija
		printf("\nUnesite input: ");
		gets(&unos);    //unos

		tren_dir = checkCmd(&unos, tren_dir);   //funkcija vraca trenutno otvoren direktorij

		if (tren_dir == NULL)  
			break;
	}

	brisi(root.dijete);
	root.dijete = NULL;

	show(&root);

	return 0;
}

Pozicija checkCmd(char* unos, Pozicija p) {  //Pozicija arg_dir

	int r = 0;
	char command[MAX_VEL] = { 0 };
	char arg[MAX_VEL] = { 0 };
	char* buffer;

	buffer = (char*)calloc(strlen(unos), sizeof(char));   

	if (buffer == NULL) {
		printf("\nGreska! Memorija nije pravilno alocirana!\n");   
		return -1;
	}

	strcpy(buffer, unos);      

	r = sscanf(buffer, "%s %s", &command, &arg);   

	if (*command == '\0')
		return p;
	if (r == -1) {
		printf("\nFATAL ERROR\n");
		return p;
	}
	if (r == 0) {
		printf("\nINPUT ERROR\n");
		return p;
	}
	else {
		return doCmd(&command, &arg, p);
	}
}

Pozicija doCmd(char* command, char* arg, Pozicija p) {

	if (strcmp(command, "mkdir") == 0) {
		addDijete(p, arg);
	}
	else if (strcmp(command, "cd") == 0) {
		return changeDir(p, arg);
	}
	else if (strcmp(command, "cd..") == 0) {
		return lastDir(p);
	}
	else if (strcmp(command, "ls") == 0) {
		show(p);
	}
	else if (strcmp(command, "exit") == 0) {
		printf("\nIzlazimo iz terminala..");
		return NULL;
	}
	else printf("\nGreska! %s naredba ne postoji!", command);
	return p;
}

Pozicija changeDir(Pozicija arg_p, char* arg_ime) {

	Pozicija p = arg_p->dijete;

	if (*arg_ime == '\0') { //enter
		printf("\nGreska! Ime direktorija je prazno!\n");
		return arg_p;
	}
	if (p == NULL) {
		printf("\nTrenutni direktorij je prazan!");
		return arg_p;
	}
	else if (strcmp(p->imeDir, arg_ime) == 0) {
		//printf("\nNaden direktorij!\n");   //za provjeru
		return p;
	}
	while (p != NULL && strcmp(p->imeDir, arg_ime) != 0) {

		p = p->brat;
	}
}

Pozicija lastDir(Pozicija p) {

	if (p->roditelj == NULL) {
		printf("\nGreska!");
		return p;
	}
	else
		return p->roditelj;
}

Pozicija makeDir(char* ime) {

	Pozicija novi_dir;
	novi_dir = (Pozicija)malloc(sizeof(Stablo));

	if (novi_dir == NULL) {
		printf("\nGreska! Neuspjesna alokacija memorije!\n");   
		return NULL;
	}
	strcpy(novi_dir->imeDir, ime);
	novi_dir->dijete = NULL;
	novi_dir->brat = NULL;

	printf("\nNapravljen je novi direktorij: %s\n", ime);
	return novi_dir;
}

int addDijete(Pozicija p, char* ime) {

	if (p->dijete == NULL) {    

		p->dijete = makeDir(ime);
		p->dijete->roditelj = p;
	}
	else {    
		addBrat(p, ime);
	}
	return 0;
}

int addBrat(Pozicija p, char* ime) {    //arg roditelj

	Pozicija roditelj = p;
	Pozicija prev = NULL;

	Pozicija novo_dijete = makeDir(ime);
	novo_dijete->roditelj = roditelj;

	p = p->dijete;    
	prev = p;

	if (strcmp(ime, p->imeDir) < 0) {   
		roditelj->dijete = novo_dijete;
		novo_dijete->brat = p;
	}
	else {

		while (p->brat != NULL & strcmp(ime, p->imeDir) > 0) {
			prev = p;
			p = p->brat;
		}
		novo_dijete->brat = prev->brat;
		prev->brat = novo_dijete;
	}
	return 0;
}

int brisi(Pozicija p) {

	if (p == NULL)
		return 0;

	brisi(p->brat);
	brisi(p->dijete);

	printf("\nIzbrisali smo %s\n", p->imeDir);
	free(p);
	return 0;
}

int show(Pozicija p) {

	if (p == NULL) {
		printf("\nGreska! Pointer ima vrijednost NULL!\n");
		return -1;
	}
	if (p->dijete == NULL) {
		printf("\nDirektorij %s je prazan!\n", p->imeDir);
		return 0;
	}

	p = p->dijete;   

	while (p != NULL) {
		printf("\n %s\n", p->imeDir);
		p = p->brat;
	}
	return 0;
}
