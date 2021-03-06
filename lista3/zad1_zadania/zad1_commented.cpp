/*
*	Oskar Makowski
*/
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <ctime>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

void fill_array(int [], int);
void insertionSortAscending(int [], int, int *, int *);
void insertionSortDescending(int [], int, int *, int *);
void mergeSortAscending(int [], int, int, int *, int *);
void mergeSortDescending(int [], int, int, int *, int *);
void mergeAscending(int[], int, int, int, int *, int *);
void mergeDescending(int[], int, int, int, int *, int *);
void quickSortAscending(int [], int, int, int *, int *);
void quickSortDescending(int [], int, int, int *, int *);
int partitionAscending(int [], int, int, int *, int *);
int partitionDescending(int [], int, int, int *, int *);
int getMax(int [], int);
void countingSortAscending(int [], int, int, int);
void countingSortDescending(int [], int, int, int);
void radixSortAscending(int [], int, int, int *, int *);
void radixSortDescending(int [], int, int, int *, int *);

int main(int argc, char * argv[])
{
	srand(time(0));

	if(argc != 5 && argc != 8)
	{
		cout << "Wrong number of arguments" << endl;		
		exit(0);
	}

	bool order; //0 descending, 1 ascending
	int function; //0 - insert, 1 - merge, 2 - quick
	fstream f;

	int * comparisons = new int(0);
	int * shifts = new int(0);
	clock_t start;
	clock_t end;
	double result;

	if(strcmp(argv[1], "--type") == 0)
	{	
		if(strcmp(argv[2], "insert") == 0)
			function = 0;
		else if(strcmp(argv[2], "merge") == 0)
			function = 1;
		else if(strcmp(argv[2], "quick") == 0)
			function = 2;
		else if(strcmp(argv[2], "radix") == 0)
			function = 3;
		else
		{
			cout << "There is no such sorting algorithm" << endl;
			exit(0);
		}
	}
	else
	{
		cout << "Wrong second parameter " << argv[1] << endl;
		exit(0);
	}

	if(strcmp(argv[3], "--comp") == 0)
	{
		if(strcmp(argv[4], ">=") == 0)
			order = 0;
		else if(strcmp(argv[4], "<=") == 0)
			order = 1;
		else
		{
			cout << "Wrong fifth parameter" << endl;
			exit(0);
		}
	}
	else
	{
		cout << "Wrong fourth parameter" << endl;
		exit(0);
	}

	if(argc == 8)
	{	
		if(strcmp(argv[5], "--stat") == 0)
		{
			f.open(argv[6], ios::out); 
			if(!f.good())
			{
				cout << "Access denied or file doesnt exist" << endl;
				exit(0);
			}

		}
		else
		{
			cout << "Wrong sixth parameter" << endl;
			exit(0);
		}

		if(argv[7] <= 0)
		{
			cout << "Eightth parameter should be > 0" << endl;
			exit(0);
		}

		int A[100];
		for(int i = 0; i < 100; i++)
		{
			A[i] = (i + 1) * 100;

			int B[A[i]];

			for(int j = 0; j < atoi(argv[7]); j++)
			{
				fill_array(B, A[i]);		
				*comparisons = 0;
				*shifts = 0;
				result = 0;
			
				switch(function)
				{
					case 0:
						if(order == 0)
						{
							start = clock();
							insertionSortDescending(B, A[i], comparisons, shifts);
							end = clock();
							result = end - start;

							f << A[i] << endl;
							f << "Comparisons: " << *comparisons << endl;
							f << "Shifts: " << *shifts << endl;
							f << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
						}
						else
						{
							start = clock();
							insertionSortAscending(B, A[i], comparisons, shifts);
							end = clock();
							result = end - start;

							f << A[i] << endl;
							f << "Comparisons: " << *comparisons << endl;
							f << "Shifts: " << *shifts << endl;
							f << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
						}
						break;

					case 1:
						if(order == 0)
						{
							start = clock();
							mergeSortDescending(B, 0, A[i] - 1, comparisons, shifts);
							end = clock();
							result = end - start;

							f << A[i] << endl;
							f << "Comparisons: " << *comparisons << endl;
							f << "Shifts: " << *shifts << endl;
							f << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
						}
						else
						{
							start = clock();
							mergeSortAscending(B, 0, A[i] - 1, comparisons, shifts);
							end = clock();
							result = end - start;

							f << A[i] << endl;
							f << "Comparisons: " << *comparisons << endl;
							f << "Shifts: " << *shifts << endl;
							f << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
						}
						break;

					case 2:
						if(order == 0)
						{
							start = clock();
							quickSortDescending(B, 0, A[i], comparisons, shifts);
							end = clock();
							result = end - start;

							f << A[i] << endl;
							f << "Comparisons: " << *comparisons << endl;
							f << "Shifts: " << *shifts << endl;
							f << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
						}
						else
						{
							start = clock();
							quickSortAscending(B, 0, A[i], comparisons, shifts);
							end = clock();
							result = end - start;

							f << A[i] << endl;
							f << "Comparisons: " << *comparisons << endl;
							f << "Shifts: " << *shifts << endl;
							f << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
						}
						break;

					case 3:
						if(order == 0)
						{
							start = clock();
							radixSortDescending(B, 0, A[i], comparisons, shifts);
							end = clock();
							result = end - start;

							f << A[i] << endl;
							f << "Comparisons: " << *comparisons << endl;
							f << "Shifts: " << *shifts << endl;
							f << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
						}
						else
						{
							start = clock();
							radixSortAscending(B, 0, A[i], comparisons, shifts);
							end = clock();
							result = end - start;

							f << A[i] << endl;
							f << "Comparisons: " << *comparisons << endl;
							f << "Shifts: " << *shifts << endl;
							f << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
						}
						break;
				}

				if(order == 0)
				{
					for(int i = 0; i < A[i] - 1; i++)
					{
						if(B[i] >= B[i + 1])
							continue;
						else
							cout << "Problem: " << B[i] << " " << B[i + 1] << endl;
					}
				}
				else
				{
					for(int i = 0; i < A[i] - 1; i++)
					{
						if(B[i] <= B[i + 1])
							continue;
						else
							cout << "Problem: " << B[i] << " " << B[i + 1] << endl;
					}
				}
			}
		}
	}
	else
	{
		int n;
		cin >> n;

		int A[n];		

		for(int i = 0; i < n; i++)
		{
			cin >> A[i]; 
		}

		switch(function)
		{
			case 0:
				if(order == 0)
				{
					start = clock();
					insertionSortDescending(A, n, comparisons, shifts);
					end = clock();
					result = end - start;

					cerr << "Comparisons: " << *comparisons << endl;
					cerr << "Shifts: " << *shifts << endl;
					cerr << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
				}
				else
				{
					start = clock();
					insertionSortAscending(A, n, comparisons, shifts);
					end = clock();
					result = end - start;

					cerr << "Comparisons: " << *comparisons << endl;
					cerr << "Shifts: " << *shifts << endl;
					cerr << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
				}
				break;

			case 1:
				if(order == 0)
				{
					start = clock();
					mergeSortDescending(A, 0, n - 1, comparisons, shifts);
					end = clock();
					result = end - start;

					cerr << "Comparisons: " << *comparisons << endl;
					cerr << "Shifts: " << *shifts << endl;
					cerr << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
				}
				else
				{
					start = clock();
					mergeSortAscending(A, 0, n - 1, comparisons, shifts);
					end = clock();
					result = end - start;

					cerr << "Comparisons: " << *comparisons << endl;
					cerr << "Shifts: " << *shifts << endl;
					cerr << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
				}
				break;

			case 2:
				if(order == 0)
				{
					start = clock();
					quickSortDescending(A, 0, n, comparisons, shifts);
					end = clock();
					result = end - start;

					cerr << "Comparisons: " << *comparisons << endl;
					cerr << "Shifts: " << *shifts << endl;
					cerr << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
				}
				else
				{
					start = clock();
					quickSortAscending(A, 0, n, comparisons, shifts);
					end = clock();
					result = end - start;

					cerr << "Comparisons: " << *comparisons << endl;
					cerr << "Shifts: " << *shifts << endl;
					cerr << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
				}
				break;

			case 3:
				if(order == 0)
				{
					start = clock();
					radixSortDescending(A, n, 10, comparisons, shifts);
					end = clock();
					result = end - start;

					cerr << "Comparisons: " << *comparisons << endl;
					cerr << "Shifts: " << *shifts << endl;
					cerr << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
				}
				else
				{
					start = clock();
					radixSortAscending(A, n, 10, comparisons, shifts);
					end = clock();
					result = end - start;

					cerr << "Comparisons: " << *comparisons << endl;
					cerr << "Shifts: " << *shifts << endl;
					cerr << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
				}
				break;
		}

		cout << endl;

		for(int i = 0; i < n - 1; i++)
		{
			if(A[i] < A[i + 1])
				continue;
			else
				cout << "Problem: " << A[i] << " " << A[i + 1] << endl;
		}

		cout << n << endl;
		for(int i = 0; i < n; i++)
		{
			cout << A[i] << " ";
		}
		cout << endl;
	}

	f.close();
}

void fill_array(int A[], int n)
{
	for(int i = 0; i < n; i++)
	{
		A[i] = rand() % n + 1;
	}
}

void insertionSortAscending(int A[], int n, int * comparisons, int * shifts)
{
	for(int i = 1; i < n; i++)
	{
		int key = A[i];
		int j = i - 1;

//		cerr << "Comparison: " << A[j] << ", " << key << endl;
		(*comparisons)++;

		while(j >= 0 && A[j] > key)
		{
//			cerr << "Shift: " << A[j + 1] << " - " << j + 1 << "'th element = "
//				 << A[j] << " - " << j << "'th element" << endl;
			(*shifts)++;

			A[j + 1] = A[j];
			j--;

			if(j >= 0)
			{
//				cerr << "Comparison: " << A[j] << ", " << key << endl;
				(*comparisons)++;
			}
		}
//		cerr << "Shift: " << A[j + 1] << " - " << j + 1 
//			 << "'th element = " << key << " - " << " key" << endl;
		(*shifts)++;

		A[j + 1] = key;
	}
}

void insertionSortDescending(int A[], int n, int * comparisons, int * shifts)
{
	for(int i = 1; i < n; i++)
	{
		int key = A[i];
		int j = i - 1;

//		cerr << "Comparison: " << A[j] << ", " << key << endl;
		(*comparisons)++;

		while(j >= 0 && A[j] < key)
		{
//			cerr << "Shift: " << A[j + 1] << " - " << j + 1 << "'th element = "
//				 << A[j] << " - " << j << "'th element" << endl;
			(*shifts)++;

			A[j + 1] = A[j];
			j--;

			if(j >= 0)
			{
//				cerr << "Comparison: " << A[j] << ", " << key << endl;
				(*comparisons)++;
			}
		}
//		cerr << "Shift: " << A[j + 1] << " - " << j + 1 
//			 << "'th element = " << key << " - " << " key" << endl;
		(*shifts)++;

		A[j + 1] = key;
	}
}

void mergeSortAscending(int A[], int start, int end, int * comparisons, int * shifts)
{
	if(start < end)
	{
		int middle = (start + end) / 2;
		mergeSortAscending(A, start, middle, comparisons, shifts);
		mergeSortAscending(A, middle + 1, end, comparisons, shifts);
		mergeAscending(A, start, middle, end, comparisons, shifts);
	}
}

void mergeAscending(int A[], int p, int q, int r, int * comparisons, int * shifts)
{
	int n1 = q - p + 1;
	int n2 = r - q;

	int L[n1 + 1];
	int R[n2 + 1];

	for(int i = 0; i < n1; i++)
	{
		L[i] = A[p + i];
	}
	for(int j = 0; j < n2; j++)
	{
		R[j] = A[q + j + 1];
	}

	L[n1] = 2147483647;
	R[n2] = 2147483647;

	int a = 0;
	int b = 0;

	for(int k = p; k <= r; k++)
	{
//		cerr << "Comparison: " << L[a] << ", " << R[b] << endl;
		(*comparisons)++;
		if(L[a] <= R[b])
		{
//			cerr << "Shift: " << A[k] << " - " << k << "'th element in A = "
//				 << L[a] << " - " << a << "'th element in L" << endl;
			(*shifts)++;
			A[k] = L[a];
			a++;
		}
		else
		{
//			cerr << "Shift: " << A[k] << " - " << k << "'th element in A = "
//				 << R[b] << " - " << b << "'th element in R" << endl;
			(*shifts)++;
			A[k] = R[b];
			b++;
		}
	}
}

void mergeSortDescending(int A[], int start, int end, int * comparisons, int * shifts)
{
	if(start < end)
	{
		int middle = (start + end) / 2;
		mergeSortDescending(A, start, middle, comparisons, shifts);
		mergeSortDescending(A, middle + 1, end, comparisons, shifts);
		mergeDescending(A, start, middle, end, comparisons, shifts);
	}
}

void mergeDescending(int A[], int p, int q, int r, int * comparisons, int * shifts)
{
	int n1 = q - p + 1;
	int n2 = r - q;

	int L[n1 + 1];
	int R[n2 + 1];

	for(int i = 0; i < n1; i++)
	{
		L[i] = A[p + i];
	}
	for(int j = 0; j < n2; j++)
	{
		R[j] = A[q + j + 1];
	}

	L[n1] = -2147483648;
	R[n2] = -2147483648;

	int a = 0;
	int b = 0;

	for(int k = p; k <= r; k++)
	{
//		cerr << "Comparison: " << L[a] << ", " << R[b] << endl;
		(*comparisons)++;
		if(L[a] >= R[b])
		{
//			cerr << "Shift: " << A[k] << " - " << k << "'th element in A = "
//				 << L[a] << " - " << a << "'th element in L" << endl;
			(*shifts)++;
			A[k] = L[a];
			a++;
		}
		else
		{
//			cerr << "Shift: " << A[k] << " - " << k << "'th element in A = "
//				 << R[b] << " - " << b << "'th element in R" << endl;
			(*shifts)++;
			A[k] = R[b];
			b++;
		}
	}
}

void quickSortAscending(int A[], int p, int r, int * comparisons, int * shifts)
{
	if(p < r)
	{
		int q = partitionAscending(A, p, r, comparisons, shifts);
		quickSortAscending(A, p, q, comparisons, shifts);
		quickSortAscending(A, q + 1, r, comparisons, shifts);
	}
}

int partitionAscending(int A[], int p, int r, int * comparisons, int * shifts)
{
	int pivot = A[p];
	int i = p;

	for(int j = p + 1; j < r; j++)
	{
//		cerr << "Comparison: " << A[j] << ", " << pivot << endl;
		(*comparisons)++;
		if(A[j] <= pivot)
		{
			i++;
//			cerr << "Shift: " << A[i] << " - " << i << "'th element = "
//				 << A[j] << " - " << j << "'th element" << endl;
			(*shifts)++;
			swap(A[i], A[j]);
		}
	}
//	cerr << "Shift: " << A[i] << " - " << i << "'th element = "
//				 << A[p] << " - " << p << "'th element" << endl;
	(*shifts)++;
	swap(A[i], A[p]);

	return i;
}

void quickSortDescending(int A[], int p, int r, int * comparisons, int * shifts)
{
	if(p < r)
	{
		int q = partitionDescending(A, p, r, comparisons, shifts);
		quickSortDescending(A, p, q, comparisons, shifts);
		quickSortDescending(A, q + 1, r, comparisons, shifts);
	}
}

int partitionDescending(int A[], int p, int r, int * comparisons, int * shifts)
{
	int pivot = A[p];
	int i = p;

	for(int j = p + 1; j < r; j++)
	{
//		cerr << "Comparison: " << A[j] << ", " << pivot << endl;
		(*comparisons)++;
		if(A[j] >= pivot)
		{
			i++;
//			cerr << "Shift: " << A[i] << " - " << i << "'th element = "
//				 << A[j] << " - " << j << "'th element" << endl;
			(*shifts)++;
			swap(A[i], A[j]);
		}
	}
//	cerr << "Shift: " << A[i] << " - " << i << "'th element = "
//				 << A[p] << " - " << p << "'th element" << endl;
	(*shifts)++;
	swap(A[i], A[p]);

	return i;
}

/*
*	Parameters:
*	array of keys
*	size of array
*	base
*	number of comparisons
*	shifts
*/
void radixSortAscending(int A[], int n, int k, int * comp, int * shifts)
{
	int m = getMax(A, n); //m is the number with the largest number of digits
	for(int i = 1; m / i > 0; i *= k) //do countingSort on every digit
	{
		countingSortAscending(A, k, n, i);
	}
}

//same as above, just sorting in another order
void radixSortDescending(int A[], int n, int k, int * comp, int * shifts)
{
	int m = getMax(A, n);
	for(int i = 1; m / i > 0; i *= k)
	{
		countingSortDescending(A, k, n, i);
	}
}

void countingSortAscending(int A[], int k, int n, int m)
{
	int C[k]; //array to store amount of every digit
	for(int i = 0; i < k; i++)
	{
		C[i] = 0; //initialization
	}

	for(int i = 0; i < n; i++)
	{
		C[(A[i] / m) % 10]++; //number of elements that are equal to i
	}

	for(int i = 1; i < k; i++)
	{
		C[i] = C[i] + C[i - 1]; //elements less than or equal to i
	}

	int B[n];
	for(int i = n - 1; i >= 0; i--)
	{
		B[C[(A[i] / m) % 10] - 1] = A[i]; //elements are put to their proper places in B array
		C[(A[i] / m) % 10]--;
	}

	for(int i = 0; i < n; i++)
	{
		A[i] = B[i]; //copying output back to original array
	}
}

//same as above, just sorting in another order
void countingSortDescending(int A[], int k, int n, int m)
{
	int C[k];
	for(int i = 0; i < k; i++)
	{
		C[i] = 0;
	}

	for(int i = 0; i < n; i++)
	{
		C[(A[n - i - 1] / m) % 10]++;
	}

	for(int i = 1; i < k; i++)
	{
		C[i] = C[i] + C[i - 1];
	}

	int B[n];
	for(int i = n - 1; i >= 0; i--)
	{
		B[C[(A[i] / m) % 10] - 1] = A[i];
		C[(A[i] / m) % 10]--;
	}

	for(int i = 0; i < n; i++)
	{
		A[i] = B[i];
	}
}

int getMax(int A[], int n)
{
	int mx = A[0];
	for(int i = 1; i < n; i++)
	{
		if(A[i] > mx)
			mx = A[i];
	}
	return mx;
}
