#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int binarySearch(int [], int, int, int);
void test();

int main()
{
	srand(time(0));

	int n;
	cin >> n;
	int A[n];

	for(int i = 0; i < n; i++)
	{
		cin >> A[i];
	}
	cout << endl;

	int value;
	cin >> value;

	int result = binarySearch(A, 0, n, value);
	cout << "Res: " << result << endl;

	test();
}

int binarySearch(int A[], int p, int q, int x)
{
	if(p <= q) //condition to stop recursive calls
	{
		int mid = (q + p) / 2; //set index of middle element
		if(A[mid] == x) //we were looking for middle element - return 1
			return 1;

		if(A[mid] > x) //array is sorted so we know in which half element may be
		{
			return binarySearch(A, p, mid - 1, x);
		}
		else
		{
			return binarySearch(A, mid + 1, q, x);
		}
	}
	return 0; //element x wasnt found
}

//testing procedure
void test()
{
	int n = 100;
	int A[n];

	for(int i = 0; i < n; i++)
	{
		A[i] = 1000 * (i + 1);
		int B[A[i]];

		for(int j = 0; j < B[A[i]]; j++)
		{
			B[j] = j * 2;
		}

		int value = rand() % A[i];
		int res = binarySearch(B, 0, A[i], value);
		cout << res << " ";
	}
}
