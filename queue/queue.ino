#define QUEUE_EMPTY 0

typedef struct node{
    byte value;
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

bool enqueue(queue *q, byte value)
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

byte dequeue(queue *q)
{
    if(q->head == NULL) return QUEUE_EMPTY;

    node *tmp = q->head;
    byte result = tmp->value;
    q->head = q->head->next;

    if(q->head == NULL){
        q->tail = NULL;
    }

    free(tmp);
    return result;
}
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
