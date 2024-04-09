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
       takenOrders newOr;
    FILE *file2 = fopen(foodsTxt,"rb+");
    food currentF;
    fread(&current,sizeof(current),1,file);
    while(!feof(file))
    {
        if(foodID == currentF.foodID)
        {
            break;                  //AYNI İŞLEM YAPILIYORRR
        }
        fread(&current,sizeof(current),1,file);
    } fclose(file2);
       newOr.f=currentF;
       newOr.isActive=true;
       newOr.isConfirmed=false;
       newOr.quantity=amount;
       strcpy(newOr.tableID,tableId);

       fwrite(&newOr,sizeof(takenOrders),1,file);//DOSYAYA YAZARKEN YEMEK İSMİNİ BİNARY YAZDIRIYOR
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

void updateAmount(char tableID[],int foodID,int amount)
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
            if(foodID == current.f.foodID)//FoodId saçma değer döndürüyor
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
            printf("Amount is updated...");
			char text[200];
			sprintf(text,"Amount of the food with id %d in table %s is updated as %d\n",foodID,tableID,amount);
			writeToLogFile(text);
		}
		else
        {
            printf("Order is not found!!!\n");
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
            billAmount+=(current.quantity * current.f.foodPrice);
            fread(&current, sizeof(current),1,file);
        }

        fclose(file);
    file = fopen(tableId, "w+");
    fclose(file);
    printf("TOTAL FEE:%f",billAmount);
    printf("Payment received successfully....");
    char text[200];
    sprintf(text,"Payment of the table %s received successfully....\nTOTAL FEE :%f\n",tableId,billAmount);
    writeToLogFile(text);
}


void cancelOrder(char tableId[],int foodId)
{   DIR *dir;
    dir= opendir(tableId);
    strcat(tableId,"//");
    strcat(tableId,ordersTxt);
    FILE *file = fopen(tableId,"a+b");
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
            printf("Order is canceled...");
			char text[200];
			sprintf(text,"Order of the food with id %d in table %s is canceled \n",foodId,tableId);
			writeToLogFile(text);
		}

}
