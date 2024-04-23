#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure representing a node in the queue
typedef struct {
    int data;
} Node;

// Structure representing the FIFO queue
typedef struct {
    Node elements[MAX_SIZE];
    int front;
    int rear;
    int size;
} Queue;

// Function to initialize the queue
void initialize(Queue* queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    return queue->size == 0;
}

// Function to check if the queue is full
int isFull(Queue* queue) {
    return queue->size == MAX_SIZE;
}

// Function to add an element to the rear of the queue
void enqueue(Queue* queue, int data) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->elements[queue->rear].data = data;
    queue->size++;
}

// Function to remove an element from the front of the queue
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }
    
    int data = queue->elements[queue->front].data;
    queue->front = (queue->front + 1) % MAX_SIZE;
    queue->size--;
    
    return data;
}

// Function to display the contents of the queue
void display(list* queue) {
    
    printf("Queue elements: ");
    for (i = 0; i < queue->size; i++) {
        int index = (queue->front + i) % MAX_SIZE;
        printf("%d ", queue->elements[index].data);
    }
    printf("\n");
}

int main() {
    Queue queue;
    initialize(&queue);
    
    int data, choice;
    
    while (1) {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the data to enqueue: ");
                scanf("%d", &data);
                enqueue(&queue, data);
                break;
                
            case 2:
                if (isEmpty(&queue)) {
                    printf("Queue is empty. Cannot dequeue.\n");
                } else {
                    int dequeuedData = dequeue(&queue);
                    printf("Dequeued element: %d\n", dequeuedData);
                }
                break;
                
            case 3:
                display(&queue);
                break;
                
            case 4:
                printf("Exiting program.\n");
                exit(0);
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}
