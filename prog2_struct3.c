#include <stdio.h>
#include <string.h>
#define MAX 10

typedef char String[20];

typedef struct {
    int elems[MAX];
    int count;
} ArrayList; 

//void insertRear(int arr[], int *count, int item);
void insertRear(ArrayList *list, int item);
void insertFront(ArrayList *list, int item);
void insertAt(ArrayList *list, int item, int ndx);
void display(ArrayList list);
void removeFront(ArrayList *list);
void insertSorted(ArrayList *list, int item);
void removeFirst(ArrayList *list, int item);
void removeAllOccurence(ArrayList *list, int item);
void removeRear(ArrayList *list);

void main() {
    String menu[5] = {"Add Front", "Delete Front", "Add Rear", "Delete Rear", "EXIT"};
    ArrayList myList;
    int choice, value;
    myList.count = 0;
    insertFront(&myList, 5);
    insertFront(&myList, 4);
    insertFront(&myList, 3);
    insertFront(&myList, 1);
    display(myList);
    insertSorted(&myList,2);
    insertSorted(&myList,2);
    insertSorted(&myList,2);
    insertSorted(&myList,2);
    display(myList);
    //removeFirst(&myList,3);
    removeAllOccurence(&myList,2);
    display(myList);


    // do {
    //     for(int i = 0; i < 5; ++i) {
    //         printf("[%2d]  %s\n", i+1, menu[i]);
    //     }
    //     printf("enter choice: ");
    //     scanf("%d", &choice);

    //     switch(choice) {
    //         case 1:
    //             printf("Enter item to be added: ");
    //             scanf("%d", &value);
    //             insertFront(&myList, value);
    //             display(myList);
    //             break;
    //         case 2:
    //             removeFront(&myList);
    //             display(myList);
    //             break;
    //         case 3:
    //             printf("Enter item to be added: ");
    //             scanf("%d",&value);
    //             insertRear(&myList,value);
    //             display(myList);
    //             break;
    //         case 4:
    //             removeRear(&myList);
    //             display(myList);
    //             break;
    //         case 5:
    //             printf("Thank you.");
    //             break;
    //         deafult:
    //             printf("Invalid input!!!");
    //     }
    //     printf("\n");
    // } while(choice != 5);

    
}

// void insertRear(int arr[], int *count, int item) {
//     if(*count < MAX) {
//         arr[(*count)++] = item;
//     }
// }
void removeFront(ArrayList *list){
    if (list->count > 0){
        memmove(list->elems,list->elems+1,4*(list->count--));
    }
}
void insertRear(ArrayList *list, int item) {
    if(list->count < MAX) {
        list->elems[(list->count)++] = item;
    }
    // insertAt(list, item, list->count);
}

void insertFront(ArrayList *list, int item) {
    insertAt(list, item, 0);
}

void insertAt(ArrayList *list, int item, int ndx) {
    if(list->count < MAX) {
        for(int i = list->count; i > ndx; --i) {
            list->elems[i] = list->elems[i-1];
        }
        list->elems[ndx] = item;
        (list->count)++;
    }
}

void removeRear(ArrayList *list) {
    if(list->count > 0) {
        (list->count)--;
    }
}

void display(ArrayList list) {
    printf("{");
    for(int i = 0; i < list.count; ++i) {
        printf("%d", list.elems[i]);
        if(i < list.count - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}

void insertSorted(ArrayList *list, int item){
    int i;
    if (list->count < MAX){
      for (i = list->count; item < list->elems[i-1]; --i){
            list->elems[i] = list->elems[i-1];
        }  
        list->elems[i] = item;
        list->count++;
    }   
}
void removeFirst(ArrayList *list, int item){
    int i;
    for (i = 0; i < list->count; ++i){
        if (list->elems[i] == item){
            memmove(list->elems+i, list->elems+i+1,(list->count-i)*4);
            break;
        }
    }
    list->count--;
}
void removeAllOccurence(ArrayList *list, int item){
    int i;
    int k = 0;
    for (i = 0; i < list -> count; ++i){
        if (list->elems[i]!=item){
            list->elems[k++] = list->elems[i];
        } 
    }
    list->count-=k;
}