#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

typedef char String[20];
typedef struct{
    String fname;
    String lname;
} Name, *NamePtr, NameListArray[MAX];

Name createName(String fname, String lname);
void displayName(Name n);
void changeName(Name *n, String lname);
Name changeName2(Name name, String lname);

void main(){
    Name n = createName("Jio","Delgado");
    changeName(&n,"Choi");
    Name k = changeName2(n,"Jansen");
    displayName(n);
    displayName(k);
    
}
Name changeName2(Name name, String lname){
    strcpy(name.lname,lname);
    return name;
}
Name createName(String fname, String lname){
    Name n;
    strcpy(n.fname,fname);
    strcpy(n.lname,lname);
    return n;
}
void changeName(Name *n, String lname){
    strcpy(n->lname,lname);
}

void displayName(Name n){
    printf("%s, %s",n.lname,n.fname);
}