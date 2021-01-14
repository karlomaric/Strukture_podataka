#include <stdio.h>
#include <stdlib.h>

typedef struct cvor;
typedef struct cvor* Pozicija;

struct cvor {

	int br;
	Pozicija Lijevo;
	Pozicija Desno;
} _cvor;

Pozicija stvoriCvor(int);
Pozicija unesi(Pozicija trenutna, Pozicija element);
Pozicija trazi(Pozicija trenutna, int broj);
void ispisi_inorder(Pozicija trenutna);
Pozicija brisi(Pozicija trenutna, int broj);
Pozicija traziMax(Pozicija trenutna);
Pozicija traziMin(Pozicija trenutna);

int main()
{
	Pozicija root = NULL;     //root je nula jer je stablo prazno (ne postoji head element u stablima), tj. root pokazuje na pranzo

	int numb, a, trazeni_broj;

	char c = 0;
	while (c != 'e') {

		printf("\nOperacija:\n");
		printf("u - unesi\ni- ispisi\nt- trazi element\no- obrisi\ne- end\n");
		scanf(" %c", &c);

		switch (c) {

		case 'u':

			printf("Unesi broj: ");
			scanf("%d", &a);
			printf("\n");
			root = unesi(root, a);
			break;

		case 'i':

			ispisi_inorder(root);
			break;

		case 'o':
			printf("Unesi broj koji zelis izbrisat:");
			scanf("%d", &a);
			printf("\n");
			root = brisi(root, a);

			break;

		case't':
			printf("Unesi trazeni broj:");
			scanf("%d", &a);
			printf("\n");
			trazeni_broj = trazi(root, a);
			if (trazeni_broj != NULL)
				printf("Broj %d je pronaden.\n", a);
			break;

		default:
			break;
		}

	}
	return 0;
}


Pozicija unesi(Pozicija trenutna, int element) {

	if (NULL == trenutna) {

		trenutna = (Pozicija)malloc(sizeof(_cvor));

		trenutna->br = element;
		trenutna->Lijevo = NULL;
		trenutna->Desno = NULL;

	}


	else if (trenutna->br > element) {
		trenutna->Lijevo = unesi(trenutna->Lijevo, element);
	}
	else if (trenutna->br < element) {
		trenutna->Desno = unesi(trenutna->Desno, element);
	}
	else {
		printf("\nGreska! Duplikat!");
		free(element);
	}

	return trenutna;
}

Pozicija trazi(Pozicija trenutna, int broj) {

	if (NULL == trenutna) {
		printf("Broj ne postoji!\n");
		return NULL;
	}

	if (trenutna->br == broj)
		return trenutna->br;

	else if (trenutna->br < broj)
		trazi(trenutna->Desno, broj);

	else
		trazi(trenutna->Lijevo, broj);

}

void ispisi_inorder(Pozicija trenutna) {

	if (NULL == trenutna)
		return NULL;

	ispisi_inorder(trenutna->Lijevo);
	printf("%d ", trenutna->br);
	ispisi_inorder(trenutna->Desno);
}

Pozicija brisi(Pozicija trenutna, int broj) {

	if (NULL == trenutna)
		return NULL;

	if (trenutna->br == broj) {
		if (trenutna->Lijevo == NULL && trenutna->Desno == NULL) {

		}
		if (trenutna->Lijevo != NULL) {
			Pozicija temp = traziMax(trenutna->Lijevo);
			trenutna->br = temp->br;
			trenutna->Lijevo = brisi(trenutna->Lijevo, temp->br);
		}
		else if (trenutna->Desno != NULL) {
			Pozicija temp = traziMin(trenutna->Desno);
			trenutna->br = temp->br;
			trenutna->Desno = brisi(trenutna->Desno, temp->br);
		}
		else {
			free(trenutna);
			return NULL;
		}
	}
	else if (trenutna->br > broj) {
		trenutna->Lijevo = brisi(trenutna->Lijevo, broj);
	}
	else {   //(trenutna->br < broj)
		trenutna->Desno = brisi(trenutna->Desno, broj);
	}
	printf("Broj ne postoji!\n");
	return trenutna;
}

Pozicija traziMax(Pozicija trenutna) {

	if (NULL == trenutna)
		return NULL;
	while (trenutna->Desno != NULL) {
		trenutna = trenutna->Desno;
	}
	return trenutna;
}

Pozicija traziMin(Pozicija trenutna) {

	if (NULL == trenutna)
		return NULL;
	while (trenutna->Lijevo != NULL) {
		trenutna = trenutna->Lijevo;
	}
	return trenutna;
}