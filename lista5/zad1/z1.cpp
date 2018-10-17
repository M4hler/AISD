/*
*	Oskar Makowski
*/

#include <iostream>
#include <climits>
#define INIT_SIZE 128
using namespace std;

class Element
{
public:
	int key;
	int priority;

	Element()
	{
		key = INT_MAX;
		priority = INT_MAX;
	}

	Element(int a, int b)
	{
		key = a;
		priority = b;
	}
};

class Heap
{
public:
	int length;
	int heap_size;
	Element * array;

	Heap(int size)
	{
		length = size;
		array = new Element[length];
		heap_size = 0;
	}

	int parent(int i)
	{
		return (i - 1) / 2;
	}

	int left(int i)
	{
		return 2 * i + 1;
	}

	int right(int i)
	{
		return 2 * (i + 1);
	}

	void heapify(int i)
	{
		int l = left(i);
		int r = right(i);

		int smallest;
		if(l < heap_size && array[l].priority < array[i].priority)
		{
			smallest = l;
		}
		else
		{
			smallest = i;
		}

		if(r < heap_size && array[r].priority < array[smallest].priority)
		{
			smallest = r;
		}

		if(smallest != i)
		{
			swap(array[i], array[smallest]);
			heapify(smallest);
		}
	}

	void buildHeap()
	{
		heap_size = length;

		for(int i = (length - 1) / 2; i >= 0; i--)
		{
			heapify(i);
		}
	}
};

class PriorityQueue
{
public:
	Heap * heap;

	PriorityQueue(int size)
	{
		heap = new Heap(size);
	}

	Element * min()
	{
		if(heap -> heap_size < 1)
			return NULL;
		else
			return new Element(heap -> array[0].key, heap -> array[0].priority);
	}

	Element * extractMin()
	{
		if(heap -> heap_size < 1)
		{
			cout << "Heap is empty" << endl;
			return NULL;
		}

		Element * tmp = &(heap -> array[0]);
		Element * min = new Element(tmp -> key, tmp -> priority);

		heap -> array[0] = heap -> array[heap -> heap_size - 1];
		heap -> heap_size--;

		heap -> heapify(0);

		return min;
	}

	void decreaseKey(int i, int key)
	{
		if(key > heap -> array[i].priority)
		{
			cout << "New key can't be greater than original one" << endl;
			return;
		}

		heap -> array[i].priority = key;
		while(i > 0 && heap -> array[heap -> parent(i)].priority > heap -> array[i].priority)
		{
			swap(heap -> array[i], heap -> array[heap -> parent(i)]);
			i = heap -> parent(i);
		}
	}

	void insert(int key, int priority)
	{
		heap -> heap_size++;
		heap -> array[heap -> heap_size - 1].key = key;
		decreaseKey(heap -> heap_size - 1, priority);
	}

	bool empty()
	{
		if(heap -> heap_size == 0)
			return true;
		else
			return false;
	}
};

int main()
{
	PriorityQueue * queue = new PriorityQueue(INIT_SIZE);

	int n;
	cin >> n;

	for(int i = 0; i < n; i++)
	{
		string instruction;
		cin >> instruction;

		if(instruction == "insert")
		{
			int param1, param2;
			cin >> param1;
			cin >> param2;

			queue -> insert(param1, param2);
		}
		else if(instruction == "empty")
		{
			bool empty = queue -> empty();

			if(empty == true)
				cout << "1" << endl;
			else
				cout << "0" << endl;
		}
		else if(instruction == "top")
		{
			Element * el = queue -> min();

			if(el == NULL)
				cout << endl;
			else
				cout << el -> key << endl;

			delete(el);
		}
		else if(instruction == "pop")
		{
			Element * el = queue -> extractMin();

			if(el == NULL)
				cout << endl;
			else
				cout << el -> key << endl;

			delete(el);
		}
		else if(instruction == "priority")
		{
			int param1, param2;
			cin >> param1;
			cin >> param2;

			for(int i = 0; i < queue -> heap -> heap_size; i++)
			{
				if(queue -> heap -> array[i].key == param1)
					queue -> decreaseKey(i, param2);
			}
		}
		else if(instruction == "print")
		{
			for(int i = 0; i < queue -> heap -> heap_size; i++)
			{
				cout << "(" << queue -> heap -> array[i].key << "," << queue -> heap -> array[i].priority << ") ";
			}
			cout << endl;
		}
	}
}
