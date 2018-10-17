#include <iostream>
#include <climits>
#include <cstdlib>
#define INIT_SIZE 128
using namespace std;

class ListNode
{
public:
	int vertex;
	double weight;
	ListNode * next;
};

class SingleLinkedList
{
public:
	ListNode * root;

	SingleLinkedList()
	{
		root = NULL;
	}

	void insert(int targetVertex, double edgeWeight)
	{
		if(root == NULL)
		{	
			ListNode * new_node = new ListNode;

			new_node -> vertex = targetVertex;
			new_node -> weight = edgeWeight;
			new_node -> next = NULL;

			root = new_node;
		}
		else
		{
			ListNode * new_node = new ListNode;

			new_node -> vertex = targetVertex;
			new_node -> weight = edgeWeight;
			new_node -> next = NULL;

			ListNode * last = root;
			while(last -> next != NULL)
				last = last -> next;

			last -> next = new_node; 
		}
	}

	int search(ListNode * n, int value)
	{
		if(n == NULL)
		{
			return 0;
		}
		else if(n -> vertex == value)
			return 1;

		while(n -> next != NULL)
		{
			if(n -> vertex == value)
				return 1;
			n = n -> next;
		}
			
		if(n -> vertex == value)
			return 1;

		return 0;
	}

	void del(int value)
	{
		if(root == NULL)
			return;
		else if(root -> next == NULL)
		{
			delete root;
			root = NULL;
		}
		else
		{
			ListNode * prev = root;
			ListNode * to_del = root -> next;

			while(to_del -> vertex != value && to_del -> next != NULL)
			{
				prev = to_del;
				to_del = to_del -> next;
			}

			if(to_del -> vertex == value)
			{
				if(to_del -> next == NULL)
				{
					delete(to_del);
					prev -> next = NULL;
				}
				else
				{
					prev -> next = to_del -> next;
					delete(to_del);
				}
			}
		}
	}
};

class Element
{
public:
	int key;
	double priority;

	Element()
	{
		key = INT_MAX;
		priority = INT_MAX;
	}

	Element(int a, double b)
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

	void decreaseKey(int i, double key)
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

	void insert(int key, double priority)
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

class Graph
{
public:
	int verticesNumber;
	SingleLinkedList * vertices;

	Graph(int verticesNum)
	{
		verticesNumber = verticesNum;
		vertices = new SingleLinkedList[verticesNum];
	}

	void addEdge(int source, int sink, double weight)
	{
		vertices[source - 1].insert(sink, weight);
	}

	void edgeSet()
	{
		for(int i = 0; i < verticesNumber; i++)
		{
			if(vertices[i].root != NULL)
			{
				cout << i + 1 << " -> ";
				
				ListNode * node = vertices[i].root;
				while(node -> next != NULL)
				{
					cout << "(" << node -> vertex << "," << node -> weight << ") ";
					node = node -> next;
				}
				cout << "(" << node -> vertex << "," << node -> weight << ") ";
			}
			cout << endl;
		}
	}
};

class Dijkstra
{
public:
	int verticesNum;
	int startingVertex;
	double * distance;
	int * previous;
	Graph * graph;

	Dijkstra(Graph * g, int start)
	{
		graph = g;
		verticesNum = graph -> verticesNumber;
		startingVertex = start;
		distance = new double[verticesNum];
		previous = new int[verticesNum];
	}

	void findShortestPath()
	{
		PriorityQueue * queue = new PriorityQueue(verticesNum);

		for(int i = 0; i < verticesNum; i++)
		{
			distance[i] = INT_MAX;
			previous[i] = 0;
			queue -> insert(i, distance[i]);
		}

		distance[startingVertex - 1] = 0;
		queue -> decreaseKey(startingVertex - 1, 0);

		while(queue -> empty() == false)
		{
			Element * el = queue -> extractMin();

			if(graph -> vertices[el -> key].root != NULL)
			{
				ListNode * node = graph -> vertices[el -> key].root;
				while(node -> next != NULL)
				{
					if(distance[node -> vertex - 1] > distance[el -> key] + node -> weight)
					{
						distance[node -> vertex - 1] = distance[el -> key] + node -> weight;
						previous[node -> vertex - 1] = el -> key;

						for(int j = 0; j < queue -> heap -> heap_size; j++)
						{
							if(queue -> heap -> array[j].key == node -> vertex - 1)
							{
								queue -> decreaseKey(j, distance[node -> vertex - 1]);
								break;
							}
						}
					}

					node = node -> next;
				}

				if(distance[node -> vertex - 1] > distance[el -> key] + node -> weight)
				{
					distance[node -> vertex - 1] = distance[el -> key] + node -> weight;
					previous[node -> vertex - 1] = el -> key;

					for(int j = 0; j < queue -> heap -> heap_size; j++)
					{
						if(queue -> heap -> array[j].key == node -> vertex - 1)
						{
							queue -> decreaseKey(j, distance[node -> vertex - 1]);
							break;
						}
					}
				}
			}
		}
	}
};

int main()
{
	clock_t start = clock();

	int verticesNumber;
	cin >> verticesNumber;

	Graph * graph = new Graph(verticesNumber);

	int edgesNumber;
	cin >> edgesNumber;

	for(int i = 0; i < edgesNumber; i++)
	{
		int vertex1;
		int vertex2;
		double weight;

		cin >> vertex1;
		cin >> vertex2;
		cin >> weight;

		graph -> addEdge(vertex1, vertex2, weight);
	}

	int startingVertex;
	cin >> startingVertex;

	Dijkstra * dijkstra = new Dijkstra(graph, startingVertex);
	dijkstra -> findShortestPath();

	for(int i = 0; i < verticesNumber; i++)
	{
		cout << i + 1 << " " << dijkstra -> distance[i] << endl;
	}

	for(int i = 0; i < verticesNumber; i++)
	{
		int a = dijkstra -> previous[i];
		double diff = dijkstra -> distance[i];
		string finalString = to_string(i + 1);

		while(a != 0)
		{
			diff -= dijkstra -> distance[a];
			finalString = to_string(a + 1) + " --(" + to_string(diff) + ")-> " + finalString;
			diff = dijkstra -> distance[a];
			a = dijkstra -> previous[a];
		}

		diff -= dijkstra -> distance[a];
		finalString = to_string(a + 1) + " --(" + to_string(diff) + ")-> " + finalString;
		cerr << finalString << endl;
	}

	clock_t end = clock();
	double result = end - start;
	cerr << "Time: " << result / CLOCKS_PER_SEC << endl;
}
