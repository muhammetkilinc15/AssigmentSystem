#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include "customer.h"
extern char *foodsTxt;
extern char *ordersTxt;
extern char *closedOrdersTxt;
extern char *takenOrdersTxt;
extern char *logTtxt;

//This method to receive a new order
void placeNewOrder(char tableId[],int foodID,int amount)
{
   FILE *file = fopen(takenOrdersTxt,"rb+");
   takenOrders current;
   int size=fread(&current,sizeof(current),1,file);
   
   if(size==0)
   {
	
    FILE *file2 = fopen(foodsTxt,"rb+");
    food currentF;
    fread(&currentF,sizeof(currentF),1,file2);
    while(!feof(file2))
    {
        if(foodID == currentF.foodID)
        {
            break;                  
        }
        fread(&currentF,sizeof(currentF),1,file2);
    } 
	   fclose(file2);

	   current.f = currentF;
       current.isActive=true;
       current.isConfirmed=false;
       current.quantity=amount;
       strcpy(current.tableID,tableId);
		
       fwrite(&current,sizeof(current),1,file);
       fclose(file);
       printf("New order is added successfully....\n");

       char text[200];
       sprintf(text,"New order for table %s is taken successfully....\n",tableId);
       writeToLogFile(text);
   }
   else
   {
     printf("We are so busy right now, please try ordering again soon.\n") ;
   }
}

//This method updates the amount of food which taken
void updateQuantity(char tableID[],int foodID,int amount)
{
    DIR *dir;
    dir= opendir(tableID);
    strcat(tableID,"//");
    strcat(tableID,ordersTxt);

    FILE *file = fopen(tableID,"r+b");
    takenOrders current;
        fread(&current, sizeof(current),1,file);
        bool isUpdated = false;
        while( !feof(file))
        {
            if(foodID == current.f.foodID)
            {
                current.quantity = amount;
                fseek(file, -sizeof(current), SEEK_CUR);
                fwrite(&current,sizeof(current),1,file);
                isUpdated = true;
                break;
            }
            fread(&current, sizeof(current),1,file);
        }
        fclose(file);
        closedir(dir);

        if(isUpdated)
		{
            printf("Amount is updated...\n");
			char text[200];
			sprintf(text,"Amount of the food with id %d in table %s is updated as %d\n",foodID,tableID,amount);
			writeToLogFile(text);
		}
		else
        {
            printf("Order is not found!!!\n");
        }

}

//This method pays the bill
void payBill(char tableId[])
{
    strcat(tableId,"//");
    strcat(tableId,ordersTxt);
    FILE *file = fopen(tableId,"rb+");
    takenOrders current;
    fread(&current, sizeof(current),1,file);
    float billAmount=0;
	
        while( !feof(file))
        {
			if(current.isActive)
			{
				billAmount+= (current.f.foodPrice * current.quantity);
			}
            fread(&current, sizeof(current),1,file);
        }

    fclose(file);
    truncateFile(tableId);
    printf("TOTAL FEE:%.2f\n",billAmount);
    printf("Payment received successfully....\n");
    char text[200];
    sprintf(text,"Payment of the table %s received successfully....\nTOTAL FEE:%f",tableId,billAmount);
    writeToLogFile(text);
	manageClosedOrders(1,billAmount);
}


//This method cancels the meals that have been abandoned
void cancelOrder(char tableId[],int foodId)
{   DIR *dir;
    dir= opendir(tableId);
    strcat(tableId,"//");
    strcat(tableId,ordersTxt);
    FILE *file = fopen(tableId,"rb+");
    takenOrders current;
        fread(&current, sizeof(current),1,file);
        bool isCanceled = false;
        while( !feof(file))
        {
            if(foodId == current.f.foodID)
            {
				if(current.isActive==false)
				{
					printf("The order is already canceled. That's why it can't be updated!!!\n");
					break;
				}
                current.isActive=false;
                fseek(file, -sizeof(current), SEEK_CUR);
                fwrite(&current,sizeof(current),1,file);
                isCanceled = true;
            }
            fread(&current, sizeof(current),1,file);
        }
        fclose(file);
        if(isCanceled)
		{
            printf("Order is canceled...\n");
			char text[200];
			sprintf(text,"Order of the food with id %d in table %s is canceled \n",foodId,tableId);
			writeToLogFile(text);
		}
		else
		{
			printf("Order not found!!!\n");
		}
}
