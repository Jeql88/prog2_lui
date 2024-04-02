#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

typedef char String[20];

typedef struct{
    int day;
    int month;
    int year;
} Mydate;

typedef struct{
    int id;
    String name;
    Mydate exp;
    float price;
} Product;

typedef struct{
    Product prods[MAX];
    int count;
} ProductListStatic;

typedef struct{
    Product *prods;
    int count;
    int max;
} ProductListDynamic;

int dateDiff(Mydate a, Mydate b);
void display(ProductListDynamic list);
Product createProduct(int id, String name, Mydate exp, float price);
Mydate returnDate(int day, int month, int year);
void addProduct(ProductListDynamic *list, Product to_add);
void addSorted(ProductListDynamic *list, Product to_add);
ProductListDynamic allExpired(ProductListDynamic *list, Mydate exp_date);
void deleteIndex(ProductListDynamic *list, int index);

void main(){
    ProductListDynamic prod_list;
    prod_list.prods = malloc(sizeof(Product)*10);
    prod_list.count = 0;
    prod_list.max = MAX;
    addProduct(&prod_list,createProduct(1111,"Jansen",returnDate(26,6,2003),500));
    addProduct(&prod_list,createProduct(2222,"Jio",returnDate(28,10,2003),1000));
    addSorted(&prod_list,createProduct(3333,"Ram",returnDate(28,6,2010),2000));
    addSorted(&prod_list,createProduct(3333,"Ram",returnDate(28,6,2001),2000));
    display(prod_list);
    printf("\nexpired\n\n");
    ProductListDynamic expired_list = allExpired(&prod_list, returnDate(1,5,2005));
    display(expired_list);
    printf("\nnon expired\n\n");
    display(prod_list);
}
void deleteIndex(ProductListDynamic *list, int index){
    int i;
    for (i = index; i < list->count-1; ++i){
        list->prods[i] = list->prods[i+1];
    }
    list->count--;
}
void addSorted(ProductListDynamic *list, Product to_add){
    int i;
    for (i = list->count; i > 0 && dateDiff(list->prods[i-1].exp,to_add.exp) < 0; --i){
        list->prods[i] = list->prods[i-1];
    }
    list->prods[i] = to_add;
    list->count++;
}
ProductListDynamic allExpired(ProductListDynamic *list, Mydate exp_date){
    int i;
    ProductListDynamic to_return;
    to_return.prods = malloc(sizeof(Product)*list->count);
    to_return.count = 0;
    to_return.max = MAX;
    int og_count = list->count;
    for (i = 0; i < og_count; ++i){
        if (dateDiff(list->prods[i].exp,exp_date) <= 0){
            addSorted(&to_return,list->prods[i]);
            deleteIndex(list,i);
        }
    }
    return to_return;
}

int dateDiff(Mydate a, Mydate b){
    if (a.year > b.year){
        return (a.year-b.year)*365;
    } else if (a.year < b.year){
        return (a.year-b.year)*365;
    } else{
        if (a.month > b.month){
            return (a.month-b.month)*30;
        } else if (a.month < b.month){
            return (a.month-b.month)*30;
        } else{
            if (a.day > b.day){
                return a.day-b.day;
            } else if (a.day < b.day){
                return a.day-b.day;
            } else{
                return 0;
            }
        }
    }
}
    
void display(ProductListDynamic list){
    for (int i = 0; i < list.count; ++i){
        printf("%d %s expires at %d/%d/%d $%.2f\n",list.prods[i].id,list.prods[i].name,list.prods[i].exp.day,list.prods[i].exp.month,list.prods[i].exp.year,list.prods[i].price);
    }
}
Mydate returnDate(int day, int month, int year){
    Mydate to_return = {day,month,year};
    return to_return;
}
Product createProduct(int id, String name, Mydate exp, float price){
    Product to_return;
    to_return.id = id;
    strcpy(to_return.name, name);
    to_return.exp = exp;
    to_return.price = price;
    return to_return;
}
void addProduct(ProductListDynamic *list, Product to_add){
    list->prods[list->count++] = to_add;
}