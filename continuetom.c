#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "cis1201.h"

customerList initCustomerList(){
	//initializes the customer list
	customerList CL = 
	{
	{{"111111","Customer 1",0.0},
	 {"222222","Customer 2",50.0},
	 {"333333","Customer 3",150.0},
	 {"444444","Customer 4",250.0},
	 {"555555","Customer 5",0.0},
	 {"666666","Customer 6",50.0},
	 {"777777","Customer 7",150.0},
	 {"888888","Customer 8",250.0},
	}
	,8};
	return CL;
}

productList initProductList(){
	//initializes the product list
	productList PL = 
	{
	{{"111111","Product 1",20.0,5},
	 {"222222","Product 2",50.0,5},
	 {"333333","Product 3",70.0,5},
	 {"444444","Product 4",100.0,5},
	 {"555555","Product 5",10.0,5},
	 {"666666","Product 6",40.0,5},
	 {"777777","Product 7",60.0,5},
	 {"888888","Product 8",150.0,5},
	}
	,8};
	return PL;
}

void displayProductList(productList PL){
	int x;
	int count = PL.count;
	system("cls");
	printf("\nNumber of products: %d\n",count);
	for(x=0;x<count;x++){
		printf("\n %s \t %s \t %7.2f \t Remaining: %d",PL.prod[x].ID,PL.prod[x].name,PL.prod[x].price,PL.prod[x].qtyRemaining);
	}
}

void displayCustomerList(customerList CL){
	int x;
	int count = CL.count;
	system("cls");
	printf("\nNumber of customers: %d\n",count);
	for(x=0;x<count;x++){
		printf("\n %s \t %s \t %7.2f",CL.cust[x].ID,CL.cust[x].name,CL.cust[x].balance);
	}
}

/* 5 POINTS */
boolean findCustomer(customerList CL, char ID[]){
	int i;
	//Returns TRUE is the customer record with the given ID is in the list and FALSE otherwise.
	for (i = 0; i < CL.count; ++i){
		if (strcmp(CL.cust[i].ID,ID) == 0){
			return 1;
		}
	}
	return 0;
}

/* 5 POINTS */
void addProduct(productList *PL, product P){
	int i;
	//Adds the given product record to the end of the product list only if it has not yet found in the list.
	//Otherwise, if the product record is already present, modify the record by adding the quantity found in the parameter
	//to the quantity recorded in the product list for the given item.
	for (i = 0; i < PL->count; ++i){
		if (strcmp(PL->prod[i].ID, P.ID) == 0){
			PL->prod[i].qtyRemaining+=P.qtyRemaining;
			break;
		}
	}
	if (i == PL->count){
		PL->prod[PL->count++] = P;
	}
}

/* 10 POINTS */
void addCustomer(customerList *CL, customer C){
	int i;
	//Inserts the given customer info into its proper sorted position in the customer list ONLY if
	//the customer info is not yet present in the list. Invoke function findCustomer() whenever necessary.
	if (findCustomer(*CL,C.ID) == 0){
		for (i = CL->count; i > 0 && atoi(CL->cust[i-1].ID) > atoi(C.ID) ; --i){
			CL->cust[i] = CL->cust[i-1];
		}
		CL->cust[i] = C;
		CL->count++;
	}
}

/* 10 POINTS */
void reloadBalance(customerList *CL, char ID[], float amount){
	//Adds the given balance into the given customer's record in the customer list.
	//In addition, this function shall output 4 lines of display:
	//(1) the customer name, 
	//(2) the customer's old balance, 
	//(3) the balance added,
	//(4) the customer's new balance.
	int i;
	for (i = 0; i < CL->count; ++i){
		if (strcmp(CL->cust[i].ID,ID) == 0){
			CL->cust[i].balance += amount;
			break;
		}
	}
	printf("\n1. Customer Name = %s\n",CL->cust[i].name);
	printf("2. Customer's Old Balance = %.2f\n",CL->cust[i].balance - amount);
	printf("3. Balance Added = %.2f\n",amount);
	printf("4. Customer's New Balance = %.2f",CL->cust[i].balance);
}

/* 10 POINTS */

void sortProductList(productList *PL){
	//Sorts the product list by increasing order of price.
	int i, k;
	float temp;
	product temp_product;
	for (i = 0; i < PL->count; ++i){
		temp = PL->prod[i].price;
		for (k = i; k < PL->count; ++k){
			if (PL->prod[k].price < temp){
				temp = PL->prod[k].price;
				product temp_product = PL->prod[k];
				PL->prod[k] = PL->prod[i];
				PL->prod[i] = temp_product;
			}
		}
	}
}

/* 30 POINTS */
order processOrder(customerList *CL, productList *PL, char custID[], char prodID[], int qty){
	//Create an order item that records the customer transacting, the product and its quantity being ordered.
	//**Process order only if both product ID and customer ID exist in the lists.
	//**If there's insufficient balance for the requested quantity, do not process the order at all. 
	//**Otherwise, supply whatever is available in stock.
	//Update the affected customer and product records accordingly by decreasing the balance and remaining quantity
	//of the customer and product.
	//Record the actual quantity supplied based on the available stock and the customer's balance.
	//Record the appropriate order status (SUCCESS/OUT_OF_BAL - insufficient balance/OUT_OF_STOCK - incomplete stock/ERROR - item not found)
	//Return the order item to the calling function.
}

/* 30 POINTS */
productList getItemsToRestock(productList *PL){
	//Transfers the product records with quantity of 0 to a new list which represents the items need to be restocked
	//Note: Items that are transferred must be deleted from the original product list.
	//Return the newly created list to the calling function.
}

