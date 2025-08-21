#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cifre(char str[], char aux[]);

int main()
{
	char str1[] = "Ana are 12 mere si 15 pere\0";
	char str2[] = "Mara are 44 de ani si conduce de 20 de ani\0";
	char nr1[100];
	char nr2[100];

	cifre(str1, nr1);
	cifre(str2, nr2);
	char aux[100];
	strcpy(aux, nr1);
	strcat(aux, nr2);
	printf("%s\n", aux);
	strcpy(aux, nr2);
	strcat(aux, nr1);
	printf("%s", aux);
	return 0;
}
