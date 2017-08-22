//list of header files
#include "general_functions.h"
#include "core_functions.h"
#include <tchar.h>
#include <strsafe.h>
#include <time.h>

void SetColor(int ForgC)
{
	WORD wColor;
	//Handle to get the current background attribute
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the foreground colour
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	//Handle to the current output buffer
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//Used to reset the cursor to the top left.
	COORD coord = { 0, 0 };
	///A return value... indicating how many chars were written
	DWORD count;
	//This is a structure containing all of the console info
	//it is used here to find the size of the console
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	///Here we will set the current color
	SetConsoleTextAttribute(hStdOut, wColor);
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		///his fills the buffer with a given character (in this case 32=space).
		FillConsoleOutputCharacter(hStdOut, (TCHAR)32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
		FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
		//This will set cursor position for the next print statement.
		SetConsoleCursorPosition(hStdOut, coord);
	}
	return;
}

void SetColorAndBackground(int ForgC, int BackC)
{
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
	return;
}

int main(){
	TCHAR old[MAX_PATH];
	TCHAR new[MAX_PATH];
	if (GetConsoleTitle(old, MAX_PATH)) {
		StringCchPrintf(new, MAX_PATH, TEXT("LIBRA 1.0"), old); //Console tite set
		if (!SetConsoleTitle(new))
			puts("\n");
		else
			puts("\n");
	}
	SetColorAndBackground(28, 55); //font color set
	ClearConsoleToColors(55, 57); //background color set
	time_t tictoc;
	time(&tictoc);
	printf("The time is %s\n", ctime(&tictoc)); //system time stamp
    login = fopen("password.dat","rb"); //pointer to file containing password
    if(login == NULL){
        gotoxy(10,9);
		puts("Be an administrator. Sign up"); //set password
        adminsignup();
    }
	else{
        adminsignin(); //password input only
    }
    mainmenu();
    return 0;
}

void mainmenu() //main menu display function
{
    while(1){
        system("cls"); //clear screen
        gotoxy(20,3);
        puts("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(20,5);
        puts("\xDB\xDB\xDB\xDB\xB2 1. Add Book");
        gotoxy(20,7);
        puts("\xDB\xDB\xDB\xDB\xB2 2. Delete Book");
        gotoxy(20,9);
        puts("\xDB\xDB\xDB\xDB\xB2 3. Search Book");
        gotoxy(20,11);
        puts("\xDB\xDB\xDB\xDB\xB2 4. View List");
        gotoxy(20,13);
        puts("\xDB\xDB\xDB\xDB\xB2 5. Edit Book Record");
        gotoxy(20,15);
        puts("\xDB\xDB\xDB\xDB\xB2 6. Change Password");
        gotoxy(20,17);
        puts("\xDB\xDB\xDB\xDB\xB2 7. Close Application");
        gotoxy(20,19);
        puts("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(20,21);
        puts("Enter your choice:");
        switch(getch()){
            case '1':
                addbooks();
                break;
            case '2':
                deletebooks();
                break;
            case '3':
                searchbooks();
                break;
            case '4':
                viewbooks();
                break;
            case '5':
                editbooks();
                break;
            case '6':
                change_password();
                gotoxy(10,13);
                puts("press any key to continue...");
                getch();
                break;
            case '7':
                credits();
            default:
                gotoxy(10,23);
                puts("\aWrong Entry!\tPlease re-enter correct option");
                getch(); //holds the screen until a key is pressed
        }
    }
}
void addbooks(void){    //funtion that adds records of books filing
	system("cls");
	FILE *fp; //pointer to file
	int i, choice;
	add_window();
	gotoxy(20,22);
	puts("Enter your choice:");
	scanf("%d", &choice);
	if(choice==7)
        mainmenu() ;
	system("cls");
	fp = fopen("Record.dat","ab+");
	if(getdata(choice) == 1){
        book.cat=categories[choice-1];
        fseek(fp,0,SEEK_END);
        fwrite(&book,sizeof(book),1,fp);
        fclose(fp);
        gotoxy(21,14);
        puts("The record is sucessfully saved");
        gotoxy(21,15);
        puts("Save any more records? (Y/N):");
        if(getch()=='n')
            mainmenu();
        else{
            system("cls");
            addbooks();
        }
    }
    fclose(fp); //file close
}
void deletebooks(){    //function that deletes items from file Record.dat
    FILE *ft,*fp;
    system("cls");
    int d,findbook = 0;
    char another='y';
    while(another=='y'){  //infinite loop
        system("cls");
        gotoxy(10,5);
        puts("Enter ID of book to delete:");
        scanf("%d",&d);
        fp = fopen("Record.dat","rb+");
        while(fread(&book,sizeof(book),1,fp)==1){
            if(book.id==d){
                gotoxy(10,7);
                puts("The book record is available");
                gotoxy(10,8);
                printf("Book name:  %s",book.name);
                gotoxy(10,9);
                printf("Rack No. : %d",book.rackno);
                findbook = 1;
                gotoxy(10,10);
                printf("Do you want to delete it? (Y/N):\n");
                if(getch()=='y'){
                    ft=fopen("test.dat","wb");  //temporary file delete
                    rewind(fp);
                    while(fread(&book,sizeof(book),1,fp)==1){
                        if(book.id!=d){
                            fwrite(&book,sizeof(book),1,ft); //write all in tempory file except when
                        }                              //we want to delete
                    }
                    fclose(fp);
                    fclose(ft);
                    remove("Record.dat");
                    rename("test.dat","Record.dat"); //copy all item from temporary file to fp except when
                                        //we want to delete
                    gotoxy(10,11);
                    printf("The record is sucessfully deleted");
                }
            }
        }
        if(findBook == 0){
            gotoxy(10,10);
            puts("No record is found\n");
            getch();
        }
        gotoxy(10,12);
        puts("Delete another record? (Y/N)");
        fflush(stdin);
        another=getch();
    }
}


void searchbooks()
{
    system("cls");
    puts("*****************************Search Books*********************************");
    gotoxy(20,10);
    puts("\xDB\xDB\xDB\xB2 1. Search By ID");
    gotoxy(20,14);
    puts("\xDB\xDB\xDB\xB2 2. Search By Name");
    gotoxy( 15,20);
    puts("Enter Your Choice");
    switch(getch())
    {
        case '1':
            searchByID();
            break;
        break;
        case '2':
            searchByName();
            break;
        default :
            getch();
            searchbooks();
    }
}

void viewbooks(void)  //show the list of book persists in library
{
	int j;
	FILE *fp;
	system("cls");
	gotoxy(1, 1);
	puts("*********************************Book List*****************************");
	gotoxy(2, 3);
	puts("        ID       BOOK NAME     AUTHOR      QUANTITY     PRICE       RACK ");
	j = 4;
	fp = fopen("Record.dat", "rb+");
	while (fread(&book, sizeof(book), 1, fp) == 1){
			gotoxy(10, j);
			printf("%d", book.id);
			gotoxy(22, j);
			printf("%s", book.name);
			gotoxy(36, j);
			printf("%s", book.author);
			gotoxy(50, j);
			printf("%d", book.quantity);
			gotoxy(57, j);
			printf("%.2f", book.price);
			gotoxy(69, j);
			printf("%d", book.rackno);
			printf("\n\n");
			j++;
	}
	fclose(fp);
	gotoxy(35, 25);
	returnfunc();
}


void editbooks(void)  //edit book information
{
	system("cls");
	FILE *fp;
	int c=0,d;
	gotoxy(20,4);
	printf("****Edit Books Section****");
	char another='y';
	while(another=='y')
	{
		system("cls");
		gotoxy(15,6);
		puts("Enter ID of Book to be edited:");
		scanf("%d",&d);
		fp=fopen("Record.dat","rb+");
		while(fread(&book,sizeof(book),1,fp)==1)
		{
			if(checkid(d)==0)
			{
				gotoxy(15,7);
				puts("The book is availble");
				gotoxy(15,8);
				printf("The Book ID:%d",book.id);
				gotoxy(15,9);
				printf("Enter new name:");
				scanf("%s",book.name);
				gotoxy(15,10);
				printf("Enter new Author:");
				scanf("%s",book.author);
				gotoxy(15,11);
				printf("Enter new quantity:");
				scanf("%d",&book.quantity);
				gotoxy(15,12);
				printf("Enter new price:");
				scanf("%f",&book.price);
				gotoxy(15,13);
				printf("Enter new rackno:");
				scanf("%d",&book.rackno);
				gotoxy(15,14);
				puts("The record is successfully modified");
				fseek(fp,ftell(fp)-sizeof(book),0);
				fwrite(&book,sizeof(book),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
			{
				gotoxy(15,9);
				puts("No record found");
			}
		}
		gotoxy(15,16);
		puts("Modify another record? (Y/N)");
		fflush(stdin);
		another=getch() ;
	}
		returnfunc();
}