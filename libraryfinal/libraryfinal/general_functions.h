#include "variables.h"

void gotoxy (int x, int y)
{
	COORD coord;
        coord.X = x; coord.Y = y; // X and Y coordinates
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (!SetConsoleCursorPosition(hConsole, coord)) {

		}
}

void returnfunc()
{
	puts(" \nPress ENTER to return to main menu");
    a:
        if(getch()==13) //allow only use of enter
            mainmenu();
        else
        goto a;
}

void get_password(char* pass)
{
	char temp_passP[25];
	int i = 0;
	while (1)
	{
		temp_passP[i] = getch();
		if (temp_passP[i] == 13){ break; }
		else if (temp_passP[i] == 8)
		{
			if (i != 0) {
				printf("\b \b");
				i--;
			}
			else { printf("\a"); }
		}
		else
		{
			printf("*");
			*(pass + i) = temp_passP[i];
			i++;
		}
		*(pass + i) = '\0';
	}
}




void credits(){
    system("cls");
    gotoxy(16,3);
    puts("Programmers....");
    gotoxy(16,6);
    puts("Mansoor Mubashir Faizan");
    gotoxy(16,8);
    puts("E-mail: 14besefzafar@seecs.edu.pk");
    gotoxy(16,10);
    puts("SEECS");
    gotoxy(16,11);
    puts("NUST H12 Islamabad");
    gotoxy(10,17);
    puts("Exit in 3 seconds...........>");
    Sleep(3000);
    exit(0);
}


void adminsignup(){
    char temp[10];
    login = fopen("password.dat","wb");
    gotoxy(10,10);
    puts("Enter password: ");
    get_password(password);
    gotoxy(10,11);
    puts("Re Enter Password: ");
    get_password(temp);
    while(strcmp(password,temp)!=0){
        gotoxy(10,10);
        puts("Password did not match! Enter again");
        gotoxy(10,11);
        puts("Enter password: ");
        get_password(password);
        gotoxy(10,12);
        puts("Re Enter Password: ");
        get_password(temp);
        system("cls");
    }
    fwrite(&password,sizeof(password),1,login);
    fclose(login);
}

void adminsignin(){
    char temp[10];
    login = fopen("password.dat","rb");
    gotoxy(10,10);
    puts("Enter password: ");
    get_password(temp);
    while(fread(&password, sizeof(password),1,login)==1){
        while(strcmp(temp,password)!=0){
            system("cls");
            gotoxy(10,10);
            puts("Password did not match! ");
            puts("Enter Again: ");
            get_password(temp);
        }
        gotoxy(10,11);
        puts("Password Matched");
        break;
    }
    fclose(login);
    gotoxy(10,12);
    puts("Press any key...");
    getch();
}

void add_window(){
    gotoxy(20,5);
	puts("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2SELECT CATEGORIES\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(20,7);
	puts("\xDB\xDB\xDB\xDB\xB2 1. Arts");
	gotoxy(20,9);
	puts("\xDB\xDB\xDB\xDB\xB2 2. Economics");
	gotoxy(20,11);
	puts("\xDB\xDB\xDB\xDB\xB2 3. Engineering");
	gotoxy(20,13);
	puts("\xDB\xDB\xDB\xDB\xB2 4. History");
	gotoxy(20,15);
	puts("\xDB\xDB\xDB\xDB\xB2 5. Humanities");
	gotoxy(20,17);
	puts("\xDB\xDB\xDB\xDB\xB2 6. Science");
	gotoxy(20,19);
	puts("\xDB\xDB\xDB\xDB\xB2 7. Back to main menu");
	gotoxy(20,21);
	puts("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

}

int change_password(){
    system("cls");
    FILE *login;
    char old_pass[10], new_pass[10];
    gotoxy(10,10);
    puts("Enter Old password: ");
    get_password(old_pass);
    gotoxy(10,11);
    puts("Enter New password: ");
    get_password(new_pass);
    login = fopen("password.dat","rb+");
    while(fread(&password,sizeof(password),1,login)==1){
        if(strcmp(old_pass,password)==0){
            strcpy(password,new_pass);
            fseek(login,-sizeof(password),SEEK_CUR);
            fwrite(&password,sizeof(password),1,login);
            fclose(login);
            gotoxy(10,12);
            puts("Password sucessfully changed! ");
            return 1;
        }else{
            gotoxy(10,12);
            puts("Password changing process failed!");
            return 0;
        }

    }

}
