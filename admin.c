#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
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
		// user ve grup üyeleri okuyabilir , yazabilir ve iþlem yapabilir
		// ,S_IRUSR |S_IWUSR |S_IXUSR |  S_IRGRP |  S_IWGRP |  S_IXGRP
        mkdir(tableID);
        strcat(tableID,"//");
        strcat(tableID,ordersTxt);
		// ab+ append binary +(read and write) demek
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
        printf("Table %s is deleted successfully....\n",tableID);
        char text[200];
		sprintf(text,"Table %s is deleted successfully....\n",tableID);
		writeToLogFile(text);
    }
    else
    {
        printf("There is no table with the given id!!!\n");
    }
}
void checkNewOrder()
{
    takenOrders current;
    FILE *file = fopen(takenOrdersTxt, "rb+");
    fread(&current, sizeof(current), 1, file);

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    fclose(file);

    printf("Size: %ld\n",size);
    if (size == 0)
    {
        printf("No new orders...\n");
        return;
    }
    else
    {
        printTakenOrders(current); // display current order
        printf("Confirm Order?\nYes : 1\nNo  : 0\n");
        printf("Warning: Unconfirmed orders will be canceled!!!\nWarning: Approved orders are assigned to the relevant table!!!\n");
        int selection=-1;
        scanf("%d", &selection);
		char text[200];

        if(selection ==1 || selection == 0)
        {
            truncateFile(takenOrdersTxt); // takenOrders.txt icini bosalttim
            if (selection == 1) {
                printf("New order is taken successfully....\n");
                char temp[100];
                strcpy(temp, current.tableID);
                strcat(temp, "//");
                strcat(temp, ordersTxt);
                current.isConfirmed=true;

                FILE *ordersFile = fopen(temp, "ab+");
                fwrite(&current, sizeof(current), 1, ordersFile);
                fclose(ordersFile);

                sprintf(text,"New order for the table %s added to its order list successfully...\n",current.tableID);
                writeToLogFile(text);
            }
            else
            {
                sprintf(text,"Order for table %s is canceled....\n",current.tableID);
                writeToLogFile(text);
            }
        }
    }
}


void showAllInvocies()
{
   manageClosedOrders(0,0);
}

void updateFood(int foodID,float fee)
{
    if(isExistFood(foodID)==true)
    {

        FILE *file = fopen(foodsTxt, "rb+"); // rb+ read binary +(read and write)
        food current;
        fread(&current, sizeof(current),1,file);
        bool isUpdated = false;
        while( !feof(file))
        {
            if(foodID == current.foodID)
            {
                current.foodPrice = fee;
                fseek(file, -sizeof(current), SEEK_CUR);
                fwrite(&current,sizeof(current),1,file);
                isUpdated = true;
                break;
            }
            fread(&current, sizeof(current),1,file);
        }
        fclose(file);
        if(isUpdated == true)
		{
			printf("Food is updated......\n");
			char text[200];
			sprintf(text,"Fee of the food %d is updated as %f\n",foodID,fee);
			writeToLogFile(text);
		}
    }
	else
    {
         printf("There is no food with the given food ID!!!\n");
    }
}


