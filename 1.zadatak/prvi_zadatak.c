#include <stdio.h>
#include <stdlib.h>


typedef struct studenti {
	char ime[75];
	char prezime[75];
	int bodovi;
} stud ; 



 int main()

{

	char ch;
	int br= 0, i=0;
	FILE* fp;
	stud* student;
	double rel_br_bod[75];
	int max_br_bod = 80;


	fp = fopen("prvi_zad.txt", "r");
	if (fp == NULL) {
		printf(" *GRESKA!* Problem u otvaranju datoteku! \n");
		return 1;
	}

	while (!feof(fp)) {

		ch = fgetc(fp);
		if ( ch == '\n')
			br++;
	}

	rewind(fp);

	printf("Broj redaka je %d\n", br);

	student = (stud*) malloc(sizeof(stud) * br);  //dinamicka alokacija niza struktura

	 while (!feof(fp))  {
		 fscanf(fp, " %s	%s	%d", student[i].ime, student[i].prezime, &student[i].bodovi);
			i++;
		}
	 for(i=0; i<br; i++)
	 rel_br_bod [i] = ((double)student[i].bodovi / (double) max_br_bod) *100 ;

	 for (i = 0; i < br; i++)  {
		 printf("%s	%s	%d %.4lf\n", student[i].ime, student[i].prezime, student[i].bodovi,rel_br_bod[i] );
	 }

	fclose(fp); 

} 