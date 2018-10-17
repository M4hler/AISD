#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

struct node
{
	int key;
	struct node * next;
};

bool empty(struct node **);
void insert_front(struct node **);
void insert_back(struct node **);
void insert_back2(struct node **, int);
void print_all(struct node *);
void key_search(struct node *);
void search_element(struct node *);
void search(struct node *, int);
void delete(struct node **);
void merge(struct node *, struct node *);
void random_el(struct node **);

int main(int argc, char * argv[])
{
	struct node * list1 = NULL;

	int choice;
	do
	{
		printf("\n[0] - exit\n");
		printf("[1] - insert at the beginning\n");
		printf("[2] - insert at the end\n");
		printf("[3] - delete\n");
		printf("[4] - empty\n");
		printf("[5] - print all\n");
		printf("[6] - search with key\n");
		printf("[7] - search i-th element\n");
		printf("[8] - merge\n");
		printf("[9] - fill with random number\n");
		printf("Option: ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 0:
				printf("Exit\n");
				break;

			case 1:
				insert_front(&list1);
				break;

			case 2:
				insert_back(&list1);
				break;

			case 3:
				delete(&list1);
				break;

			case 4:
				if(empty(&list1) == true)
				{
					printf("List is empty\n");
				}
				else
				{
					printf("List is not empty\n");
				}
				break;

			case 5:
				print_all(list1);
				break;

			case 6:
				key_search(list1);
				break;

			case 7:
				search_element(list1);
				break;

			case 8: 
				merge(list1, list1);
				break;

			case 9:
				random_el(&list1);
				break;

			default:
				printf("No such an action!\n");
				break;
		}
	} while(choice != 0);
}

void random_el(struct node ** n)
{
	srand(time(NULL));
	for(int i = 0; i < 1000; i++)
	{
		insert_back2(n, rand() % 100);
	}

	int number = 990;
	clock_t start = clock();

	for(int i = 0; i < 1000; i++)
	{
		search(*n, number);
	}
	double result = clock() - start;
	printf("clicks: %f time: %f looking for %d element\n", result, result/CLOCKS_PER_SEC, number);

	clock_t start2 = clock();
	for(int i = 0; i < 1000; i++)
	{
		int a = rand() % 1000;		
		search(*n, a);
	}
	double result2 = clock() - start2;
	printf("clicks: %f time: %f looking for random elements\n", result2, result2/CLOCKS_PER_SEC);
}

void search(struct node * n, int value)
{
	if(empty(&n) == true)
	{
		printf("List is empty\n");
		return;
	}

	for(int i = 1; i < value; i++)
	{
		if((*n).next == NULL)
		{
			printf("There is no such an element");
			return;
		}		
		n = (*n).next;
	}
}

void merge(struct node * n1, struct node * n2)
{
	if(n1 == NULL || n2 == NULL)
		return;
	if(n1 == n2)
	{
		struct node * copy = NULL;

		while((*n2).next != NULL)
		{
			insert_back2(&copy, (*n2).key);
			n2 = (*n2).next;
		}
		insert_back2(&copy, (*n2).key);
		
		(*n2).next = copy;
	}
	else
	{
		while((*n1).next != NULL)
		{
			n1 = (*n1).next;
		}
		(*n1).next = n2;
	}
}

void insert_back2(struct node ** n, int value)
{	
	if(empty(n) == true)
	{	
		struct node * new_node = malloc(sizeof(struct node *));

		(*new_node).key = value;
		(*new_node).next = NULL;

		*n = new_node;
	}
	else
	{
		struct node * new_node = malloc(sizeof(struct node *));

		(*new_node).key = value;
		(*new_node).next = NULL;

		struct node * last = *n;
		while((*last).next != NULL)
			last = (*last).next;

		(*last).next = new_node; 
	}
}

void insert_front(struct node ** n)
{
	if(empty(n) == true)
	{
		struct node * new_node = malloc(sizeof(struct node *));

		int value;
		printf("Give value: ");
		scanf("%d", &value);

		(*new_node).key = value;
		(*new_node).next = NULL;

		*n = new_node;
	}
	else
	{
		struct node * new_node = malloc(sizeof(struct node *));

		int value;
		printf("Give value: ");
		scanf("%d", &value);

		(*new_node).key = value;
		(*new_node).next = *n;

		*n = new_node;
	}
}

void delete(struct node ** n)
{
	if(empty(n) == true)
	{
		printf("List is empty, nothing to delete\n");
		return;
	}

	int value;
	printf("Give number of element to delete: ");
	scanf("%d", &value);

	if(value == 1)
	{
		*n = (**n).next;
	}
	else
	{
		struct node * del = *n;
		for(int i = 1; i < value - 1; i++)
		{
			del = (*del).next;
			if((*del).next == NULL)
			{
				printf("There is no such an element");
				return;
			}
		}
		struct node * tmp = del;
		(*del).next = (*(*tmp).next).next;
	}
}

void search_element(struct node * n)
{
	if(empty(&n) == true)
	{
		printf("List is empty\n");
		return;
	}

	int value;
	printf("Give number of element you are looking for: ");
	scanf("%d", &value);

	for(int i = 1; i < value; i++)
	{
		if((*n).next == NULL)
		{
			printf("There is no such an element");
			return;
		}		
		n = (*n).next;
	}

	printf("%dth element has value %d\n", value, (*n).key);
}

void key_search(struct node * n)
{
	if(empty(&n) == true)
	{
		printf("List is empty, there are no keys\n");
		return;
	}

	int value;
	printf("Give value you are looking for: ");
	scanf("%d", &value);

	int i = 1;
	while((*n).next != NULL && (*n).key != value)
	{
		n = (*n).next;
		i++;
	}

	if((*n).next == NULL && (*n).key != value)
	{
		printf("Given value was not found\n");
		return;
	}

	printf("%dth elements in the list has given value\n", i);
}

void insert_back(struct node ** n)
{
	if(empty(n) == true)
	{
		struct node * new_node = malloc(sizeof(struct node *));

		int value;
		printf("Give value: ");
		scanf("%d", &value);

		(*new_node).key = value;
		(*new_node).next = NULL;

		*n = new_node;
	}
	else
	{
		struct node * new_node = malloc(sizeof(struct node *));
		int value;
		printf("Give value: ");
		scanf("%d", &value);

		(*new_node).key = value;
		(*new_node).next = NULL;

		struct node * last = *n;
		while((*last).next != NULL)
			last = (*last).next;

		(*last).next = new_node; 
	}
}

void print_all(struct node * n)
{
//	system("clear");
	if(empty(&n) == true)
	{
		printf("List is empty\n");
		return;
	}	
	
	struct node * a = n;	
	while((*a).next != NULL)
	{
		printf("%d\n", (*a).key);
		a = (*a).next;
	}
	printf("%d\n", (*a).key);
}

bool empty(struct node ** n)
{
	if(*n == NULL)
		return true;
	else
		return false;
}
