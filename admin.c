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
		// user ve grup üyeleri okuyabilir , yazabilir ve işlem yapabilir
        mkdir(tableID,S_IRUSR |S_IWUSR |S_IXUSR |  S_IRGRP |  S_IWGRP |  S_IXGRP);
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
	// rb+ read binary +(read and write)
    FILE *file = fopen(takenOrdersTxt, "rb+");
    takenOrders current;
    size_t bytesRead = fread(&current, sizeof(current), 1, file);

    if (bytesRead == 0) {
        printf("Size: 0\n");
        printf("No new orders...\n");
        return;
    }
    else
    {

        printf("size %d  \n", sizeof(current));
        showOrderTable(current);
        fclose(file);
        // 	w+ write +(read and write)	takenOrders.txt dosyasının içeriğini boşalt
        file = fopen(takenOrdersTxt, "w+");
        fclose(file);

        printf("Confirm Order?\nYes : 1\nNo  : 0\n");
        printf("Warning: Unconfirmed orders will be canceled!!!\nWarning: Approved orders are assigned to the relevant table!!!\n");

        int selection = -1;
        scanf("%d", &selection);

        if (selection == 1) {
            printf("New order is taken successfully....\n");
            char temp[100];
            strcpy(temp, current.tableID);
            strcat(temp, "//");
            strcat(temp, ordersTxt);
            current.isConfirmed=true;
            // orders.txt dosyasını "ab+ (append binary read and write)" modunda aç, current verisini yaz ve kapat
            FILE *ordersFile = fopen(temp, "ab+");
            if (ordersFile == NULL) {
                perror("Error opening file");
                return;
            }
            fwrite(&current, sizeof(current), 1, ordersFile);
            fclose(ordersFile);
			char text[200];
			sprintf(text,"New order for the table %s added to its order list successfully...\n",current.tableID);
			writeToLogFile(text);
        }
        else
        {
           char text[200];
			sprintf(text,"Order for table %s is canceled....\n",current.tableID);
			writeToLogFile(text);
        }
    }
}

void showAllInvocies()
{
   operationForClosedOrders(0,0);
}

void updateFood(int foodID,float fee)
{
    if(isExistFood(foodID)==true)
    {
		// rb+ read binary +(read and write)
        FILE *file = fopen(foodsTxt, "rb+");
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
    }else
    {
         printf("There is no food with the given food ID!!!\n");
    }
}


