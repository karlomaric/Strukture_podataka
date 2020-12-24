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

int push(Pozicija, Pozicija);
int pop(Pozicija);
int ispis(Pozicija);
int velicina_Buffera(FILE * fp);
char* napravi_Buffer(FILE*);
float izr_rez_postfix_izraza(Pozicija, char*);
Pozicija newElement(float);
float* operandi(Pozicija);
int operacija(Pozicija, float*, char);

int main()
{
	FILE* fp;
	Cvor head;
	head.next = NULL;
	char* postfix_izraz;

	
	
	float rez = 0;

	fp = fopen("postfix.txt", "r");
	
	if (fp == NULL) {
		printf("\nDatoteka nije uspjesno otvorena!");
		return -1;
	}

	postfix_izraz = napravi_Buffer(fp);     //sadrzaj datoteke prepisujemo u string


	rez = izr_rez_postfix_izraza(&head, postfix_izraz);    //funkcija racuna rezultat te ce ispisivati sve korake!


	printf("\nRezultat postfix izraza je: %.2f", rez);

	return 0;
}

int operacija(Pozicija head, float* operandi, char operator) {

	float x = 0, y = 0, rez = 0;

	y = *(operandi + 0);
	x = *(operandi + 1);

	if (operandi == NULL) {
		printf("Neuspjesno pronaden operand!");
	return -1;
	}

	switch (operator) {

	case '+': head->next->br = x + y;
		break;

	case '*': head->next->br = x * y;
		break;

	case '-': head->next->br = x - y;
		break;

	case '/': head->next->br = x / y;
		break;
	}
	return 0;
}

float* operandi(Pozicija p) {       //stvara se niz koji sadrzi operande funkcije

	float* operandi = 0;
	Pozicija novi_op = NULL;

	if (p == NULL) {
		printf("Neispravan argument!!");
		return NULL;
	}

	else if (p->next == NULL || p->next->next == NULL) {
		printf("Nema dovoljno argumenata!");
		return NULL;
	}

	operandi = (float*)malloc(sizeof(float) * 2);

	*(operandi + 0) = p->next->br;
	*(operandi + 1) = p->next->next->br;

	pop(p);

	return operandi;
}

float izr_rez_postfix_izraza(Pozicija head, char* string ) {      //pozicija p = pozicija head stoga

	int i;
	char operator;
	int read_offset = 0;
	float znak=0;
	float rezultat = 0;


	while (string != EOF) {

		i = sscanf(string, "%f%n", &znak, &read_offset);

		if (i == EOF)
			break;					  //dosli smo do kraja datoteke

		if (i == 1) {
			printf("\nUcitan je broj %.2f", znak);
			push (head , newElement(znak));

			string += read_offset;
		}

		if (i == 0) {

			operator = *(string + 1);		 //+1 je zbog razmaka
			string += read_offset;

			printf("\nUcitan je znak: %c", operator);
				
			operacija(head, operandi(head), operator);
		}

		ispis(head);

		//pomice se pokazivac u stringu
	}
	rezultat = head->next->br;

	pop(head);		//skidamo zadnji clan sa stoga koji je zapravo i rezultat

	return rezultat;
}

char* napravi_Buffer(FILE* fp) {

	char* buffer;

	buffer = (char*)calloc(velicina_Buffera(fp) + 1, sizeof(char));   //alokacija buffer, podsjeti se calloca!

	fread(buffer, velicina_Buffera(fp) , 1 , fp);  //gdje spremamo, velicina pojedinog, ukupna velicina, odakle citamo? ili ovako

	return buffer;
}

int velicina_Buffera(FILE* fp) {
	int vel_buffera = 0;

	fseek(fp, 0, SEEK_END);

	vel_buffera = ftell(fp);
	//printf("\nvelicina buffera je %d", vel_buffera);

	rewind(fp);

	return vel_buffera;

}

int push(Pozicija head, Pozicija novi) {

	if (head == NULL || novi == NULL) {

		printf("Neispravni argumenti!");
		return -1;
	}

	novi->next = head->next;
	head->next = novi;

	return 0;
}

int pop(Pozicija head) {

	Pozicija temp;

	if (head->next == NULL)
		return -1;    //prazan stog!

	temp = head->next;
	head->next = temp->next;
	free(temp);

	return 0;
}

int ispis(Pozicija P) {

	P = P->next;

	if (P == NULL)
		printf("\nGRESKA! Stog je prazan!");

	else {
		printf("\nIspisujemo stog: ");
		while (P != NULL) {
			printf(" %d ", P->br);
		P = P->next;
		}
		puts("");
	}
	return 0;
}

Pozicija newElement(float arg_br) {      //stvaram novi element, i broj iz postfixa dodijelim

	Pozicija novi;

	novi = (Pozicija)malloc(sizeof(Cvor));

	novi->br = arg_br;

	return novi;
}

