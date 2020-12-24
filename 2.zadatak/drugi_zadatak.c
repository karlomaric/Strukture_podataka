#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct osoba;

typedef struct osoba* Pozicija;  

struct osoba {

	char ime[50];
	char prezime[50];
	int g_rod;
	Pozicija next;
};

void upisP(Pozicija);
void ispis(Pozicija);
void upisK(Pozicija);
void trazi_prez(Pozicija);
void brisi_el(Pozicija);

int main() 

{
	struct osoba head;
	head.next = NULL;
	upisP(&head);
	upisP(&head);
	upisK(&head);
	ispis(head.next);
	trazi_prez(&head);
	brisi_el(&head);
	ispis(head.next);
}

void upisP(Pozicija P) {

	Pozicija tmp;

	tmp = (Pozicija)malloc(sizeof(struct osoba));

	printf("Unesite podatke o osobi:\n");
	scanf("%s %s %d", tmp->ime, tmp->prezime, &tmp->g_rod);

	tmp->next = P->next;
	P->next = tmp;
	
}

void ispis(Pozicija P)
{
	printf("\nIspis ljudi:\n");
	while (P != NULL) {
		printf("%s %s %d\n", P->ime, P->prezime, P->g_rod);
		P = P->next;
	}
}

void upisK(Pozicija P) {

	Pozicija tmp;
	tmp = (Pozicija)malloc(sizeof(struct osoba));  //nova struktura

	printf("Unesite podatke o osobi:\n");
	scanf("%s %s %d", tmp->ime, tmp->prezime, &tmp->g_rod);

	while (P->next != NULL) 
		P = P->next;

	P->next = tmp;
	tmp->next = NULL;
}

void trazi_prez(Pozicija P) {

	char prezime[50];  //odi upisujemo prezime koje trazimo

	printf("\nupisite prezime koje trazimo\n");
	scanf("%s", prezime);

	while (P->next != NULL && strcmp(prezime, P->prezime) != 0)  //dok ne dodemo do zadnjeg clana ili dok ne nademo trazeno prezime
	{
		P = P->next;  // prebacujemo na sljedeci clan
	}
	
	if (strcmp(prezime, P->prezime) == 0)    // nasli smo prezime
		printf("Trazeno prezime je pronadeno: %s %s %d\n", P->ime, P->prezime, P->g_rod);   // ispisujemo osobu sa trazenim prezimenom

	else if (strcmp(prezime, P->prezime) != 0)  //nismo nasli prezime
		printf("\nOsoba sa trazenim prezimenom nije pronadena!");

}

void brisi_el(Pozicija P) {

	Pozicija prije;
	char prezime[50];

	prije = (Pozicija)malloc(sizeof(struct osoba));     //

	printf("\nUnesite prezime osobe koju zelimo ukloniti:\n");
	scanf("%s", prezime);

	while (P->next != NULL && strcmp(prezime, P->prezime) != 0) {  //isti uvjet kao i kod trazi_prez

		prije = P;			
		P = P->next;							//idemo na sljedeci clan
	}

	if (strcmp(prezime, P->prezime) == 0) {    //ako smo pronasli trazeno prezime

		prije->next = P->next;  
		free(P);    //brisemo element iz liste, tj. oslobadamo memoriju
	  }
	else if (strcmp(prezime, P->prezime) != 0)         // ako nismo pronasli trazeno prezime
		printf("Trazeno prezime nije nadeno u listi");
}