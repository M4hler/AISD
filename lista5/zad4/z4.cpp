#include <iostream>
#include <climits>
#include <string.h>
#include <cstdlib>
#include <ctime>
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

	int search(int x)
	{
		for(int i = 0; i < heap -> heap_size; i++)
		{
			if(heap -> array[i].key == x)
				return true;
		}
		
		return false;
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

class Edge
{
public:
	int source;
	int sink;
	double weight;
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

	void createEdgeSet(Edge * edgeSet)
	{
		int j = 0;
		for(int i = 0; i < verticesNumber; i++)
		{
			if(vertices[i].root != NULL)
			{
				ListNode * node = vertices[i].root;
				while(node -> next != NULL)
				{
					edgeSet[j].source = i + 1;
					edgeSet[j].sink = node -> vertex;
					edgeSet[j].weight = node -> weight;
					j++;
					node = node -> next;
				}

				edgeSet[j].source = i + 1;
				edgeSet[j].sink = node -> vertex;
				edgeSet[j].weight = node -> weight;
				j++;
			}
		}
	}
};

class Prim
{
public:
	Graph * graph;
	int verticesNum;
	int startingVertex;
	double * distance;
	int * previous;

	Prim()
	{
		graph = NULL;
	}

	void set(Graph * g, int start)
	{
		graph = g;
		verticesNum = graph -> verticesNumber;
		startingVertex = start;
		distance = new double[verticesNum];
		previous = new int[verticesNum];
	}

	void minimalSpanningTree()
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
					if(queue -> search(node -> vertex - 1) == true && (distance[node -> vertex - 1] > node -> weight))
					{
						distance[node -> vertex - 1] = node -> weight;
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

				if(queue -> search(node -> vertex - 1) == true && (distance[node -> vertex - 1] > node -> weight))
				{
					distance[node -> vertex - 1] = node -> weight;
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

/*	void findShortestPath()
	{
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
	} */
};

class Set
{
public:
	int parent;
	int rank;

	static int find(Set * sets, int i)
	{
		if(sets[i].parent != i)
		{
			sets[i].parent = find(sets, sets[i].parent);
		}

		return sets[i].parent;
	}

	static void setsUnion(Set * sets, int x, int y)
	{
		int rx = find(sets, x);
		int ry = find(sets, y);

		if(sets[rx].rank < sets[ry].rank)
		{
			sets[rx].parent = ry;
		}
		else if(sets[rx].rank > sets[ry].rank)
		{
			sets[ry].parent = rx;
		}
		else
		{
			sets[ry].parent = rx;
			sets[ry].rank++;
		}
	}
};

class Kruskal
{
public:
	Graph * graph;

	Kruskal()
	{
		graph = NULL;
	}

	Graph * minimalSpanningTree(int edgesNumber)
	{
		Set * sets = new Set[graph -> verticesNumber];
		for(int i = 0; i < graph -> verticesNumber; i++)
		{
			sets[i].parent = i;
			sets[i].rank = 0;
		}

		Graph * resultGraph = new Graph(graph -> verticesNumber);

		Edge * edgeSet = new Edge[2 * edgesNumber];
		graph -> createEdgeSet(edgeSet);

		qsort(edgeSet, 2 * edgesNumber, sizeof(edgeSet[0]), myComp);

		for(int i = 0; i < 2 * edgesNumber; i++)
		{
			Edge edge = edgeSet[i];
			int x = Set::find(sets, edge.source);
			int y = Set::find(sets, edge.sink);
			if(x != y)
			{
				resultGraph -> addEdge(edge.source, edge.sink, edge.weight);
				resultGraph -> addEdge(edge.sink, edge.source, edge.weight); //added
				Set::setsUnion(sets, x, y);
			}
		}

		return resultGraph;
	}

	static int myComp(const void * p1, const void * p2)
	{
		Edge * a = (Edge *)p1;
		Edge * b = (Edge *)p2;
		return a -> weight > b -> weight;
	}
};

class RandomWalk
{
public:
	Graph * graph;
	int * visited;
	int verticesNum;
	clock_t begin;
	
	RandomWalk(Graph * g)
	{
		begin = clock();

		graph = g;
		verticesNum = graph -> verticesNumber;
		visited = new int[verticesNum];

		for(int i = 0; i < verticesNum; i++)
		{
			visited[i] = 0;
		}
	}

	void start()
	{
		int startingVertex = rand() % graph -> verticesNumber;
		int visits = 1;
		int k = 0;
		double W = 0;
		int M = sizeof(int) * verticesNum;
		visited[startingVertex] = 1;

		while(visits < verticesNum)
		{
			k++;

			int target = rand() % (verticesNum - 1);
			ListNode * node = graph -> vertices[startingVertex].root;

			for(int j = 0; j < target; j++)
			{
				node = node -> next;
			}

			W += node -> weight;
			startingVertex = node -> vertex - 1;
			if(visited[startingVertex] == 0)
			{
				visited[startingVertex] = 1;
				visits++;
			}
		}

		double result = clock() - begin;
		cout << "Random: " << k << " " << W << " " << M << " " << result / CLOCKS_PER_SEC << endl;
	}
};

class LowestWeightWalk
{
public:
	Graph * graph;
	int * visited;
	int verticesNum;
	clock_t begin;

	LowestWeightWalk(Graph * g)
	{
		begin = clock();
		graph = g;
		verticesNum = graph -> verticesNumber;
		visited = new int[verticesNum];

		for(int i = 0; i < verticesNum; i++)
		{
			visited[i] = 0;
		}
	}	

	void start()
	{
		int startingVertex = rand() % graph -> verticesNumber;
		int visits = 1;
		int k = 0;
		double W = 0;
		int M = sizeof(int) * verticesNum;
		visited[startingVertex] = 1;

		while(visits < verticesNum)
		{
			k++;

			double minWeight = INT_MAX;
			ListNode * node = graph -> vertices[startingVertex].root;
			ListNode * target;

			for(int j = 0; j < verticesNum - 1; j++)
			{
				if(node -> weight < minWeight && visited[node -> vertex - 1] == 0)
				{
					target = node;
				}

				node = node -> next;
			}

			W += target -> weight;
			startingVertex = target -> vertex - 1;
			visited[startingVertex] = 1;
			visits++;
		}

		double result = clock() - begin;
		cout << "Lowest weight: " << k << " " << W << " " << M << " " << result / CLOCKS_PER_SEC << endl;
	}
};

class EulerWalkKruskal
{
public:
	Graph * graph;
	int * visited;
	int verticesNum;
	clock_t begin;

	EulerWalkKruskal(Graph * g)
	{
		begin = clock();
		graph = g;
		verticesNum = graph -> verticesNumber;
		visited = new int[verticesNum];

		for(int i = 0; i < verticesNum; i++)
		{
			visited[i] = 0;
		}
	}

	void start()
	{
		int startingVertex = rand() % graph -> verticesNumber;
		int visits = 1;
		int k = 0;
		double W = 0;
		int M = sizeof(int) * verticesNum;
		visited[startingVertex] = 1;

		Kruskal * kruskal = new Kruskal();
		kruskal -> graph = graph;

		int edgesNumber = (verticesNum * (verticesNum - 1)) / 2;
		Graph * mst = kruskal -> minimalSpanningTree(edgesNumber);
		M += mst -> verticesNumber * sizeof(int) + edgesNumber * sizeof(ListNode);

		while(visits < verticesNum)
		{
			k++;

			ListNode * node = mst -> vertices[startingVertex].root;
			ListNode * target;
			int minVisited = 2;

			while(node -> next != NULL)
			{
				if(visited[node -> vertex - 1] < minVisited)
				{
					minVisited = visited[node -> vertex - 1];
					target = node;

					if(minVisited == 0)
						break;
				}

				node = node -> next;
			}

			if(visited[node -> vertex - 1] < minVisited)
			{
				minVisited = visited[node -> vertex - 1];
				target = node;
			}

			W += target -> weight;

			if(minVisited == 0)
			{
				startingVertex = target -> vertex - 1;
				visited[startingVertex]++;
			}
			else
			{
				visited[startingVertex]++;
				startingVertex = target -> vertex - 1;
				visits++;
			}
		}

		double result = clock() - begin;
		cout << "Euler kruskal: " << k << " " << W << " " << M << " " << result / CLOCKS_PER_SEC << endl;
	}
};

class EulerWalkPrim
{
public:
	Graph * graph;
	int verticesNum;
	clock_t begin;

	EulerWalkPrim(Graph * g)
	{
		begin = clock();
		graph = g;
		verticesNum = graph -> verticesNumber;
	}

	void start()
	{
		int startingVertex = rand() % graph -> verticesNumber;
		int k = 0;
		double W = 0;
		int M = sizeof(int) * verticesNum + (verticesNum * (verticesNum - 1)) / 2 * sizeof(ListNode);

		Prim * prim = new Prim();
		prim -> graph = graph;
		prim -> set(graph, startingVertex);
		prim -> minimalSpanningTree();

		for(int i = 0; i < verticesNum; i++)
		{
			int a = prim -> previous[startingVertex];

			if(i != a)
			{
				W += prim -> distance[i];
			}
			k++;
		}

		double result = clock() - begin;
		cout << "Euler prim: " << k << " " << W << " " << M << " " << result / CLOCKS_PER_SEC << endl;
	}
};

int main(int argc, char * argv[])
{
	srand(time(0));

	int verticesNumber;
	cin >> verticesNumber;

	Graph * graph = new Graph(verticesNumber);

	int edgesNumber = (verticesNumber * (verticesNumber - 1)) / 2;
	for(int i = 0; i < edgesNumber; i++)
	{
		int vertex1;
		int vertex2;
		double weight;

		cin >> vertex1;
		cin >> vertex2;
		cin >> weight;

		graph -> addEdge(vertex1, vertex2, weight);
		graph -> addEdge(vertex2, vertex1, weight);
	}

	RandomWalk * randomWalk = new RandomWalk(graph);
	randomWalk -> start();

	LowestWeightWalk * lowestWeightWalk = new LowestWeightWalk(graph);
	lowestWeightWalk -> start();

	EulerWalkKruskal * eulerWalkKruskal = new EulerWalkKruskal(graph);
	eulerWalkKruskal -> start();

	EulerWalkPrim * eulerWalkPrim = new EulerWalkPrim(graph);
	eulerWalkPrim -> start();
}
