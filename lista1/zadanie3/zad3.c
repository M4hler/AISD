#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

struct node
{
	int key;
	struct node * next;
	struct node * prev;
};

bool empty(struct node **);
void insert_back(struct node **, int);
void insert_front(struct node **, int);
void insert_inside(struct node ** start, int value1, int value2);
void print_all(struct node *);
void merge(struct node *, struct node *);
void search_next(struct node *, int);
void search_prev(struct node *, int);
void random_el(struct node **);

int main(int argc, char * argv[])
{
	struct node * list = NULL;
	struct node * list2 = NULL;

	for(int i = 0; i < 10; i++)
	{
		insert_front(&list, i);
		insert_front(&list2, 10 + i);
	}

	random_el(&list);
}

void merge(struct node * list1, struct node * list2)
{
	if(list1 == list2)
	{
		struct node * copy = NULL;
		struct node * last = (*list2).prev;

		while((*last).prev != list2)
		{
			insert_back(&copy, (*last).key);
			last = (*last).prev;
		}
		insert_back(&copy, (*list2).key);
		merge(list1, copy);
	}
	else
	{
		struct node * last1 = (*list1).prev;
		struct node * last2 = (*list2).prev;	
		
		(*last1).next = list2;
		(*list2).prev = last1;

		(*last2).next = list1;
		(*list1).prev = last2;
	}
}

void random_el(struct node ** n)
{
	srand(time(NULL));
	for(int i = 0; i < 1000; i++)
	{
		insert_back(n, rand() % 100);
	}

	int number = 990;
	clock_t start = clock();

	for(int i = 0; i < 1000; i++)
	{
		if(1000 - number < 500)
			search_next(*n, 1000 - number);
		else
			search_prev(*n, number);
	}
	double result = clock() - start;
	printf("clicks: %f time: %f looking for %d element\n", result, result/CLOCKS_PER_SEC, number);

	clock_t start2 = clock();
	for(int i = 0; i < 1000; i++)
	{
		int a = rand() % 1000;		
		if(1000 - a < 500)
			search_next(*n, 1000 - a);
		else
			search_prev(*n, a);
	}
	double result2 = clock() - start2;
	printf("clicks: %f time: %f looking for random elements\n", result2, result2/CLOCKS_PER_SEC);
}

void search_next(struct node * n, int value)
{
	if(empty(&n) == true)
	{
		printf("List is empty\n");
		return;
	}

	for(int i = 0; i < value; i++)
	{
		n = (*n).next;
	}
}

void search_prev(struct node * n, int value)
{
	if(empty(&n) == true)
	{
		printf("List is empty\n");
		return;
	}

	for(int i = 0; i < value; i++)
	{
		n = (*n).prev;
	}
}

void insert_back(struct node ** start, int value)
{
	if(empty(start) == true)
	{		
		struct node * new_node = malloc(sizeof(struct node));
		(*new_node).key = value;
		(*new_node).next = (*new_node).prev = new_node;
		*start = new_node;
	}
	else
	{
		struct node * last = (**start).prev;
		struct node * new_node = malloc(sizeof(struct node));
		(*new_node).key = value;
		(*new_node).next = *start;
		(**start).prev = new_node;
		(*new_node).prev = last;
		(*last).next = new_node;
	}
}

void insert_front(struct node ** start, int value)
{
	if(empty(start) == true)
	{		
		struct node * new_node = malloc(sizeof(struct node));
		(*new_node).key = value;
		(*new_node).next = (*new_node).prev = new_node;
		*start = new_node;
	}
	else
	{
		struct node * last = (**start).prev;
		struct node * new_node = malloc(sizeof(struct node));
		(*new_node).key = value;
		(*new_node).next = *start;
		(*new_node).prev = last;
		(*last).next = (**start).prev = new_node;
		*start = new_node;
	}
}

void insert_inside(struct node ** start, int value1, int value2)
{
	struct node * new_node = malloc(sizeof(struct node));
	(*new_node).key = value1;

	struct node * tmp = *start;
	while((*tmp).key != value2)
	{
		tmp = (*tmp).next;
		if(tmp == *start)
		{
			printf("Cant insert after node with the given key\n");			
			return;
		}
	}
	struct node * nxt = (*tmp).next;
	(*tmp).next = new_node;
	(*new_node).prev = tmp;
	(*new_node).next = nxt;
	(*nxt).prev = new_node;
}

void print_all(struct node * n)
{
	struct node * tmp = n;

	while((*tmp).next != n)
	{
		printf("%d ", (*tmp).key);
		tmp = (*tmp).next;
	}
	printf("%d", (*tmp).key);
}

bool empty(struct node ** n)
{
	if(*n == NULL)
		return true;
	else
		return false;
}
