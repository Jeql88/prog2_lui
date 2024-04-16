#include <stdlib.h>
#include <stdio.h>

typedef struct node{
    int data;
    struct node *next;
} NodeType, *NodePtr;

void display(NodePtr list);
void insertFront(NodePtr *list, int item);
void insertRear(NodePtr *list, int item);
void insertIndex(NodePtr *list, int item, int index);
void insertSorted(NodePtr *list, int item);
void main(){
    NodePtr head = NULL;
    
    insertFront(&head,1);
    display(head);
    insertRear(&head,6);
    display(head);
    insertRear(&head,7);
    display(head);
    insertRear(&head,8);
    display(head);
    insertRear(&head,9);
    display(head);
    insertIndex(&head,2,1);
    insertIndex(&head,3,2);
    insertIndex(&head,4,3);
    insertSorted(&head,5);
    display(head);
    
}

void insertSorted(NodePtr *list, int item){
    NodePtr temp = malloc(sizeof(NodeType));
    temp->data = item;
    for (; (*list)!= NULL && (*list)->data < item; list = &(*list)->next){}
    if (temp!=NULL){
        temp->next = (*list);
    } else{
        temp->next = NULL;
    }
    *list = temp;
}
void insertIndex(NodePtr *list, int item, int index){
    NodePtr temp = malloc(sizeof(NodeType));
    temp->data = item;
    for (int i = 0; (*list)!= NULL && i < index; list = &(*list)->next, ++i){
    }
    if (temp!=NULL){
        temp->next = (*list);
    } else{
        temp->next = NULL;
    }
    *list = temp;
}
void insertRear(NodePtr *list, int item){
    NodePtr temp;
    temp = malloc(sizeof(NodeType));
    temp->data = item;
    temp->next = NULL;
    for (; (*list) != NULL; list = &(*list)->next){}
    *list = temp;
}
void insertFront(NodePtr *list, int item){
    NodePtr temp = malloc(sizeof(NodeType));
    if (temp!=NULL){
        temp->data = item;
        temp->next = *list;
        *list = temp;
    }    
}
void display(NodePtr list){
    printf("\n");
    for (;list != NULL; list = list->next){
        printf("%d ",list->data);
    }
}