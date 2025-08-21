#include <stdio.h>

int prim(int a);

int main()
{
	int a = -1;

	scanf("%d", &a);
	while (a != 0)
	{
		int rez = prim(a);
		if (rez)
			printf("%d ", a);

		scanf("%d", &a);
	}

	return 0;
}