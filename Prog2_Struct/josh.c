#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef char String[10];

typedef struct{
    int hour;
    int minute;
} MyTime;

typedef struct{
    char type;
    String plateNum;
    String color;
    String model;
} Vehicle;

typedef struct{
    Vehicle vehicle;
    MyTime timeIn;
    MyTime timeOut;
} ParkingInfo;

typedef struct{
    ParkingInfo *slot;
    int count;
    int max;
} ParkingArea, ParkingHistory;

void InitParkingArea(ParkingArea* parking, int total_parking);
ParkingInfo createParkingInfo(Vehicle vehicle, MyTime timeIn, MyTime timeOut);
Vehicle createVehicle(char type, String plateNum, String color, String model);
MyTime createTime(int hour, int minute);
void displayParkingArea(ParkingArea to_display);
bool addParkIn(ParkingArea* pa, Vehicle c, MyTime in, int loc);
bool addParkOut(ParkingArea* pa, MyTime out, String plateNum);
ParkingHistory createParkingHistory(int max);
bool checkOutVehicle(ParkingArea *pa, ParkingHistory *ph, String plateNum);
void printParkingReceipt(ParkingInfo pi);

void main(){
    ParkingArea parking_slots;
    InitParkingArea(&parking_slots, 10);
    displayParkingArea(parking_slots);
    ParkingHistory parking_receipt;
    parking_receipt = createParkingHistory(10);
    int to_add;
    printf("\n\nHow many vehicles to checkin: ");
    scanf("%d",&to_add);
    char type;
    String plateNum,color,model;
    int hour, minute, loc;
    for (int i = 0; i < to_add; ++i){
        while (getchar()!='\n');
        printf("Vehicle Type: ");
        scanf("%c",&type);
        while (getchar()!='\n');
        printf("plateNum: ");
        scanf("%s",&plateNum);
        while (getchar()!='\n');
        printf("color: ");
        scanf("%s",&color);
        while (getchar()!='\n');
        printf("model: ");
        scanf("%s",&model);
        while (getchar()!='\n');

        printf("hour in: ");
        scanf("%d",&hour);
        while (getchar()!='\n');
        printf("minute in: ");
        scanf("%d",&minute);
        while (getchar()!='\n');

        printf("location: ");
        scanf("%d",&loc);
        addParkIn(&parking_slots, createVehicle(type,plateNum,color,model), createTime(hour,minute), loc);

        displayParkingArea(parking_slots);
    }
    int will_add = 1;
    while (getchar()!='\n');
    while (will_add != 0){
        printf("\nDo you want to checkout? 0 - no: ");
        scanf("%d",&will_add);
        printf("Plate number to checkout: ");
        scanf("%s",&plateNum);
        while (getchar()!='\n');
        printf("Checkout hour: ");
        scanf("%d",&hour);
        while (getchar()!='\n');
        printf("Checkout minute: ");
        scanf("%d",&minute);
        while (getchar()!='\n');
        
        if (addParkOut(&parking_slots,createTime(hour,minute),plateNum) == 0){
            printf("\nError\n");
        } else{
            printf("\nSuccessful\n");
            
            checkOutVehicle(&parking_slots, &parking_receipt, plateNum);
            
        }
        displayParkingArea(parking_slots);
    }
}

bool checkOutVehicle(ParkingArea *pa, ParkingHistory *ph, String plateNum){
    
    for (int i = 0; i < pa->max; ++i){
        if (strcmp(pa->slot[i].vehicle.plateNum,plateNum)==0){
            printParkingReceipt(pa->slot[i]);
            ph->slot[ph->count++] = pa->slot[i];
            pa->slot[i] = createParkingInfo(createVehicle(' ',"","",""),createTime(0,0),createTime(0,0));
            return 1;
        }
    }
    return 0;
    
}
void InitParkingArea(ParkingArea* parking, int total_parking){
    parking->slot = malloc(sizeof(ParkingInfo)*total_parking);
    parking->count = 0;
    parking->max = total_parking;
    for (int i = 0; i < total_parking; ++i){
        parking->slot[i] = createParkingInfo(createVehicle(' ',"","",""),createTime(0,0),createTime(0,0));
    }
}

ParkingInfo createParkingInfo(Vehicle vehicle, MyTime timeIn, MyTime timeOut){
    ParkingInfo to_return;
    to_return.vehicle = vehicle;
    to_return.timeIn = timeIn;
    to_return.timeOut = timeOut;
    return to_return;
}

Vehicle createVehicle(char type, String plateNum, String color, String model){
    Vehicle to_return;
    to_return.type = type;
    strcpy(to_return.plateNum,plateNum);
    strcpy(to_return.color,color);
    strcpy(to_return.model,model);
    return to_return;
}

MyTime createTime(int hour, int minute){
    MyTime to_return;
    to_return.hour = hour;
    to_return.minute = minute;
    return to_return;
}

bool addParkIn(ParkingArea* pa, Vehicle c, MyTime in, int loc){
    if (pa->slot[loc].timeIn.minute == 0 && pa->slot[loc].timeIn.hour == 0){
        pa->slot[loc].vehicle = c;
        pa->slot[loc].timeIn = in;
        pa->count++;
        return 1;
    } else{
        return 0;
    }
}

bool addParkOut(ParkingArea* pa, MyTime out, String plateNum){
//consider timeout shud come out after timein
    for (int i = 0; i < pa->max; ++i){
        if (strcmp(pa->slot[i].vehicle.plateNum,plateNum) == 0){
            pa->slot[i].timeOut = out;
            pa->count--;
            return 1;
        }
    }
    return 0;
}

ParkingHistory createParkingHistory(int max){
    ParkingHistory to_return;
    to_return.slot = malloc(sizeof(ParkingInfo)*max);
    to_return.max = max;
    to_return.count = 0;
    return to_return;
}
void displayParkingArea(ParkingArea to_display){
    printf("NO SLOT | STATUS                         | TIME IN       | TIME OUT");
    for (int i = 0; i < to_display.max; ++i){
        printf("\n%8d",i);
        if (to_display.slot[i].timeIn.minute == 0 && to_display.slot[i].timeIn.hour == 0 ){
            printf("| available");
        } else{
            printf(" %s - %s - %-s",to_display.slot[i].vehicle.plateNum, to_display.slot[i].vehicle.color, to_display.slot[i].vehicle.model);
            printf("%12d:%2d",to_display.slot[i].timeIn.hour, to_display.slot[i].timeIn.minute);
            if (to_display.slot[i].timeOut.hour == 0 && to_display.slot[i].timeOut.minute == 0){
                printf("          --:--");
            } else{
                printf("          %2d:%2d",to_display.slot[i].timeOut.hour,to_display.slot[i].timeOut.minute);
            }
        }
    }
}

void printParkingReceipt(ParkingInfo pi){
   
    printf("\nTYPE : %c\n",pi.vehicle.type);
    printf("VEHICLE : %s - %s - %s\n",pi.vehicle.plateNum, pi.vehicle.model, pi.vehicle.color);
    printf("TIME IN : %d:%d\n", pi.timeIn.hour, pi.timeIn.minute);
    printf("TIME OUT: %d:%d\n",  pi.timeOut.hour,  pi.timeOut.hour);
    
}
