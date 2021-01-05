/*Napisati program koji pomoæu vezanih listi(stabala) predstavlja strukturu direktorija.
Omoguæiti unos novih direktorija i pod - direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij.Toènije program treba preko menija simulirati
korištenje DOS naredbi : 1 - "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define str_vel 256

typedef struct stablo* pozicija;

struct stablo {
	char ime_dir[str_vel];
	pozicija roditelj;
	pozicija dijete1;
	pozicija dijete2;  //brat
};

typedef struct stablo _stablo;

// za stablo
pozicija napravi_direktorij(char*);
int dodaj_dijete1(pozicija, char*);
int dodaj_dijete2(pozicija, char*);
int pokazi_sadrzaj(pozicija);
int brisi(pozicija);

//za terminal
pozicija provjeriNaredbu(char*, pozicija);
pozicija obaviNaredbu(char*, char*, pozicija);
pozicija promijeni_dir(pozicija, char*);
pozicija prosli_dir(pozicija);


int main() {

	char unos[str_vel];
	char username[str_vel];

	pozicija tren_dir = NULL;  //trenutni direktorij je prazan

	_stablo root;
	root.dijete1 = NULL;
	root.dijete2 = NULL;
	root.roditelj = NULL;

	tren_dir = &root;     //trenutno otvoreni direktorij

	printf("\nUnesite ime root direktorija:\n");
	//scanf("%s", username);
	gets(username);

	strcpy(root.ime_dir, username);

	while (1) {

		printf("\n%s/", tren_dir->ime_dir);    //ispis trenutno otvorenog direktorija

		printf("\nUnesite input: ");
		gets(&unos);    //unos koji korisnik unosi

		//printf("\nInput je: %s", input);   //provjera


		tren_dir = provjeriNaredbu(&unos, tren_dir);   //funkcija vraca direktorij koji je trenutno otvoren

		if (tren_dir == NULL)  //ako nije otvoren nijedan direktorij, izlazi se iz programa!
			break;
	}

	brisi(root.dijete1);
	root.dijete1 = NULL;

	pokazi_sadrzaj(&root);

	return 0;
}

pozicija provjeriNaredbu(char* unos, pozicija p) {  //pozicija arg_dir

	int r = 0;
	char command[str_vel] = { 0 };
	char arg[str_vel] = { 0 };
	char* buffer;

	buffer = (char*)calloc(strlen(unos) + 20, sizeof(char));   //velicina buffera je velicina korisnikovog unosa + 20 bitova viska za svaki slucaj

	if (buffer == NULL) {
		printf("\nGreska! Memorija nije pravilno alocirana!\n");   //provjeravamo je li buffer dobro alociran
		return -1;
	}

	strcpy(buffer, unos);      //korisnikov unos prepisujemo u buffer

	printf("\nIspis buffera: %s", buffer);   //provjeravamo sto je u bufferu

	r = sscanf(buffer, "%s %s", &command, &arg);   //iz buffera citamo 


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
		return obaviNaredbu(&command, &arg, p);
	}

}

pozicija obaviNaredbu(char* command, char* arg, pozicija p) {

	if (strcmp(command, "mkdir") == 0) {

		dodaj_dijete1(p, arg);
	}

	else if (strcmp(command, "cd") == 0) {

		return promijeni_dir(p, arg);
	}

	else if (strcmp(command, "cd..") == 0) {

		return prosli_dir(p);
	}

	else if (strcmp(command, "ls") == 0) {

		pokazi_sadrzaj(p);
	}

	else if (strcmp(command, "exit") == 0) {

		printf("\nIzlazimo iz terminala");
		return NULL;
	}

	else printf("\nGreska! %s naredba ne postoji!", command);


	return p;
}

pozicija promijeni_dir(pozicija arg_p, char* arg_ime) {

	pozicija p = arg_p->dijete1;

	if (*arg_ime == '\0') { //enter
		printf("\nGreska! Ime direktorija je prazno!\n");
		return arg_p;
	}

	if (p == NULL) {
		printf("\nTrenutni direktorij je prazan!");
		return arg_p;
	}

	else if (strcmp(p->ime_dir, arg_ime) == 0) {
		//printf("\nNaden direktorij!\n");   //za provjeru
		return p;
	}

	while (p != NULL && strcmp(p->ime_dir, arg_ime) != 0) {

		p = p->dijete2;
	}

}

pozicija prosli_dir(pozicija p) {

	if (p->roditelj == NULL) {
		printf("\nGreska!");
		return p;
	}

	else
		return p->roditelj;
}

pozicija napravi_direktorij(char* ime) {

	pozicija novi_dir;

	novi_dir = (pozicija)malloc(sizeof(_stablo));

	if (novi_dir == NULL) {
		printf("\nGreska! Neuspjesna alokacija memorije za novi direktorij!\n");   //provjeravamo alokaciju memorije
		return NULL;
	}

	strcpy(novi_dir->ime_dir, ime);
	novi_dir->dijete1 = NULL;
	novi_dir->dijete2 = NULL;

	printf("\nNapravili smo novi direktorij imena: %s\n", ime);
	return novi_dir;
}

int dodaj_dijete1(pozicija p, char* ime) {

	if (p->dijete1 == NULL) {    //ako nema djeteta

		p->dijete1 = napravi_direktorij(ime);
		p->dijete1->roditelj = p;
	}

	else {    //ako vec postoji dijete, dodajemo drugo dijete
		dodaj_dijete2(p, ime);
	}

	return 0;
}

int dodaj_dijete2(pozicija p, char* ime) {    //argument je roditelj

	pozicija roditelj = p;
	pozicija prev = NULL;

	pozicija novo_dijete = napravi_direktorij(ime);
	novo_dijete->roditelj = roditelj;

	p = p->dijete1;    //p je sada prvo dijete
	prev = p;

	if (strcmp(ime, p->ime_dir) < 0) {    //ako je ime manje od imena prvog djeteta

		roditelj->dijete1 = novo_dijete;
		novo_dijete->dijete2 = p;
	}

	else {

		while (p->dijete2 != NULL & strcmp(ime, p->ime_dir) > 0) {

			prev = p;
			p = p->dijete2;
		}

		novo_dijete->dijete2 = prev->dijete2;
		prev->dijete2 = novo_dijete;
	}

	return 0;
}

int brisi(pozicija p) {

	if (p == NULL)
		return 0;

	brisi(p->dijete2);
	brisi(p->dijete1);

	printf("\nIzbrisali smo %s\n", p->ime_dir);
	free(p);

	return 0;
}

int pokazi_sadrzaj(pozicija p) {

	if (p == NULL) {
		printf("\nGreska! Pointer ima vrijednost NULL!\n");
		return -1;
	}

	if (p->dijete1 == NULL) {
		printf("\nDirektorij %s je prazan!\n", p->ime_dir);
		return 0;
	}

	p = p->dijete1;    //pokazivac ide na prvo dijete

	while (p != NULL) {

		printf("\n %s\n", p->ime_dir);
		p = p->dijete2;
	}

	return 0;
}