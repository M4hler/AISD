/*
*	Oskar Makowski
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
void dualPivotQuickSortAscending(int [], int, int, int *, int *);
void dualPivotQuickSortDescending(int [], int, int, int *, int *);
int partition2Ascending(int [], int, int, int*, int *, int *);
int partition2Descending(int [], int, int, int*, int *, int *);

int main(int argc, char * argv[])
{
	//example call: ./a.out --type dpquick --comp '<='
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
		else if(strcmp(argv[2], "dpquick") == 0)
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
	cin >> n; //get size

	int A[n];

	for(int i = 0; i < n; i++)
	{
		cin >> A[i]; //gei input
	}

	//creating all necessary variables to make statistics
	int * comparisons = new int(0);
	int * shifts = new int(0);
	clock_t start;
	clock_t end;
	double result;

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
				dualPivotQuickSortDescending(A, 0, n, comparisons, shifts);
				end = clock();
				result = end - start;

				cerr << "Comparisons: " << *comparisons << endl;
				cerr << "Shifts: " << *shifts << endl;
				cerr << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
			}
			else
			{
				start = clock();
				dualPivotQuickSortAscending(A, 0, n, comparisons, shifts);
				end = clock();
				result = end - start;

				cerr << "Comparisons: " << *comparisons << endl;
				cerr << "Shifts: " << *shifts << endl;
				cerr << "Time: " << result << ", " << result / CLOCKS_PER_SEC << endl;
			}
			break;
	}

	cout << endl;

	//check if output is sorted in correct order
	if(order == 0)
	{
		for(int i = 0; i < n - 1; i++)
		{
			if(A[i] >= A[i + 1])
				continue;
			else
				cout << "Problem: " << A[i] << " " << A[i + 1] << endl;
		}
	}
	else
	{
		for(int i = 0; i < n - 1; i++)
		{
			if(A[i] <= A[i + 1])
				continue;
			else
				cout << "Problem: " << A[i] << " " << A[i + 1] << endl;
		}
	}

	//print output
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
*	
*	Writing to standard error output was commented because even redirection to file took very long time 
*	to save all information about comparisons and shifts
*/
void insertionSortAscending(int A[], int n, int * comparisons, int * shifts)
{
	clock_t start = clock();

	for(int i = 1; i < n; i++)
	{
		int key = A[i];
		int j = i - 1;

		cerr << "Comparison: " << A[j] << ", " << key << endl;
		(*comparisons)++;

		while(j >= 0 && A[j] > key)
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

//same as above, just sorting in another order
void insertionSortDescending(int A[], int n, int * comparisons, int * shifts)
{
	clock_t start = clock();

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
	if(start < end)
	{
		int middle = (start + end) / 2;
		mergeSortAscending(A, start, middle, comparisons, shifts);
		mergeSortAscending(A, middle + 1, end, comparisons, shifts);
		mergeAscending(A, start, middle, end, comparisons, shifts);
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
		cerr << "Comparison: " << L[a] << ", " << R[b] << endl;
		(*comparisons)++;
		if(L[a] <= R[b])
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

	L[n1] = -2147483648;
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
	if(p < r)
	{
		int q = partitionAscending(A, p, r, comparisons, shifts);
		quickSortAscending(A, p, q, comparisons, shifts);
		quickSortAscending(A, q + 1, r, comparisons, shifts);
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
	int pivot = A[p];
	int i = p;

	for(int j = p + 1; j < r; j++)
	{
		cerr << "Comparison: " << A[j] << ", " << pivot << endl;
		(*comparisons)++;
		if(A[j] <= pivot)
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

/*
*	Parameters:
*	array of keys
*	index of first element to be sorted
*	index of last element to be sorted + 1
*	number of comparisons between keys
*	number of shifts between keys
*/
void dualPivotQuickSortAscending(int A[], int p, int r, int * comparisons, int * shifts)
{
	if(p < r)
	{
		int q1, q2; 
		q2 = partition2Ascending(A, p, r, &q1, comparisons, shifts);
		dualPivotQuickSortAscending(A, p, q1, comparisons, shifts);
		dualPivotQuickSortAscending(A, q1 + 1, q2, comparisons,shifts);
		dualPivotQuickSortAscending(A, q2 + 1, r, comparisons, shifts);
	}
}

/*
*	Parameters:
*	array of keys
*	index of first element to be sorted
*	index of last element to be sorted + 1
*	pointer to modify other pivot
*	number of comparisons between keys
*	number of shifts between keys
*/
int partition2Ascending(int A[], int p, int r, int * r2, int * comparisons, int * shifts)
{
	int lower_than_left_pivot = 0;
	int greater_than_right_pivot = 0;

	cerr << "Comparison: " << A[p] << ", " << A[r] << endl;
	(*comparisons)++;
	if(A[p] > A[r])
	{
		cerr << "Shift: " << A[p] << " - " << p << "'th element = "
		     << A[r] << " - " << r << "'th element" << endl;
		(*shifts)++;	
		swap(A[p], A[r]);
	}

	int j = p + 1; //set indexes
	int g = r - 1;
	int k = p + 1;
	int x = A[p]; //set pivots
	int y = A[r];

	while(k <= g)
	{
		if(lower_than_left_pivot >= greater_than_right_pivot) //count strategy
		{	
			cerr << "-----Comparison: " << A[k] << ", " << x << endl;
			(*comparisons)++;
			if(A[k] < x) //compare with left pivot
			{
				cerr << "Shift: " << A[k] << " - " << k << "'th element = "
			    	     << A[j] << " - " << j << "'th element" << endl;
				(*shifts)++;
				swap(A[k], A[j]);
				j++;
				lower_than_left_pivot++;
			}
			else 
			{
				cerr << "Comparison: " << A[k] << ", " << y << endl;
				(*comparisons)++;
				if(A[k] >= y) //compare with right pivot
				{
					cerr << "Comparison: " << A[g] << ", " << y << endl;
					(*comparisons)++;
					while(A[g] > y && k < g)
					{
						g--;
						cerr << "Comparison: " << A[g] << ", " << y << endl;
						(*comparisons)++;
					}
					cerr << "Shift: " << A[k] << " - " << k << "'th element = "
				    	     << A[g] << " - " << g << "'th element" << endl;
					(*shifts)++;
					swap(A[k], A[g]);
					g--;

					cerr << "Comparison: " << A[k] << ", " << x << endl;
					(*comparisons)++;
					if(A[k] < x)
					{
						cerr << "Shift: " << A[k] << " - " << k << "'th element = "
				    	     	     << A[j] << " - " << j << "'th element" << endl;
						(*shifts)++;				
						swap(A[k], A[j]);
						j++;
					}
					greater_than_right_pivot++;
				}
			}
		}
		else
		{
			cerr << "Comparison: " << A[k] << ", " << y << endl;
			(*comparisons)++;
			if(A[k] >= y)
			{
				cerr << "Comparison: " << A[g] << ", " << y << endl;
				(*comparisons)++;
				while(A[g] > y && k < g)
				{
					g--;
					cerr << "Comparison: " << A[g] << ", " << y << endl;
					(*comparisons)++;
				}
				cerr << "Shift: " << A[k] << " - " << k << "'th element = "
			    	     << A[g] << " - " << g << "'th element" << endl;
				(*shifts)++;
				swap(A[k], A[g]);
				g--;

				cerr << "Comparison: " << A[k] << ", " << x << endl;
				(*comparisons)++;
				if(A[k] < x)
				{
					cerr << "Shift: " << A[k] << " - " << k << "'th element = "
			    	     	     << A[j] << " - " << j << "'th element" << endl;
					(*shifts)++;				
					swap(A[k], A[j]);
					j++;
				}
				greater_than_right_pivot++;
			}
			else
			{
				cerr << "-----Comparison: " << A[k] << ", " << x << endl;
				(*comparisons)++;
				if(A[k] < x)
				{
					cerr << "Shift: " << A[k] << " - " << k << "'th element = "
				    	     << A[j] << " - " << j << "'th element" << endl;
					(*shifts)++;
					swap(A[k], A[j]);
					j++;
					lower_than_left_pivot++;
				}
			}
		}
		k++;
	}

	j--; //adjusting indexes for final swaps
	g++;

	cerr << "Shift: " << A[p] << " - " << p << "'th element = "
	     << A[j] << " - " << j << "'th element" << endl;
	(*shifts)++;		
	swap(A[p], A[j]); //final swaps to place everything in proper order

	cerr << "Shift: " << A[r] << " - " << r << "'th element = "
	     << A[g] << " - " << g << "'th element" << endl;
	(*shifts)++;
	swap(A[r], A[g]);

	*r2 = j; //change first pivot

	return g; //return second pivot
}

//same as above, just sorting in another order
void dualPivotQuickSortDescending(int A[], int p, int r, int * comparisons, int * shifts)
{
	if(p < r)
	{
		int q1, q2; 
		q2 = partition2Descending(A, p, r, &q1, comparisons, shifts);
		dualPivotQuickSortDescending(A, p, q1, comparisons, shifts);
		dualPivotQuickSortDescending(A, q1 + 1, q2, comparisons,shifts);
		dualPivotQuickSortDescending(A, q2 + 1, r, comparisons, shifts);
	}
}

//same as above, just sorting in another order
int partition2Descending(int A[], int p, int r, int * r2, int * comparisons, int * shifts)
{
	int lower_than_left_pivot = 0;
	int greater_than_right_pivot = 0;

	cerr << "Comparison: " << A[p] << ", " << A[r] << endl;
	(*comparisons)++;
	if(A[p] < A[r])
	{
		cerr << "Shift: " << A[p] << " - " << p << "'th element = "
	    	 << A[r] << " - " << r << "'th element" << endl;
		(*shifts)++;
		swap(A[p], A[r]);
	}

	int j = p + 1;
	int g = r - 1;
	int k = p + 1;
	int x = A[p];
	int y = A[r];

	while(k <= g)
	{
		if(lower_than_left_pivot >= greater_than_right_pivot)
		{
			cerr << "Comparison: " << A[k] << ", " << x << endl;
			(*comparisons)++;
			if(A[k] > x)
			{
				cerr << "Shift: " << A[k] << " - " << k << "'th element = "
		    		 << A[j] << " - " << j << "'th element" << endl;
				(*shifts)++;
				swap(A[k], A[j]);
				j++;
			}
			else
			{
				cerr << "Comparison: " << A[k] << ", " << y << endl;
				(*comparisons)++;
				if(A[k] <= y)
				{
					cerr << "Comparison: " << A[g] << ", " << y << endl;
					(*comparisons)++;
					while(A[g] < y && k < g)
					{
						g--;
						cerr << "Comparison: " << A[g] << ", " << y << endl;
						(*comparisons)++;
					}

					cerr << "Shift: " << A[k] << " - " << k << "'th element = "
		    			 << A[g] << " - " << g << "'th element" << endl;
					(*shifts)++;
					swap(A[k], A[g]);
					g--;

					cerr << "Comparison: " << A[k] << ", " << x << endl;
					(*comparisons)++;
					if(A[k] > x)
					{
						cerr << "Shift: " << A[k] << " - " << k << "'th element = "
		    			 	<< A[j] << " - " << j << "'th element" << endl;
						(*shifts)++;
						swap(A[k], A[j]);
						j++;
					}
				}
			}
		}
		else
		{
			cerr << "Comparison: " << A[k] << ", " << y << endl;
			(*comparisons)++;
			if(A[k] <= y)
			{
				cerr << "Comparison: " << A[g] << ", " << y << endl;
				(*comparisons)++;
				while(A[g] < y && k < g)
				{
					g--;
					cerr << "Comparison: " << A[g] << ", " << y << endl;
					(*comparisons)++;
				}

				cerr << "Shift: " << A[k] << " - " << k << "'th element = "
		    			 << A[g] << " - " << g << "'th element" << endl;
				(*shifts)++;
				swap(A[k], A[g]);
				g--;

				cerr << "Comparison: " << A[k] << ", " << x << endl;
				(*comparisons)++;
				if(A[k] > x)
				{
					cerr << "Shift: " << A[k] << " - " << k << "'th element = "
	   			 	<< A[j] << " - " << j << "'th element" << endl;
					(*shifts)++;
					swap(A[k], A[j]);
					j++;
				}
			}
			else
			{
				if(A[k] > x)
				{
					cerr << "Shift: " << A[k] << " - " << k << "'th element = "
			    		 << A[j] << " - " << j << "'th element" << endl;
					(*shifts)++;
					swap(A[k], A[j]);
					j++;
				}
			}
		}
		k++;
	}
	j--;
	g++;

	cerr << "Shift: " << A[p] << " - " << p << "'th element = "
	    	<< A[j] << " - " << j << "'th element" << endl;
	(*shifts)++;
	swap(A[p], A[j]);

	cerr << "Shift: " << A[r] << " - " << r << "'th element = "
	    	<< A[g] << " - " << g << "'th element" << endl;
	(*shifts)++;
	swap(A[r], A[g]);

	*r2 = j;
	return g;
}


