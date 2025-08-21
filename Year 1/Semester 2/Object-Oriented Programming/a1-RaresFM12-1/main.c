#include<stdio.h>

void Menu();
void PrintPascalTriangle(int n);
int IsPrime(int n);
void LongestSubsequenceOfPrimeNr(int v[], int n, int* max_len, int* start);

int main()
{
	Menu();
	return 0;
}

// This function creates the menu
void Menu()
{
	int option;
	int n;
	int v[105];

	printf("1) Print Pascal's triangle\n");
	printf("2) Find the longest subsequence of contiguous prime numbers.\n");
	printf("3) Exit\n");

	while (1)
	{
		printf("Choose one option: ");
		scanf("%d", &option);

		if (option == 1)
		{
			printf("Choose the value for n: ");
			scanf("%d", &n);
			PrintPascalTriangle(n);
		}
		else if (option == 2)
		{
			printf("The length of the vector: ");
			scanf("%d", &n);
			printf("The elements of the vector: ");
			for (int i = 0; i < n; ++i)
				scanf("%d", &v[i]);

			int max_len = 0, start = 0;
			LongestSubsequenceOfPrimeNr(v, n, &max_len, &start);

			printf("The longest contiguous subsequence of prime numbers is of length: %d\n", max_len);
			printf("The longest subsequence of prime numbers is: ");
			for (int i = 0; i < max_len; ++i)
				printf("%d ", v[start + i]);
			printf("\n");
		}

		else if (option == 3)
			break;

		else
			printf("Bad command!\n");
	}
	
}

// This function prints Pascal's triangle of dimension n
// Params: n - dimension of the triangle
void PrintPascalTriangle(int n)
{
	// Outer loop to display each row
	for (int i = 0; i < n; ++i)
	{
		// The lines for the alignement of the echilateral triangle
		for (int j = 0; j < n - i - 1; ++j)
			printf(" ");

		// Print all values on a row
		int val = 1; // the first value is always 1
		for (int k = 0; k <= i; ++k)
		{
			printf("%d ", val);

			// Compute the next value
			val = val * (i - k) / (k + 1);   // with the formula C(m, k) = C(m, k - 1) * (m - k + 1) / k
		}

		printf("\n");
	}
}

// Checks if a number is prime
// Param: n - the number
int IsPrime(int n)
{
	if (n < 2)
		return 0;

	if (n == 2)
		return 1;

	if (n % 2 == 0)
		return 0;

	for (int d = 3; d * d <= n; d += 2)
		if (n % d == 0)
			return 0;

	return 1;
}

// This function finds the longest contiguous subsequence of prime numbers
// Params: v - the vector
//         n - the nr. of elements
//         max_len - max length
//         start - the starting position of the subsequence
void LongestSubsequenceOfPrimeNr(int v[], int n, int* max_len, int* start)
{
	int curr_len = 0, curr_start = 0;

	for (int i = 0; i < n; ++i)
	{
		if (IsPrime(v[i]))
		{
			if (curr_len == 0)       // if it's a new subsequence
				curr_start = i;

			curr_len++;
		}
		else           
		{
			curr_len = 0;
			curr_start = 0;
		}

		if (curr_len > *max_len)         // if we found a new subsequence
		{
			*max_len = curr_len;
			*start = curr_start;
		}

	}

	
}