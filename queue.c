#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_EMPTY INT_MIN

typedef struct node{
    int value;
    struct node *next;
} node;

typedef struct {
    node *head;
    node *tail;
} queue;

void init_queue(queue *q){
    q->head = NULL;
    q->tail = NULL;
}

bool enqueue(queue *q, int value)
{
    node * newnode = malloc(sizeof(node));
    newnode->value = value;
    newnode->next = NULL;

    if(newnode == NULL) return false;

    if(q->tail !=NULL){
        q->tail->next = newnode;
    }
    q->tail = newnode;

    if(q->head == NULL){
        q->head = newnode;
    }
    return true;
}

int dequeue(queue *q)
{
    if(q->head == NULL) return QUEUE_EMPTY;

    node *tmp = q->head;
    int result = tmp->value;
    q->head = q->head->next;

    if(q->head == NULL){
        q->tail = NULL;
    }

    free(tmp);
    return result;
}

int main()
{
    queue s1;
    
    init_queue(&s1);

    enqueue(&s1, 0x7E);
    enqueue(&s1, 0x89);
    enqueue(&s1, 69);
    enqueue(&s1, 420);

    int num;
    while(1){
        printf("Enter 69 to deque");
        scanf("%d", &num);
        
        if(num == 69){
            int t;
            t = dequeue(&s1);
            printf("t = %d\n", t);
        } else if(num == 34){
            break;
        }
    }
    // int t;
    // while((t = dequeue(&s1)) != QUEUE_EMPTY ){
    //     printf("t = %d\n", t);
    // }
}