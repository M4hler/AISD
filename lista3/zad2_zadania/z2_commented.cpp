#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <stdio.h>
using namespace std;

int Select(int [], int, int, int, int *, int *);
int RandomSelect(int [], int, int, int, int *, int *);
int RandomPartition(int [], int, int, int *, int *);
int partition(int [], int, int, int *, int *);
int selectPartition(int [], int, int, int);
void insertionSort(int [], int, int, int *, int *);
void generateRandom(int [], int);
void generatePermutation(int [], int);
bool inSet(int [], int, int);

int main(int argc, char * argv[])
{
	srand(time(0));

	if(argc != 2)
	{
		cout << "Wrong number of arguments" << endl;
		exit(0);
	}

	int n, stat;
	cin >> n; //input length of array
	cin >> stat; //number of k'th minimal element to find
	int A[n];

	int * comp = new int(0);
	int * shifts = new int(0);
	int rsResult, sResult;

	if(strcmp(argv[1], "-r") == 0)
	{
		generateRandom(A, n);

		for(int i = 0; i < n; i++)
		{
			cerr << A[i] << " ";
		}
		cerr << endl << "searching for " << stat << "'th minimal element" << endl;

		rsResult = RandomSelect(A, 0, n, stat, comp, shifts);
		sResult = Select(A, 0, n, stat, comp, shifts);
	}
	else if(strcmp(argv[1], "-p") == 0)
	{
		generatePermutation(A, n);

		for(int i = 0; i < n; i++)
		{
			cerr << A[i] << " ";
		}
		cerr << endl << "searching for " << stat << "'th minimal element" << endl;

		rsResult = RandomSelect(A, 0, n, stat, comp, shifts);
		sResult = Select(A, 0, n, stat, comp, shifts);
	}

	bool printed = false;
	for(int i = 0; i < n; i++)
	{
		if(printed == false)
		{
			if(A[i] == rsResult)
			{
				cout << "[" << A[i] << "]" << " ";
				printed = true;
			}
			else
				cout << A[i] << " ";
		}
		else
		{
			cout << A[i] << " ";
		}
	}
	cout << endl;
	cerr << "Comparisons: " << *comp << endl;
	cerr << "Shifts: " << *shifts << endl;
}

void generateRandom(int A[], int n)
{
	for(int i = 0; i < n; i++)
	{
		A[i] = rand() % n;
	}
}

void generatePermutation(int A[], int n)
{
	for(int i = 0; i < n; i++)
	{
		int element = rand() % n + 1;
		while(inSet(A, i, element) == true)
		{
			element = rand() % n + 1;
		}
		A[i] = element;
	}
}

bool inSet(int A[], int n, int x)
{
	for(int i = 0; i < n; i++)
	{
		if(A[i] == x)
			return true; //true if x is already in A
	}
	return false;
}

int RandomSelect(int A[], int p, int q, int k, int * comp, int * shifts)
{
	if(p == q - 1) //condition to stop recursive calls at some point
		return A[p];

	int r = RandomPartition(A, p, q, comp, shifts); //get index of pivot, and partition array around it
	cerr << "pivot: " << r << endl;
	int s = r - p + 1;

	if(k == s)
		return A[r];
	if(k < s)
		RandomSelect(A, p, r, k, comp, shifts); //seek k'th minimal element in one of two parts, it cant be in the other
	else
		RandomSelect(A, r + 1, q, k - s, comp, shifts);
}

int RandomPartition(int A[], int p, int r, int * comp, int * shifts)
{
	int i = rand() % r + p; //get index od pivot
	swap(A[r - 1], A[i]); //adjust its position
	return partition(A, p, r, comp, shifts); //make normal partition
}

//normal partition
int partition(int A[], int p, int r, int * comparisons, int * shifts)
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

int Select(int A[], int p, int q, int k, int * comp, int * shifts)
{
	int length = q - p;

	if(length <= 5) //if array length is less than 5, just return its middle value
	{
		insertionSort(A, p, q, comp, shifts);
		return A[p + k - 1];
	}

	int segments = length / 5;
	int remainder = length % 5;
	int * medians;
	int n;
	
	if(remainder == 0)
	{
		n = length / 5;
		medians = new int[n];
	}
	else
	{
		n = (length + 5) / 5;
		medians = new int[n];
	}
	int j = 0;
	for(int i = 0; i < segments; i++)
	{
		insertionSort(A, p + i * 5, p + (i + 1) * 5, comp, shifts); //do insertionSort of every 5-element segment of array
		medians[j] = A[p + 2 + i * 5]; //building array of medians
		j++;
	}

	if(remainder != 0)
	{
		insertionSort(A, p + segments * 5, q, comp, shifts);
		medians[j] = A[p + segments * 5 + remainder / 2];
	}

	int x = Select(medians, 0, n, (n + 1) / 2, comp, shifts); //get median of medians
	int y = selectPartition(A, p, q - 1, x); //partition array around median of medians

	if(y == k - 1)
		return x;
	if(k - 1 < y)
		return Select(A, p, y, k, comp, shifts); //seek k'th minimal element in proper part
	else
		return Select(A, y + 1, q, k - y, comp, shifts);
}

//normal insertionSort
void insertionSort(int A[], int p, int n, int * comparisons, int * shifts)
{
	for(int i = p; i < n; i++)
	{
		int key = A[i];
		int j = i - 1;

		cerr << "Comparison: " << A[j] << ", " << key << endl;
		(*comparisons)++;

		while(j >= p && A[j] > key)
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

//a little edited partition
int selectPartition(int arr[], int l, int r, int x)
{
    	int i;
    	for (i = l; i < r; i++)
        	if (arr[i] == x)
           		break;

    	swap(arr[i], arr[r]);

    	i = l;
   	for (int j = l; j <= r - 1; j++)
    	{
		if (arr[j] <= x)
		{
		    	swap(arr[i], arr[j]);
		    	i++;
		}
    	}
    	swap(arr[i], arr[r]);

    	return i;
}
