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

void newOrder(char tableId[],int foodID,int amount)
{
   FILE *file = fopen(takenOrdersTxt,"ab+");
   takenOrders current;
   int size=fread(&current,sizeof(current),1,file);
   if(size==0)
   {
       fprintf(file,"%s","Kontrol");//Düzeltilecek
       fclose(file);
       char text[200];
       sprintf(text,"New order\n",foodID);
       writeToLogFile(text);
   }
   else
   {
     printf("Hata verilecek") ;//Düzeltilecek
   }
}

void updateAmount(char tableID[],int foodID,int amount)
{
    strcat(tableID,"//");
    strcat(tableID,ordersTxt);
    FILE *file = fopen(tableID,"ab+");
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
            }
            fread(&current, sizeof(current),1,file);
        }
        fclose(file);
         if(isUpdated)
		{

			char text[200];
			sprintf(text,"Loga yazılacak\n",foodID,amount);//Düzeltilecek
			writeToLogFile(text);
		}

}
void payBill(char tableId[])
{
    strcat(tableId,"//");
    strcat(tableId,ordersTxt);
    FILE *file = fopen(tableId,"ab+");
    takenOrders current;
    fread(&current, sizeof(current),1,file);
    float billAmount=0;
        while( !feof(file))
        {
            billAmount+=current.quantity*current.f.foodPrice;
            fread(&current, sizeof(current),1,file);
        }
        fclose(file);
    char text[200];
    sprintf(text,"Loga yazılacak\n",billAmount);//Düzeltilecek
    writeToLogFile(text);
}


void cancelOrder(char tableId[],int foodId)
{
    strcat(tableId,"//");
    strcat(tableId,ordersTxt);
    FILE *file = fopen(tableId,"ab+");
    takenOrders current;
        fread(&current, sizeof(current),1,file);
        bool isCanceled = false;
        while( !feof(file))
        {
            if(foodId == current.f.foodID)
            {
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

			char text[200];
			sprintf(text,"Loga yazılacak\n",foodId);//Düzeltilecek
			writeToLogFile(text);
		}

}
