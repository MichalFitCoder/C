#include <stdio.h>
#include <stdlib.h>

struct node {
    float salary;
}

struct list{
    node elements[100];
    
    int front;
    int end;
    int size;
};

void add(struct list* queue, float data) {
    queue->rear = (queue->end + 1);
    queue->elements[queue->end]->salary = data;
    queue->size++;
}

void del(struct list* queue){
    //float data = queue->elements[queue->front].salary;
    queue->front = (queue->front + 1);
    queue->size--;
}

void display(struct list* queue) {
    
    printf("Queue elements: ");
    for (int i = 0; i < queue->size; i++) {
        int index = (queue->front + i)
        printf("%.2f ", queue->elements[index].salary);
    }
    printf("\n");
}

int main(){
    
    struct list* list;
    list->front = 0;
    list->end = -1;
    list->size = 0;

    add(list,234);


    return 0;
}
