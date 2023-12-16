/* 
ARRAY IMPLEMENTATION OF QUEUE
*/



#include <stdio.h>

#define QUEUE_SIZE 4

typedef struct Queue{
    int arr[QUEUE_SIZE];
    int front;
    int back;
}Queue;


void initQueue(Queue *q){
    q->front = 0;
    q->back = -1;
}

void enqueue(Queue *q, int value){
    // check for overflow
    if (q->back + 1 < QUEUE_SIZE){
        // increase queue back
        q->back++;
        // add new value at top
        q->arr[q->back] = value;
        printf("Enqueued %d\n", value);
    }
    else {
        printf("Queue overflow: Cant enqueue %d\n", value);
    }
}

int dequeue(Queue *q){
    // check for underflow
    if (q->front > -1 && q->front <= q->back){
        // get value at top of Queue
        int value = q->arr[q->front];

        // increase queue front
        q->front++;
        printf("Removed %d\n", value);

        return value;
    }
    else{
        printf("Queue underflow: Empty\n");
        return(-1);
    }
}

// displays the content of Queue
void QueueDump(Queue *q){
    printf("| ");
    for (int i=q->front; i<=q->back; i++){
        if (i > -1){
            printf("%d | ", q->arr[i]);
        }
    }
    printf("\n");
}


/*
if you look carefully, this queue doesnt reuse the space of the dequeued elements,ie,
as the front advances forward, the space before it remains unused even though more elements can be added

Can you try and implement a queue which does reuse the space? This is called a circular queue!

*/
int main(){
    Queue q;
    initQueue(&q);

    enqueue(&q, 1);
    QueueDump(&q);
    enqueue(&q, 2);
    QueueDump(&q);
    enqueue(&q, 3);
    QueueDump(&q);
    dequeue(&q);
    QueueDump(&q);
    enqueue(&q, 4);
    QueueDump(&q);
    dequeue(&q);
    QueueDump(&q);

    // should be able to add this since there are only 2 elements in the queue of size 4
    enqueue(&q,5);
    QueueDump(&q);

    return 0;
}
