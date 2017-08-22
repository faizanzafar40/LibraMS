//list of header files
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>

FILE *login; //file pointer
//list of global variables
char findBook;
char password[10];
int choice;
struct BOOK //structure definition of BOOK
{
    int id;
    char name[20];
    char author[20];
    int quantity;
    float price;
    int rackno;
    char *cat;
};
struct BOOK book;

COORD coord = {0, 0};

//list of function prototypes
char categories[][15] = { "Arts", "Economics", "Engineering", "History", "Humanities", "Science" };
void returnfunc(void);
void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void editbooks(void);
void searchbooks(void);
void issuebooks(void);
void viewbooks(void);
void closeapplication(void);
int  getdata(int);
int  checkid(int);
void Password();
void get_password(char *);
void issuerecord();
void credits();
void adminsignup();