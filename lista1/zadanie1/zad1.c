#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct fifo_queue
{
	int size;	
	int * head;
	int * tail;
};

void init(struct fifo_queue *, int);
void dequeue(struct fifo_queue *);
void enqueue(struct fifo_queue *);
bool empty(struct fifo_queue *);
void shift(struct fifo_queue *);

int main(int argc, char * argv[])
{
	int size;	
	printf("Give size: ");
	scanf("%d", &size);	
	
	struct fifo_queue * queue;
	init(queue, size);

	int choice;
	do
	{
		printf("\n[0] - exit\n");
		printf("[1] - enqueue\n");
		printf("[2] - dequeue\n");
		printf("[3] - empty\n");
		printf("Option: ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 0:
				printf("Exit\n");
				break;

			case 1:
				enqueue(queue);
				break;

			case 2:
				dequeue(queue);
				break;

			case 3:
				if(empty(queue) == true)
				{
					printf("Queue is empty\n");
				}
				else
				{
					printf("Queue is not empty\n");
				}
				break;

			default:
				printf("No such an action!\n");
				break;
		}
	} while(choice != 0);
}

void init(struct fifo_queue * fq, int s)
{
	(*fq).size = s;	
	(*fq).head = malloc(sizeof(int) * s);
	(*fq).tail = (*fq).head;
}

void dequeue(struct fifo_queue * fq)
{
	if(empty(fq) == true)
	{
		printf("Cant dequeue; queue is empty\n");
		return;
	}

	printf("Dequeued element: %d\n", *((*fq).head));
	shift(fq);
}

void enqueue(struct fifo_queue * fq)
{
	int value;	
	printf("Give value(int): ");
	scanf("%d", &value);

	if((*fq).tail - (*fq).head == (*fq).size)
	{
		printf("Queue is full\n");
		return;
	}

	*((*fq).tail) = value;
	(*fq).tail++;
}

void shift(struct fifo_queue * fq)
{
	int * tmp = (*fq).head;
	int * tmp2 = (*fq).head + 1;
	for(int i = 0; tmp2 != (*fq).tail; i++)
	{
		*tmp = *tmp2;
		tmp++;
		tmp2++;
	}
	(*fq).tail--;
}

bool empty(struct fifo_queue * fq)
{
	if((*fq).head == (*fq).tail)
		return true;
	else
		return false;
}
