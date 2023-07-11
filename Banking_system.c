#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    char transaction[MAX_SIZE][10];
    int front;
    int rear;
} Queue;

void init(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int is_empty(Queue *q) {
    return q->front == -1;
}

int is_full(Queue *q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

void enqueue(Queue *q, int value) {
    if (is_full(q)) {
        printf("Queue is full!\n");
        return;
    }
    if (is_empty(q)) {
        q->front = 0;
        q->rear = 0;
    }
    else
    {
        q->rear = (q->rear + 1) % MAX_SIZE;
    }
    q->data[q->rear] = value;
    if(value > 0)
    strcpy(q->transaction[q->rear] , "Deposited");
    else
    strcpy(q->transaction[q->rear],  "Withdrawed");
}

void dequeue(Queue *q) 
{
    if (is_empty(q)) // 1: True || 0:False
    {
        printf("No Transaction In Record!\n"); 
    }

    if (q->front == q->rear) 
    {
        q->front = -1;
        q->rear = -1;
    } else
    {
        q->front = (q->front + 1) % MAX_SIZE;
    }
    
}

void display(Queue *q) {
    time_t t;
    time(&t);

    if (is_empty(q)) {
        printf("No Transaction In Record!\n");
        return;
    }
    printf("\nTransaction log: \n");
    int i = q->front;
    while (i != q->rear) {
        printf("%d -- %s -- %s\n", q->data[i], q->transaction[i], ctime(&t));
        i = (i + 1) % MAX_SIZE;
    }
    printf("%d -- %s -- %s\n", q->data[q->rear], q->transaction[i], ctime(&t));
   
}

int main() {
    Queue q;
    init(&q);
    int choice, amount, balance = 10000, a;
    do {
        printf("\n1. Deposit");
        printf("\n2. Withdraw");
        printf("\n3. Balance Enquiry");
        printf("\n4. Transaction History");
        printf("\n5. Delete Oldest Transaction History");
        printf("\n6. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) 
        {

            case 1: printf("Enter amount to deposit: ");
                    scanf("%d", &amount);
                    enqueue(&q, amount);
                    balance += amount;
                    printf("Deposited %d. Current balance is %d.\n", amount, balance);
                    break;

            case 2: printf("Enter amount to withdraw: ");
                    scanf("%d", &amount);
                    if (amount <= balance) {
                        enqueue(&q, -amount);
                        balance -= amount;
                        printf("Withdrawn %d. Current balance is %d.\n", amount, balance);
                    } else {
                        printf("Insufficient balance!\n");
                    }
                    break;

            case 3:  printf("Current balance is %d.\n", balance);  break;

            case 4:  break;

            case 5:  printf("Deleting the oldest transaction!\n");
                     dequeue(&q);
                     break;
                   
            case 6:  printf("Visit Again...\n");
                     break;

            default: printf("Invalid choice!\n");
        }
        display(&q);
    } while (choice != 6);
    return 0;
}