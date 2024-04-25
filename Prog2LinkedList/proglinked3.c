#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
} NodeType, *NodePtr;

void insertFront(NodePtr *list, int data);
void display(NodePtr list);
void deleteRear(NodePtr *list);
void deleteAllOccurence(NodePtr *list, int data);
NodePtr allFactors(NodePtr list, int data);
NodePtr removeAllFactors(NodePtr *list, int data);

void main(){
    NodePtr head = NULL;
    int nums[8] = {5,4,3,2,1,7,5,5};
    for (int i = 0; i < 8; ++i){
        insertFront(&head,nums[i]);
    }
    // deleteRear(&head);
    // display(head);
    // // deleteAllOccurence(&head,7);
    // display(head);
    // NodePtr temp = allFactors(head,5);
    NodePtr temp = removeAllFactors(&head,5);
    display(temp);
    display(head);
}
void insertFront(NodePtr *list, int data){
    NodePtr temp = malloc(sizeof(NodeType));
    temp->data = data;
    temp->next = (*list);
    *list = temp;
}
void deleteAllOccurence(NodePtr *list, int data){
    while ((*list)!= NULL){
        if ((*list)->data == data){
            NodePtr temp = *list;
            (*list) = temp->next;
            free(temp);
        } else{
            list = &(*list)->next;
        }
    }
}
NodePtr removeAllFactors(NodePtr *list, int data){
    NodePtr newer = NULL;
    
    while ((*list) != NULL){
        if ((*list)->data % data == 0){
            // insertFront(&new,(*list)->data);
            NodePtr temp = (*list);
            (*list) = temp->next;
            temp->next = newer;
            newer = temp;
        } else{
            list = &(*list)->next;
        }
    }
    return newer;
}

NodePtr allFactors(NodePtr list, int data){
    NodePtr new = NULL;
    NodePtr temp;
    while (list != NULL){
        if (list->data % data == 0){
            temp = malloc(sizeof(NodeType));
            temp->data = list->data;
            temp->next = new;
            new = temp;
            // insertFront(&new,list->data);
        } 
        list = list->next;
    }
    return new;
}

void deleteRear(NodePtr *list){
    if (*list != NULL){
        for (; (*list)->next!=NULL; list = &(*list)->next){}
        NodePtr temp = *list;
        (*list) = NULL;
        free(temp);
    }
}
void display(NodePtr list){
    printf("\n{");
    for ( ; list != NULL; list = list->next){
        printf("%d",list->data);
        if (list->next != NULL){
            printf(",");
        }
    }
    printf("}");
}
