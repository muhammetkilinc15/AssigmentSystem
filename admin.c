#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include "admin.h"
extern char *foodsTxt;
extern char *ordersTxt;
extern char *closedOrdersTxt;
extern char *takenOrdersTxt;
extern char *logTtxt;

// This method creates a new table.
void createTable(char tableID[])
{
    if(isExistTable(tableID)==false)
    {

        printf("Table %s is created successfully....\n",tableID);
        mkdir(tableID,S_IRUSR |S_IWUSR |S_IXUSR);
        strcat(tableID,"//");
        strcat(tableID,ordersTxt);
        FILE *file = fopen(tableID,"ab+");
        fclose(file);
        char text[200];
        sprintf(text,"Table %s is created successfully....\n",tableID);
        writeToLogFile(text);

    }
    else
    {
        printf("This table already exist!!!\n");
    }
}
void deleteTable(char tableID[])
{
    if(isExistTable(tableID)==true)
    {
        char temp[250];
        strcpy(temp,tableID);
        strcat(temp,"//");
        strcat(temp,ordersTxt);
        remove(temp); // orders.txt is deleted...
        rmdir(tableID); // table is deleted...
<<<<<<< HEAD
         printf("Table %s is deleted successfully....\n",tableID);
=======
        printf("Table %s is deleted successfully....\n",tableID);
>>>>>>> mami
        char text[200];
		sprintf(text,"Album %s is deleted successfully....\n",tableID);
		writeToLogFile(text);
    }
    else
    {
        printf("There is no table with the given id!!!\n");
    }
}
<<<<<<< HEAD

=======
void checkNewOrder()
{
    FILE *file = fopen(takenOrdersTxt,"rb+");
    takenOrders current;
    fread(&current,sizeof(current),1,file);
    printf("size: %d \n",sizeof(current));
    showOrderTable(current);
    printf("Confirm Order?\nYes : 1\nNo: 0\n");
    printf("Warning: Unconfirmed orders will be canceled!!!\nWarning: Approved orders are assigned to the relevant table!!!\n");
    int selection=-1;
    scanf("%d",selection);
    fprintf(file,"");
}

void showAllInvocies()
{
    DIR *dir;
    char cwd[50];
    getcwd(cwd,50);
    dir = opendir(cwd);
    strcat(cwd,closedOrdersTxt);
    FILE *file = fopen(cwd,"rb+");
    float price=0.0;
    fread(&price,sizeof(price),1,file);
    printf("All payment information : \n");
    while(!feof(file))
    {
        printf("TOTAL FEE: %.2f",price);
        fread(&price,sizeof(price),1,file);
    }
    fclose(file);
    closedir(dir);
}
>>>>>>> mami


