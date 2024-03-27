/* Instructions:
	The University of San Carlos has begun rolling out its newest locker technology: GraviLockers.
	These lockers are capable of fitting any amount of items, for as long as the total weight of all items
	does not exceed the weight limit of 5 KG. However, during shipping, the lockers' disk drives were damaged,
	and the firmware that made them work was lost. Luckily, the documentation for the structures remained intact.
	
	As students of DCIS, USC needs your help. Write the codes for the functions to make the lockers work again.
	Use the structures defined below.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLOCKERS 10
#define WEIGHTLIMIT 5

typedef struct{
	char studID[9];		
	char studName[65];  
	char course[5];		
}Student;

typedef struct{
	char itemName[33];	
	float weight;		/* Weight of the item to be stored */	
}ItemDets;

// typedef struct ItemNode{
// 	ItemDets item;
// 	struct ItemNode* nextItem;
// }ItemNode, *ItemList;

typedef struct ItemNode {
	ItemDets *items;
	int count;
	int max;
}ItemNode, *ItemList;

typedef struct{
	Student owner;			/* Details of the student who owns the locker */
	ItemList IL;			/* Array list representation of all the items inside a certain locker */
	int lockerStat; 	 	/* 0 if locker is Vacant, 1 if occupied */
	float totWeight;		/* Total weight of all items in the locker */
}Locker;

/* Function depositItem(): This function will receive as parameter a Locker, a student ID, and an item to be
stored. The function will insert the item into the Locker's ItemList, which is sorted by weight. Heavier
items are stored at the end of the locker's ItemList. Before insertion, please make sure that the student ID
passed is the same as the student ID of the locker's owner. Also, make sure that the weight of all items,
including the new item to store, does not exceed the weight limit. */

void depositItem(Locker* L, char studID[], ItemDets newItem)
{
    int i;
    if (strcmp(L->owner.studID,studID)!=0){
        printf("Student ID does not match locker's owner");
    } else if(L->totWeight + newItem.weight > WEIGHTLIMIT){
        printf("Exceeds the locker's weight limit");
    } else{
        for (i = L->IL->count; i > 0 && newItem.weight < L->IL->items[i-1].weight; --i){
            L->IL->items[i] = L->IL->items[i-1];
        }
        L->IL->count++;
        L->IL->items[i] = newItem;
    }
}

/* Function getHeavyItems(): This function will receive as parameter a Locker and a weight threshold/limit.
The function will go through all the items in the passed Locker's ItemList. If any item EXCEEDS the passed
threshold/limit, store that item into a new ItemList using insertFirst, and delete it from the locker's 
ItemList. Return the ItemList of deleted items to the calling function. */

void deleteIndex(ItemList list, int index){
    for (int i = index; (i+1) < list->count; ++i){
        list->items[i] = list->items[i+1];
        
    }
    list->count--;
}
ItemList getHeavyItems(Locker* L, float limit)
{ 
    int k = 0, original_count = L->IL->count;
    ItemList tempList = malloc(sizeof(ItemList)*1);
    tempList->items = malloc(sizeof(ItemDets)*MAXLOCKERS);
    for (int i = 0; i < original_count; ++i){
        if (L->IL->items[i].weight >= limit){
            tempList->items[k++] = L->IL->items[i];
            deleteIndex((L->IL),i);
        }
    }
    tempList->count = k;
    tempList->max = MAXLOCKERS;
    return tempList;
}

void displayItemList(ItemList L)
{
    for (int i = 0; i < L->count; ++i){
        printf("%s - %.2f\n",L->items[i].itemName,L->items[i].weight);
    }
}

int main(void)
{
	ItemDets item1 = {"Prog 1 Book", 0.35};
	ItemDets item2 = {"Shoes", 0.87};
	ItemDets item3 = {"Laptop", 2.35};
	ItemDets item4 = {"Keyboard", 1.17};
	ItemNode tempNode = {malloc(sizeof(ItemDets)*15),0,MAXLOCKERS};
	Locker myLocker = {{"14101941", "Cris Militante", "BSCS"}, &tempNode, 1, 0};
    
	ItemList heavyItems;
	
	depositItem(&myLocker, "14101941", item4);
	depositItem(&myLocker, "14101941", item2);
	depositItem(&myLocker, "14101941", item3);
	depositItem(&myLocker, "14101941", item1);
	//displayItemList(myLocker.IL);
	
	heavyItems = getHeavyItems(&myLocker, 1.00);
    printf("myLocker Items:\n\n");
	displayItemList(myLocker.IL);
    printf("\nHeavy Items:\n\n");
	displayItemList(heavyItems);
	return 0;
}
