#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//typedef struct osoba OSOBA;
typedef struct osoba* Pozicija;

struct osoba {

	char ime[50];
	char prezime[50];
	int g_rod;
	Pozicija next;
};

int ispis(Pozicija); //i
int upisK(Pozicija); //uk
Pozicija trazi_prez(Pozicija); //tr_p
int brisi_el(Pozicija); //br
int upis_iza(Pozicija);  //u_iz
int upis_prije(Pozicija); //u_pr
Pozicija trazi_prethodni(Pozicija); // tr_pr
void sortiraj(Pozicija); // s
int u_dat(Pozicija); // u_dat
int iz_dat(Pozicija); //iz_dat


int main()

{
	struct osoba head;				 //OSOBA head, pocetni clan liste
	head.next = NULL;					 //prvi clan liste pokazuje na nista jer je zasad head jedini clan u listi
	struct osoba head_iz_dat;				//pocetni clan liste (koja se cita iz datoteke)
	head_iz_dat.next = NULL;					// prvi clan liste pokazuje na nista jer je zasad jedini u listi

	
	//upisP(&head);
	////upisP(&head);
	//upisK(&head);
	////ispis(head.next);
	//trazi_prez(&head);
	//brisi_el(&head);
	//ispis(head.next);
	////upis_iza(&head);
	////ispis(head.next);
	////upis_prije(&head);
	////ispis(head.next);
	////sortiraj(&head);
	////printf("\nIspis sortirane liste:\n");
	////ispis(head.next);
	//u_dat(&head);
	iz_dat(&head_iz_dat);
	//ispis(head.next);

	return 0;
}

//prilikom upisivanja gleda se di ce se ubacit (koristit strcmp, tj, dok je to prezime manje/vece od sljedeceg novog))

int upisP(Pozicija P) {

	Pozicija tmp = NULL;

	tmp = (Pozicija)malloc(sizeof(struct osoba));

	if (!tmp) {										 // if(tmp == NULL) 
		printf("\nNije uspjela alokacija memorije!\n");
	}
	printf("Unesite podatke o osobi:\n");
	scanf("%s %s %d", tmp->ime, tmp->prezime, &tmp->g_rod);

	tmp->next = P->next;
	P->next = tmp;

	return 0;
}

int ispis(Pozicija P)
{
	printf("\nIspis ljudi:\n");
	while (P != NULL) {
		printf("%s %s %d\n", P->ime, P->prezime, P->g_rod);
		P = P->next;
	}
	return 0;
}

int upisK(Pozicija P) {

	Pozicija tmp= NULL; 
	tmp = (Pozicija)malloc(sizeof(struct osoba));		 //nova struktura

	if (!tmp) {
		printf("\nNije uspjela alokacija memorije!\n");
	}

	printf("Unesite podatke o osobi:\n");
	scanf("%s %s %d", tmp->ime, tmp->prezime, &tmp->g_rod);

	while (P->next != NULL)
		P = P->next;

	P->next = tmp;
	tmp->next = NULL;

	return 0;
}

Pozicija trazi_prez(Pozicija P) {

	char prezime[50];											 //odi upisujemo prezime koje trazimo

	printf("\nUpisite prezime koje trazimo\n");
	scanf("%s", prezime);

	while (P->next != NULL && strcmp(prezime, P->prezime) != 0)  //dok ne dodemo do zadnjeg clana ili dok ne nademo trazeno prezime
	{
		P = P->next;												 // prebacujemo na sljedeci clan
	}

	if (strcmp(prezime, P->prezime) == 0)							 // nasli smo prezime
		printf("Trazeno prezime je pronadeno: %s %s %d\n", P->ime, P->prezime, P->g_rod);   // ispisujemo osobu sa trazenim prezimenom

	else if (strcmp(prezime, P->prezime) != 0)						//nismo nasli prezime
		printf("\nOsoba sa trazenim prezimenom nije pronadena!");

	return P;

}

int brisi_el(Pozicija P) {

	Pozicija prije = NULL;
	char prezime[50];

	prije = (Pozicija)malloc(sizeof(struct osoba));     

	if (!prije) {
		printf("\nNije uspjela alokacija memorije!");

	}

	printf("\nUnesite prezime osobe koju zelimo ukloniti:\n");
	scanf("%s", prezime);

	while (P->next != NULL && strcmp(prezime, P->prezime) != 0) {  //isti uvjet kao i kod trazi_prez

		prije = P;
		P = P->next;							//idemo na sljedeci clan
	}

	if (strcmp(prezime, P->prezime) == 0) {    //ako smo pronasli trazeno prezime

		prije->next = P->next;
		free(P);								//brisemo element iz liste, tj. oslobadamo memoriju
	}
	else if (strcmp(prezime, P->prezime) != 0)         // ako nismo pronasli trazeno prezime
		printf("Trazeno prezime nije nadeno u listi");

	return 0;
}

int upis_iza(Pozicija P) {

	Pozicija novi;
	Pozicija trazeni;

	novi = (Pozicija)malloc(sizeof(struct osoba));  //alociramo memoriju za novi clan koji dodajemo

	if (!novi) {
		printf("\nNije uspjela alokacija memorije");
	}

	trazeni = trazi_prez(P);

	novi->next = trazeni->next;
	trazeni->next = novi;

	printf("\nUnesite podatke o osobi koju novu zelimo dodati iza odredenog prezimena:\n");
	scanf("%s %s %d", novi->ime, novi->prezime, &novi->g_rod);

	return 0;

}

Pozicija trazi_prethodni(Pozicija P) {

	char prezime[50];					//odi upisujemo prezime koje trazimo
	Pozicija prethodni;

	printf("\nUpisite prezime koje trazimo\n");
	scanf("%s", prezime);

	while (P->next != NULL && strcmp(prezime, P->prezime) != 0)  //dok ne dodemo do zadnjeg clana ili dok ne nademo trazeno prezime
	{
		prethodni = P;												// pridajemo vrijednost prethodnom
		P = P->next;												 // prebacujemo na sljedeci clan
	}

	if (strcmp(prezime, P->prezime) == 0) {							 // nasli smo prezime
		printf("Trazeno prezime je pronadeno: %s %s %d\n", P->ime, P->prezime, P->g_rod);   // ispisujemo osobu sa trazenim prezimenom
		return prethodni;
	}

	else if (strcmp(prezime, P->prezime) != 0) {					//nismo nasli prezime
		printf("\nOsoba sa trazenim prezimenom nije pronadena!");
		return NULL;
	}
		
}

int upis_prije(Pozicija P) {

	Pozicija novi = NULL;
	Pozicija prethodni;

	prethodni = trazi_prethodni(P);

	novi = (Pozicija*)malloc(sizeof(struct osoba));

	if (!novi) {
		printf("\nNije uspjela alokacija memorije!");
	}

	novi->next = prethodni -> next;
	prethodni->next = novi;

	printf("\nUnesite podatke o osobi koju novu zelimo dodati prije odredenog prezimena:\n");
	scanf("%s %s %d", novi->ime, novi->prezime, &novi->g_rod);

	return 0;
}

void sortiraj(Pozicija P) {

	Pozicija pret, end, tmp, i;

	end = NULL;

	while (P->next != end) {

		pret = P;
		i = P->next;

		while (i->next != end)
		{

			if (strcmp(i->prezime, i->next->prezime) > 0) {

				tmp = i->next;
				pret->next = tmp;
				i->next = tmp->next;
				tmp->next = i;

				i = tmp;
			}
			pret = i;
			i = i->next;
		}
		end = i;
	}

}

int u_dat(Pozicija P) {

	FILE* fp = NULL;

	fp = fopen("osobe.txt", "w");

	if (fp == NULL) {
		printf("Datoteka nije uspjesno otvorena!\n");
		return -1;
	}

	while (P != NULL) {
			 
			fprintf(fp, "\n%s\t%s\t%d", P->ime, P->prezime, P->g_rod);   //ispisuje mi prvo neku ?trash? vrijednost,a tek onda osobe, jos pogledat sutra!
			P = P->next;
	}
	
	printf("\nUpisivanje u datoteku je zavrseno!");
	fclose(fp);
	return 0;
}

int iz_dat(Pozicija P) {

	FILE* fp = NULL;
	Pozicija tmp, novi;

	fp = fopen("osobe.txt", "r");
	
	if (fp == NULL) {

		printf("\nGRESKA!!! Datoteka nije uspjesno otvorena!\n");
		return -1;
	}

	//tmp = P;
	//tmp->next = P->next;

	while (!feof(fp)) {

		novi = (Pozicija)malloc(sizeof(struct osoba));

		if (!novi) {
			printf("\nAlokacija memorije nije uspjela!!");
		}

		fscanf(fp, "%s %s %d", novi->ime, novi->prezime, &novi->g_rod);

		novi->next = P->next;
		P->next = novi;
		P = novi;

		printf("%s %s %d\n", novi->ime, novi->prezime, novi->g_rod);

	}
	fclose(fp);

	printf("\nCitanje iz datoteke je gotovo!");
	
	return 0;
}