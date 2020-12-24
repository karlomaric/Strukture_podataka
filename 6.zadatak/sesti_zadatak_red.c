#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct red* Pozicija;

struct red {

	int broj;
	Pozicija next;

};

typedef struct red _Red;

int push(int, Pozicija);
int pop(Pozicija);
int ispis(Pozicija);

int main()
{
	_Red red1;   //kao head element
	red1.next = NULL;   //prazan je red, samo "head" element unutra

	srand(time(0));

	int el;
	char c = 0;

	while (c != 'z') {

		printf("\nUnesite slovo za operaciju: \nd za push \np za pop \ni za ispis \nz za kraj programa.\n");
		scanf(" %c", &c);

		switch (c) {

		case 'd':
			el = rand() % (100 - 10 + 1) + 10;
			push(el, &red1);
			break;

		case 'p':
			pop(&red1);
			break;

		case 'i':
			ispis(red1.next);
			break;

		case 'z':
			break;


		}
	}

	return 0;
}

int push(int el, Pozicija p) {

	Pozicija q;

	q = (Pozicija)malloc(sizeof(_Red));

	while (p->next != NULL)
		p = p->next;

	q->broj = el;

	q->next = p->next;
	p->next = q;

	printf("\nunesen je broj: %d\n", el);

	return 0;
}

int pop(Pozicija p) {

	Pozicija q;

	if (p == NULL)
		printf("\nGreska! Red je prazan!");

	else {
		printf("\nSkidamo sa reda element %d", p->next->broj);   //prvog!

		q = p->next;
		p->next = q->next;   //p->next = p->next->next

		free(q);
	}

	return 0;
}

int ispis(Pozicija p) {

	if (p == NULL)
		printf("\nGreska! Red je prazan!");

	else {
		printf("\nIspis reda:");

		while (p != NULL) {
			printf("%d ", p->broj);
			p = p->next;
		}
		puts("");
	}

	return 0;
}