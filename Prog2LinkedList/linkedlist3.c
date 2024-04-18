#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* next;
} Node, *NodePtr;


void insertAt(NodePtr *list, int a, int index);
void display(NodePtr list);
void deleteAt(NodePtr *list, int index);
void insertFirst(NodePtr *list, int a);
void deleteFirst(NodePtr *list);
void deleteLast(NodePtr *list);

void main(){
    NodePtr head;
    insertAt(&head, 5, 0);
    insertAt(&head, 6, 0);
    insertAt(&head, 7, 0);
    insertAt(&head, 8, 0);
    insertAt(&head, 9, 0);
    insertAt(&head, 1, 0);
    display(head);
    printf("\nInsert First\n");
    insertFirst(&head,5);
    display(head);
    printf("\nDelete At\n");
    deleteAt(&head, 0);
    display(head);
    printf("\nDelete First\n");
    deleteFirst(&head);
    
    display(head);
    printf("\nDelete Last\n");
    deleteLast(&head);
    display(head);
    printf("\n");
}
void display(NodePtr list){
    for (; list != NULL; list = list->next){
        printf("%d ",list->value);
    }
}
void insertAt(NodePtr *list, int a, int index){
    NodePtr temp = malloc(sizeof(Node));
    for (int i = 0; i < index && (*list)!= NULL; ++i){
        list = &(*list)->next;
    }
    temp->value = a;
    temp->next = (*list);
    (*list) = temp;
}

void insertFirst(NodePtr *list, int a){
    NodePtr temp = malloc(sizeof(Node));
    temp->value = a;
    temp->next = (*list);
    (*list) = temp;
}

void deleteAt(NodePtr *list, int index){
    NodePtr temp;
    for (int i = 0; i < index && (*list)!=NULL;++i, list = &(*list)->next){}
    // printf("%d",(*list)->value);
    if ((*list) != NULL){
        temp = (*list);
        (*list) = (*list)->next;
        free(temp);
    }
    
}

void deleteLast(NodePtr *list){
    NodePtr temp;
    for (;  (*list)->next!=NULL; list = &(*list)->next){}
    // printf("%d",(*list)->value);
    
    temp = (*list);
    (*list) = (*list)->next;
    free(temp);
    
}

void deleteFirst(NodePtr *list){
    NodePtr temp;
    temp = (*list);
    (*list) = (*list)->next;
    free(temp);
}