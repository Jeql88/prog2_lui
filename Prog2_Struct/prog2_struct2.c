#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX 10

typedef char String[20];
typedef struct{
    String fname;
    String lname;
} Name;
typedef struct {
    Name name;
    int age;
    char sex;
    String address;
} Person;


bool addPerson(Person list[], int *count, Person p);
void displayAllPerson(Person list[], int count);
Person createPerson(Name name, int age, char sex, String address);
int countFemale(Person list[], int count);
void getNames(Person list[], int count, Name name[], int *name_count, String city);
void displayNames(Name name[], int count);
Name createName(String fname, String lname);
void main(){
    Person list[MAX];
    int count = 0;
    Person p1 = createPerson(createName("Josh","Lui"),19,'M',"Cebu City");
    Person p2 = createPerson(createName("Jan","Choi"),19,'F',"Cebu City");
    addPerson(list,&count,p1);
    addPerson(list,&count,p2);
    displayAllPerson(list,count);
    int f_count = countFemale(list,count);
    printf("Number of females = %d",f_count);
    int name_count = 0;
    Name name_list[MAX];
    getNames(list,count,name_list,&name_count,"Cebu City");
    displayNames(name_list,name_count);
}
bool addPerson(Person list[], int *count, Person p){
    if (*count < MAX){
        list[(*count)++] = p;
        return true;
    } else{
        return false;
    }
}
void displayAllPerson(Person list[], int count){
    printf("%10s|%10s|%5s|%5s|%10s\n", "FNAME", "LNAME", "AGE", "SEX","ADDRESS");
    for (int i = 0; i < count; ++i){
        printf("%10s|%10s|%5d|%5c|%10s\n",list[i].name.fname,list[i].name.lname,list[i].age,list[i].sex,list[i].address);
    }
}
void displayNames(Name name[], int count){
    for (int i = 0; i < count; ++i){
        printf("\n%s %s",name[i].fname, name[i].lname);
    }
}
Name createName(String fname, String lname){
    Name n;
    strcpy(n.fname,fname);
    strcpy(n.lname,lname);
    return n;
}

Person createPerson(Name name, int age, char sex, String address){
    Person p;
    strcpy(p.name.fname,name.fname);
    strcpy(p.name.lname,name.lname);
    p.age = age;
    p.sex = sex;
    strcpy(p.address,address);
    return p;
}
int countFemale(Person list[], int count){
    int f_count = 0;
    for (int i = 0; i < count; ++i){
        if (list[i].sex == 'F'){
            f_count++;
        }     
    }
    return f_count;
}
void getNames(Person list[], int count, Name name[], int *name_count, String city){
    for (int i = 0; i < count; ++i){
        if (strcmp(list[i].address,city)==0){
            strcpy(name[(*name_count)].lname,list[i].name.lname);
            strcpy(name[(*name_count)++].fname,list[i].name.fname);  
        }
    }
}