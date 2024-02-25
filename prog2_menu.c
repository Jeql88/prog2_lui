#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX 10

typedef char String[20];

typedef struct{
    float price;
    bool available;
    String name;
} dish;

typedef struct{
    dish entree[3];
    dish sides[3];
    dish desserts[3];
} menu;

dish createDish(float price, String name, bool available);
menu loadMenu();
void displayEntree(menu main_menu, int size);
void displaySides(menu main_menu, int size);
void displayDesserts(menu main_menu, int size);
void addOrder(dish order_dish, int *total, dish all_orders[]);
void displayOrder(dish all_orders[], int total);
float sumAll(dish all_orders[], int total);
void removeDish(dish all_orders[], int *total, int index);

void main(){
    int entree_count = 3, sides_count = 3, desserts_count = 3;
    int orders = 0;
    dish customer_orders[MAX];
    menu main_menu = loadMenu();
    printf("Welcome to Jeql8's Resto!\n");
    int input = -1;
    int input2 = -1;
    int input3 = -1;
    float total = 0;
    do{
        printf("1 - Entrees\n");
        printf("2 - Sides\n");
        printf("3 - Desserts\n");
        printf("4 - Remove Order\n");
        printf("5 - Finish\n");
        printf("6 - Exit\n");
        scanf("%d",&input);
        switch(input){
            case 1:
                displayEntree(main_menu,entree_count);
                scanf("%d",&input2);
                addOrder(main_menu.entree[input2-1], &orders, customer_orders);
                displayOrder(customer_orders,orders);
                break;
            case 2:
                displaySides(main_menu,sides_count);
                scanf("%d",&input2);
                addOrder(main_menu.sides[input2-1], &orders, customer_orders);
                displayOrder(customer_orders,orders);
                break;
            case 3:
                displayDesserts(main_menu, sides_count);
                scanf("%d",&input2);
                addOrder(main_menu.desserts[input2-1], &orders, customer_orders);
                displayOrder(customer_orders,orders);
                break;
            case 4:
                displayOrder(customer_orders, orders);
                printf("Enter the number of the order you want to remove.\n");
                do{
                    scanf("%d",&input3);
                } while(input3 < 1 && input3 > total);
                removeDish(customer_orders,&orders,input3-1);
                displayOrder(customer_orders, orders);
                break;
            case 5:
                printf("Your total would be %.2f, thank you for ordering from us!",sumAll(customer_orders,orders));
                break;
            case 6:
                break;
            default:
                printf("Incorrect Input, please try again.\n");
        }
    } while (input != 6 && input != 5);
    

}

dish createDish(float price, String name, bool available){
    dish returnDish;
    returnDish.price = price;
    strcpy(returnDish.name,name);
    returnDish.available = available;
    return returnDish;
}
menu loadMenu(){
    menu main_menu;
    
    main_menu.entree[0] = createDish(285, "Beef Salpicao", true);
    main_menu.entree[1] = createDish(245, "Chicken Parmigiana", true);
    main_menu.entree[2] = createDish(255, "Fried Chicken", true);
    
    main_menu.sides[0] = createDish(55, "French Fries", true);
    main_menu.sides[1] = createDish(95, "Mango Salad", false);
    main_menu.sides[2] = createDish(85, "Mozarella Sticks", true);

    main_menu.desserts[0] = createDish(60, "Vanilla Ice Cream", false);
    main_menu.desserts[1] = createDish(50, "Mango Sago", true);
    main_menu.desserts[2] = createDish(55, "Apple Crumble", true);
    
    return main_menu;
}
void displayEntree(menu main_menu, int size){
    int i;
    for (i = 0; i < size; ++i){
        printf("[%d] %s - %.2f", i+1, main_menu.entree[i].name, main_menu.entree[i].price);
        if (main_menu.entree[i].available == true){
            printf(" -> AVAILABLE");
        } else{
            printf(" -> NOT AVAILABLE");
        }
        printf("\n");
    }
    printf("[%d] Back\n",i+1);
}
void displaySides(menu main_menu, int size){
    int i;
    for (i = 0; i < size; ++i){
        printf("[%d] %s - %.2f", i+1,main_menu.sides[i].name, main_menu.sides[i].price);
        if (main_menu.sides[i].available == true){
            printf(" -> AVAILABLE");
        } else{
            printf(" -> NOT AVAILABLE");
        }
        printf("\n");
    }
    printf("[%d] Back\n",i+1);
}
void displayDesserts(menu main_menu, int size){
    int i;
    for (i = 0; i < size; ++i){
        printf("[%d] %s - %.2f",i+1, main_menu.desserts[i].name, main_menu.desserts[i].price);
        if (main_menu.desserts[i].available == true){
            printf(" -> AVAILABLE");
        } else{
            printf(" -> NOT AVAILABLE");
        }
        printf("\n");
    }
    printf("[%d] Back\n",i+1);
}
void addOrder(dish order_dish, int *total, dish all_orders[]){
    if (*total < MAX && order_dish.available == true){
        all_orders[(*total)++] = order_dish;
    } else if (order_dish.available == false){
        printf("Sorry, this dish is unavailable.\n");
    } else{
        printf("You have reached the maximum amount of orders.");
    }
}
void displayOrder(dish all_orders[], int total){
    printf("\nCurrent Orders:\n");
    for (int i = 0; i < total; ++i){
        printf("[%d] %s - %.2f\n",i+1,all_orders[i].name,all_orders[i].price);
    }
    printf("Total = %.2f\n\n", sumAll(all_orders, total));
}
float sumAll(dish all_orders[], int total){
    float sum = 0;
    for (int i = 0; i < total; ++i){
        sum+=all_orders[i].price;
    }
    return sum;
}
void removeDish(dish all_orders[], int *total, int index){
    int i;
    for (i = *total-1; i > index; --i){
        all_orders[i-1] = all_orders[i];
    }
    (*total)--;
}