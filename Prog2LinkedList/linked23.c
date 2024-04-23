#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
} Node, *NodePtr;

void addLast(NodePtr *head, int num);
void display(NodePtr head);
void swap(NodePtr *a, NodePtr *b);
void removeNthFromEnd(NodePtr *head, int n);

void main(){
    Node *head = NULL;
    addLast(&head,2);
    
    removeNthFromEnd(&head,2);
    display(head);
    
}
void display(NodePtr head){
    while (head != NULL){
        printf("%d ", head->data);
        head = head->next;
    }
}
// void addLast(NodePtr *head, int num){
//     NodePtr list = *head;
//     NodePtr temp = malloc(sizeof(Node));
//     if (temp == NULL){
//         printf("malloc failed");
//         return;
//     }
//     temp->data = num;
//     temp->next = NULL;
//     if (list == NULL){
//         *head = temp;
//         return;
//     }
//     while (list->next != NULL){
//         list = list->next;
//     }
//     list->next = temp;
// }
void addLast(NodePtr *head, int num){
   
    NodePtr temp = malloc(sizeof(Node));
    if (temp == NULL){
        printf("malloc failed");
        return;
    }
    temp->data = num;
    temp->next = NULL;
    
    while (*head != NULL){
        head = &(*head)->next;
    }
    *head = temp;
}
void removeNthFromEnd(NodePtr *head, int n){
    NodePtr *temp = head;
    int count = 0;
    while (*temp != NULL){
        temp = &(*temp)->next;
        count++;
    }
    while (count-n > 1){
        head = &(*head)->next;
        count--; 
    }
    NodePtr temp2 = (*head)->next;
    (*head)->next = (*head)->next->next;
    free(temp2);
    // *head = (*head)->next->next;
    
}

