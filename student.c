#include <stdio.h>		//header files
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

struct student{		//structure of student
    char ID[25];
    char name[20];
    char address[20];
    char parentname[20];
    int Class;
    long unsigned int phone_no;
};

struct stu_marksheet		//structure of student marksheet
{
	char name[20];
	char roll_no[10];
	char sub1[10];
	char sub2[10];
	char sub3[10];
	char sub4[10];
	char sub5[10];
	char sub6[10];
	char total[10];
	char percentage[10];
};

struct student stu;
struct stu_marksheet stu_marks;

//This will set the forground color for printing in a console window.
void SetColor(int ForgC)
{
     WORD wColor;
     //We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        //Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     //Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     //This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
     //A return value... indicating how many chars were written
     //   not used but we need to capture this since it will be
     //   written anyway (passing NULL causes an access violation).
     DWORD count;
     //This is a structure containing all of the console info
     // it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          //This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 8) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

COORD coord = {0,0}; //set the cordinate to 0, 0 (top-left corner of window);
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawRectangle(){	//dimensions to draw rectangle
    int i, j;
    gotoxy(0,0);
    printf("%c",201);
    for(i = 1; i < 78; i++){
        gotoxy(i, 0);
        printf("%c",205);
    }
    gotoxy(78,0);
    printf("%c",187);
    for(i = 1; i < 25; i++){
        gotoxy(78, i);
        if(i == 6){
            printf("%c",185);
        }else{
            printf("%c",186);
        }
    }
    gotoxy(78, 25);
    printf("%c",188);
    for(i = 77; i > 0; i--){
        gotoxy(i,25);
        if(i == 35){
            printf("%c",202);
        }else{
            printf("%c",205);
        }
    }
    gotoxy(0,25);
    printf("%c",200);
    for(i = 24; i > 0; i--){
        gotoxy(0,i);
        if(i == 6){
            printf("%c",204);
        }else{
            printf("%c",186);
        }
    }

    for(i = 1; i < 78; i++){
        gotoxy(i,6);
        if(i == 35){
            printf("%c",203);
        }else{
            printf("%c",205);
        }
    }

    for(i = 7; i < 25; i++){
        gotoxy(35,i);
        printf("%c",186);
    }

}

void clearWindow(){		//function to clear the screen
    int i,j;
    for(i = 37; i < 78; i++){
        for(j = 7; j < 25; j++){
            gotoxy(i,j);printf(" ");
        }
    }
    return;
}

void window(){		//window function
    drawRectangle();
    gotoxy(28,2);
    SetColor(35);
    printf("STUDENT RECORD SYSTEM   ");
    gotoxy(28,3);
    printf("\tVasavi High School");
    gotoxy(31,4);
    gotoxy(25,24);
    SetColor(0);

}

void print_heading(const char st[]){	//function to print heading
    SetColorAndBackground(31,0);
    gotoxy(45,8);printf("SRS : %s",st);
    SetColorAndBackground(17,0);
}

void updateCredential()		//update_credential function
{
    clearWindow();
	char ch,up[10],login1[100];
	char y[10]="yes";
	char n[10]="no";
	int j=0,l=0,x=37;
	FILE *fp;
	fp=fopen("password.txt","w");
	do{
		printf("\nEnter yes to update your credentials and no to not:");
		fflush(stdin);
		gets(up);
		if(strcmp(up,y)==0)
		{
			printf("Enter new password:");
			while(1)
			{
				ch=getch();
				if(ch==13)
    				break;
				gotoxy(x,14);printf("*");
				login1[j++]=ch;
			}
			login1[j]='\0';
			
			fwrite(login1,sizeof(strlen(login1)+1),1,fp);
			fclose(fp);
			printf("\nYou have updated your password\n");
			system("cls");
			mainwindow();
		}
		else
		{
			system("cls");
			mainwindow();
		}
	}while(l<3);
    if(l>=3)
	{
		printf("\n\t\t\t\tLogin failed!!!! Invalid user!!!\t\t\t");
	}
}

void add_student(){		//add_student function
    clearWindow();
    print_heading("Adding Record");
    int x = 37;
    FILE *fp;
    fp = fopen("record.txt","ab+");
    SetColor(45);
    if(fp == NULL){
        MessageBox(0,"Error in Opening file\nMake sure your file is not write protected","Warning",0);
		printf("\nNo file exists\n");

    }else{
        fflush(stdin);
        gotoxy(x,10);printf("ID: ");gets(stu.ID);
        gotoxy(x,12);printf("Name: ");gets(stu.name);
        gotoxy(x,14);printf("Address: ");gets(stu.address);
        gotoxy(x,16);printf("Parent's name: ");gets(stu.parentname);
        gotoxy(x,18);printf("Class: ");scanf("%d",&stu.Class);
        gotoxy(x,20);printf("Phone Number: ");scanf("%ld",&stu.phone_no);
        fwrite(&stu, sizeof(stu), 1, fp);
        gotoxy(40,22); printf("The record is added sucessfully");
    }
    SetColor(28);
    fclose(fp);
    return;
}

void search_student()		//search_student function
{		
    clearWindow();
    print_heading("Search Record");
    SetColor(45);
    char student_id[15];
    int isFound = 0;
    gotoxy(37,10);printf("Enter ID to Search: ");fflush(stdin);
    gets(student_id);
    FILE *fp;
    fp = fopen("record.txt","rb");
    while(fread(&stu,sizeof(stu),1,fp) == 1){
        if(strcmp(student_id,stu.ID) == 0){
            isFound = 1;
            break;
        }
    }
    if(isFound == 1){
        gotoxy(37,12);printf("The record is Found");
        gotoxy(37,14);printf("ID: %s",stu.ID);
        gotoxy(37,15);printf("Name: %s",stu.name);
        gotoxy(37,16);printf("Address: %s",stu.address);
        gotoxy(37,17);printf("Parent's Name: %s",stu.parentname);
        gotoxy(37,18);printf("Class: %d",stu.Class);
        gotoxy(37,19);printf("Phone No: %ld",stu.phone_no);
    }else{
        gotoxy(37,12);printf("Sorry, No record found in the database");
    }
    SetColor(28);
    fclose(fp);
    return;
}

void modify_student()	//modify_student function
{
    clearWindow();
    print_heading("Modify Record");
    SetColor(45);
    char student_id[15];
    int isFound = 0, x = 37;
    gotoxy(37,10);printf("Enter ID to Modify: ");fflush(stdin);
    gets(student_id);
    FILE *fp;
    fp = fopen("record.txt","ab+");
    while(fread(&stu, sizeof(stu),1,fp) == 1){
        if(strcmp(student_id, stu.ID) == 0){
            fflush(stdin);
            gotoxy(x,12);printf("ID: ");gets(stu.ID);
            gotoxy(x,13);printf("Name: ");gets(stu.name);
            gotoxy(x,14);printf("Address: ");gets(stu.address);
            gotoxy(x,15);printf("Parent's name: ");gets(stu.parentname);
            gotoxy(x,16);printf("Class: ");scanf("%d",&stu.Class);
            gotoxy(x,17);printf("Phone Number: ");scanf("%ld",&stu.phone_no);
            fseek(fp,-sizeof(stu), SEEK_CUR);
            fwrite(&stu,sizeof(stu), 1, fp);
            isFound = 1;
            break;
        }
    }
    if(!isFound){
        gotoxy(x, 12);printf("No Record Found");
    }
    fclose(fp);
    SetColor(28);
    return;
}

void generate_marksheet()		//generate_marksheet function
{

	clearWindow();
    print_heading("Marksheet");
    SetColor(45);
	system("cls");
	char name[25],divission[10];
	FILE *fp;
	fp=fopen("marksheet.txt","ab+");
	int x=37,sub1,sub2,sub3,sub4,sub5,sub6,total,percentage;
	gotoxy(37,10);printf("Enter the Roll No : ");fflush(stdin);
	gets(stu_marks.roll_no);
	gotoxy(37,12);printf("Enter Name        : ");
	fflush(stdin);
	gets(stu_marks.name);
	gotoxy(x,14);printf("Enter Subject Marks :\n");
	gotoxy(x,16);printf("Enter Telugu Subject marks:");gets(stu_marks.sub1);
	sub1=atoi(stu_marks.sub1);
	gotoxy(x,18);printf("Enter Hindi Subject marks:");gets(stu_marks.sub2);
	sub2=atoi(stu_marks.sub2);
	gotoxy(x,20);printf("Enter Social Subject marks:");gets(stu_marks.sub3);
	sub3=atoi(stu_marks.sub3);
	gotoxy(x,22);printf("Enter English Subject marks:");gets(stu_marks.sub4);
	sub4=atoi(stu_marks.sub4);
	gotoxy(x,24);printf("Enter Math Subject marks:");gets(stu_marks.sub5);
	sub5=atoi(stu_marks.sub5);
	gotoxy(x,26);printf("Enter Chem Subject marks:");gets(stu_marks.sub6);
	sub6=atoi(stu_marks.sub6);
	total=sub1+sub2+sub3+sub4+sub5+sub6;
	itoa(total,stu_marks.total,10);
	percentage=(total/600)*100;
	itoa(percentage,stu_marks.percentage,10);
	fwrite(&stu_marks,sizeof(stu_marks), 1, fp);
	gotoxy(x,28);printf("\n\t\t\t\t\t\tThe data is registered sucessfully!!!!!\n");	
	system("cls");
	fclose(fp);
	SetColor(28);
}

void delete_student()		//delete_student function
{
    clearWindow();
    print_heading("Delete the Record");
    SetColor(45);
    char student_id[15];
    int isFound = 0, x = 37;
    gotoxy(37,10);printf("Enter ID to to be Deleted: ");fflush(stdin);
    gets(student_id);
    FILE *fp, *temp;
    fp = fopen("record.txt","rb");
    temp = fopen("temp.txt", "wb");
    while(fread(&stu, sizeof(stu),1,fp) == 1){
        if(strcmp(student_id, stu.ID) != 0){
            fwrite(&stu,sizeof(stu),1,temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("record.txt");
    rename("temp.txt","record.txt");
    gotoxy(37,12);printf("The record is deleted sucessfully");
    SetColor(28);
    return;
}

void holiday_list()		//holiday_list function
{
	int x=37,ch,y=40;
	do{
		printf("Enter:\n");
		printf("1.January\n");
		printf("2.February\n");
		printf("3.March\n");
		printf("4.April\n");
		printf("5.May\n");
		printf("6.June\n");
		printf("7.July\n");
		printf("8.August\n");
		printf("9.September\n");
		printf("10.October\n");
		printf("11.November\n");
		printf("12.December\n");
		printf("13.Exit\n");
		printf("Enter your choice:\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				   printf("\tHOLIDAYS in January 2020\t\t\t\t\n");
				   printf("New year----------- 1st January\n");
				   printf("Sankranthi---------14th- 16th January\n");
				   printf("Republic Day-------26th January\n\n");
				   break;
			case 2:
				   printf("\tHOLIDAYS in February 2020\t\t\t\t\n");
				   printf("Maha Shiva Ratri---21st February\n\n");
				   break;
			case 3:
				   printf("\tHOLIDAYS in March 2020\t\t\t\t\n");
				   printf("Holi---------------10th March\n");
				   printf("Ugadi--------------23rd March\n\n");
				   break;
			case 4:
				   printf("\tHOLIDAYS in April 2020\t\t\t\t\n");
				   printf("Sri RamaNamavi-----2nd April\n");
				   printf("Good Friday--------10th April\n");
				   printf("Ambedkar Jayanti---14th April\n\n");
				   break;
			case 5:
				   printf("\tHOLIDAYS in May 2020\t\t\t\t\n");
				   printf("Ramzan-------------5th May\n\n");
				   break;
			case 6:
				   printf("\tHOLIDAYS in June 2020\t\t\t\t\n");
				   printf("No Holidays!!!!\n\n");
				   break;
			case 7:
				   printf("\tHOLIDAYS in July 2020\t\t\t\t\n");
				   printf("Bakrid-------------1st July\n");
				   printf("RakshaBandan-------3rd July\n\n");
				   break;
			case 8:
				   printf("\tHOLIDAYS in August 2020\t\t\t\t\n");
				   printf("Independence Day---15th August\n");
				   printf("Ganesh Chathurthi--22nd August\n");
				   printf("Muhharam-----------30th August\n\n");
				   break;
			case 9:
				   printf("\tHOLIDAYS in September 2020\t\t\t\t\n");
				   printf("No Holidays!!!!!\n\n");
				   break;
			case 10:
					printf("\tHOLIDAYS in October 2020\t\t\t\t\n");
					printf("Gandhi Jayanti-----2nd October\n");
					printf("Dussera------------25th October\n\n");
					break;
			case 11:
					printf("\tHOLIDAYS in November 2020\t\t\t\t\n");
					printf("Diwali-------------14th November\n");
					printf("Children's Day-----14th November\n\n");
					break;
			case 12:
					printf("\tHOLIDAYS in December 2020\t\t\t\t\n");
					printf("Chrismas-----------25th December\n\n");
					break;
			case 13:return;
					break;
			default:gotoxy(x,32);printf("Invalid input\n\n");
					break;
		}
	}while(ch!=0);
}

void examination_Dates()	//examination_Dates function
{
	system("cls");
	int x=37,ch;
	do{
		gotoxy(x,8);printf("Enter Your Choics:-");
		gotoxy(x,10);printf("1.Quaterly_Examination");
		gotoxy(x,12);printf("2.Half Yearly_Examination");
		gotoxy(x,14);printf("3.Final_Examination");
		gotoxy(x,16);printf("4.Go back to menu");
		gotoxy(x,18);scanf("%d",&ch);
		switch(ch)
		{
			case 1:gotoxy(x,20);printf("Quaterly_Examination");
				   gotoxy(x,22);printf("15-09-2020------------Telugu");
				   gotoxy(x,24);printf("16-09-2020------------Hindi");
				   gotoxy(x,26);printf("17-09-2020------------English");
				   gotoxy(x,28);printf("18-09-2020------------Math");
				   gotoxy(x,30);printf("19-09-2020------------Chem");
				   gotoxy(x,32);printf("20-09-2020------------Social");
				   break;
			case 2:gotoxy(x,20);printf("Half Yearly_Examination");
				   gotoxy(x,22);printf("15-11-2020------------Telugu");
				   gotoxy(x,24);printf("16-11-2020------------Hindi");
				   gotoxy(x,26);printf("17-11-2020------------English");
				   gotoxy(x,28);printf("18-11-2020------------Math");
				   gotoxy(x,30);printf("19-11-2020------------Chem");
				   gotoxy(x,32);printf("20-11-2020------------Social");
				   break;
			case 3:gotoxy(x,20);printf("Final_Examination");
				   gotoxy(x,22);printf("15-03-2021------------Telugu");
				   gotoxy(x,24);printf("16-03-2021------------Hindi");
				   gotoxy(x,26);printf("17-03-2021------------English");
				   gotoxy(x,28);printf("18-03-2021------------Math");
				   gotoxy(x,30);printf("19-03-2021------------Chem");
				   gotoxy(x,32);printf("20-03-2021------------Social");
				   break;
			case 4: system("cls");
					return;
					break;
			default:gotoxy(x,20);printf("Invalid Input");
				    break;
		}
	}while(ch!=0);
}
				   
void mainwindow()		//mainwindow function
{
    int choice;
    SetColor(18);
    int x = 2;
    while(1){
        gotoxy(x,8);printf("1. Search Student");
        gotoxy(x,10);printf("2. Add Student");
        gotoxy(x,12);printf("3. Modify Student Record");
        gotoxy(x,14);printf("4. Generate Marksheet");
        gotoxy(x,16);printf("5. Delete Student Record");
		gotoxy(x,18);printf("6. update_Credential");
        gotoxy(x,20);printf("7. Exit");
        gotoxy(x,22);printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                search_student();
                break;
            case 2:
                add_student();
                break;
            case 3:
                modify_student();
                break;
            case 4:
			    generate_marksheet();
                break;
            case 5:
                delete_student();
                break;
            case 6:
				system("cls");
			    updateCredential();
			    break;
			case 7:
				system("cls");
				exit(0);
                break;
            default:
				printf("\nInvalid choice");
                break;
        }

    }

}

int main()				//main method
{		
    ClearConsoleToColors(30,0);
    SetConsoleTitle("Student Report System");
	printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#");
    printf("\n\t\t\t        #                  WELCOME                  #");
    printf("\n\t\t\t        #                    TO                     #");
    printf("\n\t\t\t        #               Student Report              #");
    printf("\n\t\t\t        #                   SYSTEM                  #");
    printf("\n\t\t\t        #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
	system("cls");
	//char password[]="student";
	char login[100],ch,ch1;
    int i=0,l=0,j=0,choice;
	char stu_id[10]="10",teacher_id[10]="15",index[10];
	int k=0;
	do
	{
		char password[100];
		FILE *fp;
		fp=fopen("password.txt","r");
		fread(password,sizeof(strlen(password)+1),1,fp);
		i=0;
		printf("\nEnter the password:");
		while(1)
		{
			ch=getch();
			if(ch==13)
				break;
			printf("*");
			login[i++]=ch;
		}
		login[i]='\0';
		fclose(fp);
		if(strcmp(login,password)==0)
		{
			printf("\nEnter\n1.holiday_list\n2.examination_Dates\n3.Check\n4.Exit\n");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:holiday_list();
					   break;
				case 2:examination_Dates();
						break;
			    case 3:printf("\nEnter the number to have access to the student record:");
					   while(2)
					   {
							ch1=getch();
							if(ch1==13)
								break;
							printf("*");
							index[k++]=ch1;
					   }
					   index[k]='\0';
					   if(strcmp(index,teacher_id)==0)
					   {
						   system("cls");
						   window();
					       mainwindow();
				       }
				       else
					   {
							printf("\nYou are not eligible for acessing the student record\n");
							exit(0);
					   }
						break;
				case 4:exit(1);
						break;
				default:printf("\nInvalid input");
			}
		}
		else
		{
			printf("\nPlease enter the correct user name and password\n");
			l++;
		}
	}while(l<3);
	printf("\nInvalid user.........\n");
	return 0;
}
