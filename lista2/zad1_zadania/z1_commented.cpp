/*
* 	Oskar Makowski
*/

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <ctime>
using namespace std;

//declaration of all functions in both ascending and descending variant
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

int main(int argc, char * argv[])
{
	//example call: ./a.out --type insert --comp '<='
	if(argc != 5)
	{
		cout << "Too few arguments" << endl;		
		exit(0);
	}

	bool order; //0 descending, 1 ascending
	int function; //0 - insert, 1 - merge, 2 - quick

	//set number of function to call, look for bad input
	if(strcmp(argv[1], "--type") == 0)
	{	
		if(strcmp(argv[2], "insert") == 0)
			function = 0;
		else if(strcmp(argv[2], "merge") == 0)
			function = 1;
		else if(strcmp(argv[2], "quick") == 0)
			function = 2;
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

	//set order to sort input array, llok for bad input
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

	int n;
	cin >> n; //get size of array

	int A[n];

	for(int i = 0; i < n; i++)
	{
		cin >> A[i]; //get input
	}

	//creating all necessary variables to make statistics
	int * comparisons = new int(0); //number of comparisons between keys
	int * shifts = new int(0); //number of shifts between keys
	clock_t start;
	clock_t end;
	double result; //will hold difference in cpu clocks

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
	}

	cout << endl;

	//checkinf if output is sorted in correct order
	if(order == 0) //descending
	{
		for(int i = 0; i < n - 1; i++)
		{
			if(A[i] >= A[i + 1])
				continue;
			else
				cout << "Problem: " << A[i] << " " << A[i + 1] << endl;
		}
	}
	else //ascending
	{
		for(int i = 0; i < n - 1; i++)
		{
			if(A[i] <= A[i + 1])
				continue;
			else
				cout << "Problem: " << A[i] << " " << A[i + 1] << endl;
		}
	}

	//printing size of an array and its values
	cout << n << endl;
	for(int i = 0; i < n; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}

/*
*	Parameters:
*	array of keys
*	size of array
*	number of comparisons between keys
*	number of shifts between keys
*
*	InsertionSort in an algorithm that sorts in place
*	InsertionSort computational complexity is O(n*n)
*/
void insertionSortAscending(int A[], int n, int * comparisons, int * shifts)
{
	for(int i = 1; i < n; i++)
	{
		int key = A[i]; //select key
		int j = i - 1; //set index of element to compare

		cerr << "Comparison: " << A[j] << ", " << key << endl;
		(*comparisons)++;

/*	while j-index is greater than 0 and it is greater than key we shift this element in array
*	one may think of it as sorting cards in hands; in one hand we hold already sorted pile, in other cards awaitng to sort
*	we pick a card that wasnt sorted yet, find its place in sorted pile, and make place for it
*	by shifting other cards
*/
		while(j >= 0 && A[j] > key)
		{
			cerr << "Shift: " << A[j + 1] << " - " << j + 1 << "'th element = "
				 << A[j] << " - " << j << "'th element" << endl;
			(*shifts)++;

			A[j + 1] = A[j]; //the shift
			j--; //decrementing

			if(j >= 0) //statistics purpose, check if there will be next key comparison
			{
				cerr << "Comparison: " << A[j] << ", " << key << endl;
				(*comparisons)++;
			}
		}
		cerr << "Shift: " << A[j + 1] << " - " << j + 1 
			 << "'th element = " << key << " - " << " key" << endl;
		(*shifts)++;

		A[j + 1] = key; //finally, shift the key to its place
	}
}

//same as above, just sorting in another order
void insertionSortDescending(int A[], int n, int * comparisons, int * shifts)
{
	for(int i = 1; i < n; i++)
	{
		int key = A[i];
		int j = i - 1;

		cerr << "Comparison: " << A[j] << ", " << key << endl;
		(*comparisons)++;

		while(j >= 0 && A[j] < key)
		{
			cerr << "Shift: " << A[j + 1] << " - " << j + 1 << "'th element = "
				 << A[j] << " - " << j << "'th element" << endl;
			(*shifts)++;

			A[j + 1] = A[j];
			j--;

			if(j >= 0)
			{
				cerr << "Comparison: " << A[j] << ", " << key << endl;
				(*comparisons)++;
			}
		}
		cerr << "Shift: " << A[j + 1] << " - " << j + 1 
			 << "'th element = " << key << " - " << " key" << endl;
		(*shifts)++;

		A[j + 1] = key;
	}
}


/*
*	Parameters:
*	array of keys
*	starting index to be sorted
*	last index to be sorted(IMPORTANT: initial call is with sizeof(array)-1 because of that)
*	number of comparisons between keys
*	number of shifts between keys
*
*	MergeSort is a divide-and-conquer algorithm, each recursion call needs its own copy of array, so it doesnt sort in place	
*	MergeSort computational complexity is O(n*log(n))
*/
void mergeSortAscending(int A[], int start, int end, int * comparisons, int * shifts)
{
	//if index of first element to be sorted is less than index of last element to be sorted
	//it is needed to stop recursion at some point
	if(start < end)
	{
		int middle = (start + end) / 2; //find middle index of an array
		mergeSortAscending(A, start, middle, comparisons, shifts); //recursively sort first part of an array
		mergeSortAscending(A, middle + 1, end, comparisons, shifts); //and second part of an array
		mergeAscending(A, start, middle, end, comparisons, shifts); //merge both parts
	}
}

/*
*	Parameters:
*	array of keys
*	index of first element to be sorted
*	index of middle element to divide array
*	index of last element to be sorted
*	number of comparisons between keys
*	number of shifts between keys
*/
void mergeAscending(int A[], int p, int q, int r, int * comparisons, int * shifts)
{
	int n1 = q - p + 1; //set length of first part of array
	int n2 = r - q; //and second part of an array

	int L[n1 + 1]; //+1 is for additional place for a guard to omit checking if we are out of bounds
	int R[n2 + 1]; //L is for left part, R is for right part

	for(int i = 0; i < n1; i++)
	{
		L[i] = A[p + i]; //copying elements to temporary array that were on left side of q
	}
	for(int j = 0; j < n2; j++)
	{
		R[j] = A[q + j + 1]; //copying elements to temporary array that were on right side of q
	}

	L[n1] = 2147483647; //a guard; it should be a special value like infinity, so it is set with the highest possible integer
	R[n2] = 2147483647; //or with the lowest possible integer in descending variant

	int a = 0;
	int b = 0;

	for(int k = p; k <= r; k++)
	{
		cerr << "Comparison: " << L[a] << ", " << R[b] << endl;
		(*comparisons)++;
		if(L[a] <= R[b]) //compare the keys in both arrays
		{
			cerr << "Shift: " << A[k] << " - " << k << "'th element in A = "
				 << L[a] << " - " << a << "'th element in L" << endl;
			(*shifts)++;
			A[k] = L[a]; //copy to the original array L[a] if it is lower element
			a++;
		}
		else
		{
			cerr << "Shift: " << A[k] << " - " << k << "'th element in A = "
				 << R[b] << " - " << b << "'th element in R" << endl;
			(*shifts)++;
			A[k] = R[b]; //copy R[b] if it is lower element
			b++;
		}
	}
}

//same as above, just sorting in another order
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

//same as above, just sorting in another order
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

	L[n1] = -2147483648; //a guard set with the lowest possible integer
	R[n2] = -2147483648;

	int a = 0;
	int b = 0;

	for(int k = p; k <= r; k++)
	{
		cerr << "Comparison: " << L[a] << ", " << R[b] << endl;
		(*comparisons)++;
		if(L[a] >= R[b])
		{
			cerr << "Shift: " << A[k] << " - " << k << "'th element in A = "
				 << L[a] << " - " << a << "'th element in L" << endl;
			(*shifts)++;
			A[k] = L[a];
			a++;
		}
		else
		{
			cerr << "Shift: " << A[k] << " - " << k << "'th element in A = "
				 << R[b] << " - " << b << "'th element in R" << endl;
			(*shifts)++;
			A[k] = R[b];
			b++;
		}
	}
}

/*
*	Parameters:
*	array of keys
*	index of first element to be sorted
*	index of last lement to be sorted + 1
*	number of comparisons between keys
*	number of shifts between keys
*/
void quickSortAscending(int A[], int p, int r, int * comparisons, int * shifts)
{
	//condition to stop recursion calls at some point
	if(p < r)
	{
		int q = partitionAscending(A, p, r, comparisons, shifts); //select pivot
		quickSortAscending(A, p, q, comparisons, shifts); //recursively sort elements that are at left side of pivot
		quickSortAscending(A, q + 1, r, comparisons, shifts); //or at right side of pivot
	}
}

/*
*	Parameters:
*	array of keys
*	index of first element to be sorted
*	index of last element to be sorted + 1
*	number of comparisons between keys
*	number of shifts between keys
*/
int partitionAscending(int A[], int p, int r, int * comparisons, int * shifts)
{
	int pivot = A[p]; //set pivot as the first element of array
	int i = p;

	for(int j = p + 1; j < r; j++)
	{
		cerr << "Comparison: " << A[j] << ", " << pivot << endl;
		(*comparisons)++;
		if(A[j] <= pivot) //compare element with chosen pivot
		{
			i++; //increace index to make a correct swap
			cerr << "Shift: " << A[i] << " - " << i << "'th element = "
				 << A[j] << " - " << j << "'th element" << endl;
			(*shifts)++;
			swap(A[i], A[j]); //swap the elements
		}
	}
	cerr << "Shift: " << A[i] << " - " << i << "'th element = "
				 << A[p] << " - " << p << "'th element" << endl;
	(*shifts)++;
	swap(A[i], A[p]); //final swap to place everything in proper order

	return i;
}

//same as above, just sorting in another order
void quickSortDescending(int A[], int p, int r, int * comparisons, int * shifts)
{
	if(p < r)
	{
		int q = partitionDescending(A, p, r, comparisons, shifts);
		quickSortDescending(A, p, q, comparisons, shifts);
		quickSortDescending(A, q + 1, r, comparisons, shifts);
	}
}

//same as above, just sorting in another order
int partitionDescending(int A[], int p, int r, int * comparisons, int * shifts)
{
	int pivot = A[p];
	int i = p;

	for(int j = p + 1; j < r; j++)
	{
		cerr << "Comparison: " << A[j] << ", " << pivot << endl;
		(*comparisons)++;
		if(A[j] >= pivot)
		{
			i++;
			cerr << "Shift: " << A[i] << " - " << i << "'th element = "
				 << A[j] << " - " << j << "'th element" << endl;
			(*shifts)++;
			swap(A[i], A[j]);
		}
	}
	cerr << "Shift: " << A[i] << " - " << i << "'th element = "
				 << A[p] << " - " << p << "'th element" << endl;
	(*shifts)++;
	swap(A[i], A[p]);

	return i;
}
