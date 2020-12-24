#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct stog* Pozicija;

struct stog {

	int broj;
	Pozicija next;
};

typedef struct stog _Stog;

int push(int, Pozicija);
int pop(Pozicija);
int ispis(Pozicija);


int main() 
{
	_Stog stog1;
	stog1.next = NULL;    //prazan stog, unutra samo head element

	srand(time(0));

	int el;
	char c = 0;

	while (c != 'z') {

		printf("\nUnesite slovo za operaciju: \nd za push \np za pop \ni za ispis \nz za kraj programa.\n");
		scanf(" %c", &c);

		switch (c) {

		case 'd':
			el = rand() % (100 - 10 + 1) + 10;
			push(el, &stog1);
			break;

		case 'p':
			pop(&stog1);
			break;

		case 'i':
			ispis(stog1.next);
			break;

		case 'z':
			break;


		}
	}

	return 0;
}

int push(int el, Pozicija p) {

	Pozicija q;

	q = (Pozicija)malloc(sizeof(_Stog));

	q->broj = el;
	
	q->next = p->next;
	p->next = q;

	printf("\nU stog je unesen broj %d", el);

	return 0;
}

int pop(Pozicija p) {

	Pozicija q;

	if (p == NULL)
		printf("\nGreska! Stog je prazan!");
	
	else {

		printf("\nSkidamo sa stoga element %d", p->next->broj);
		q = p->next;
		p->next = q->next;

		free(q);
	}

	return 0;
}

int ispis(Pozicija p) {

	if (p == NULL)
		printf("\nStog je prazan!");

	else {
		printf("\nIspisujemo stog:\n");
		while (p != NULL) {
			printf("%d ", p->broj);
			p = p->next;
		}
		puts("");
	}

	return 0;
}