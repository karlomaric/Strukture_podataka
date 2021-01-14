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

	Pozicija el = stvoriCvor(16);

	root = unesi(root, el);


	return EXIT_SUCCESS;
}

Pozicija stvoriCvor(int broj) {

	Pozicija p = NULL;

	p = (Pozicija)malloc(sizeof(_cvor));

	if (NULL == p) {
		printf("\nGreska! Memorija se nije ispravno alocirala1");
		return NULL;
	}

	p->br = broj;
	p->Lijevo = NULL;
	p->Desno = NULL;
}

Pozicija unesi(Pozicija trenutna, Pozicija element) {

	if (NULL == trenutna)
		return element;

	if (trenutna->br > element->br) {
		trenutna->Lijevo = unesi(trenutna->Lijevo, element);
	}
	else if (trenutna->br < element->br) {
		trenutna->Desno = unesi(trenutna->Desno, element);
	}
	else {
		free(element);
	}

	return trenutna;
}

Pozicija trazi(Pozicija trenutna, int broj) {

	if (NULL == trenutna)
		return NULL;

	if (trenutna->br > broj) {
		return trazi(trenutna->Lijevo, broj);
	}
	else if (trenutna->br < broj) {
		return trazi(trenutna->Desno, broj);
	}
	else
		return trenutna;
}

void ispisi_inorder(Pozicija trenutna) {

	if (NULL == trenutna)
		return;

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
			Pozicija temp = traziMin(trenutna->Desno);  //trenutna->Lijevo
			trenutna->br = temp->br;
			trenutna->Desno = brisi(trenutna->Desno, temp->br);   //current->left = deleteNode(current->left, tmp->number)??
		}
		else {
			free(trenutna);
			return NULL;
		}
	}
	else if (trenutna->br > broj) {   // <?
		trenutna->Lijevo = brisi(trenutna->Lijevo, broj);
	}
	else {   //(trenutna->br < broj)
		trenutna->Desno = brisi(trenutna->Desno, broj);
	}
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