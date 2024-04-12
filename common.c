#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include "common.h"
char *foodsTxt = "Foods.txt";
char *ordersTxt = "Orders.txt";
char *closedOrdersTxt = "ClosedOrders.txt";
char *takenOrdersTxt = "TakenOrders.txt";
char *logTtxt = "log.txt";
int numberOfFoods = 4;


// This function appends the given text to a file named "log.txt".   | ********** UGUR TANSAL **********
void writeToLogFile(char text[])
{
    FILE *file = fopen(logTtxt,"a+");
    fprintf(file,"%s",text);
    fclose(file);
}

// If the type is zero, the admin is reading all payments; otherwise, the customer writing their orders payment  | ********** MUHAMMET KILIN� **********
void manageClosedOrders(int type,float billAmount)
{
	FILE *file ;
    float current;

	if(type==0)
	{
			file = fopen(closedOrdersTxt, "r+");
			if(file==NULL)
			{
				printf("No payment information!!!\n");

			}else
			{
			printf("All payment information:\n");
				while (fscanf(file, "%f", &current) == 1)
				{
				   printf("TOTAL FEE: %.2f\n", current);
				}
			}
	}else
	{
		file = fopen(closedOrdersTxt,"a+");
		fprintf(file,"%f\n",billAmount);
	}

    fclose(file);
}


// This method check the if table is exist return true | ********** UGUR TANSAL **********
bool isExistTable(char tableID[])
{
	DIR *dir = opendir(tableID);
	if(dir !=NULL)
	{
		closedir(dir);
		return true;
	}else
	{
		closedir(dir);
		return false;
	}
}

// This method check the if food is exist return true | ********** MUHAMMET KILIN� **********
bool isExistFood(int foodID)
{
    FILE *file = fopen(foodsTxt,"rb+");
    food current;
    fread(&current,sizeof(current),1,file);
    while(!feof(file))
    {
        if(foodID == current.foodID)
        {
			fclose(file);
            return true;
        }
        fread(&current,sizeof(current),1,file);
    }
    fclose(file);
    return false;

}


// This method print the orders for the given table ID | ********** UGUR TANSAL **********
void showOrderListTable(char tableID[])
{
    if(isExistTable(tableID)==true)
    {
        strcat(tableID,"//");
        strcat(tableID,ordersTxt);
        FILE *file = fopen(tableID,"rb+");
        takenOrders currentTOrders;
        fread(&currentTOrders,sizeof(currentTOrders),1,file);
        int i=1;
        printf("Orders: \n");
        while(!feof(file))
        {
            printf("Food %d\n",i);
            i++;
            showOrderTable(currentTOrders);
            printf("------------------------\n");
            fread(&currentTOrders,sizeof(currentTOrders),1,file);
        }
        fclose(file);
    }
    else
    {
        printf("There is no table with the given id!!!\n");

    }
}

// This method print the orders                  | ********** UGUR TANSAL **********
void showOrderTable(takenOrders currentTOrders)
{
    printf("Table Id : %s\n",currentTOrders.tableID);
    displaySingleFood(currentTOrders.f);
    printf("Amount: %d\n",currentTOrders.quantity);
    printf("Is confirmed: %s\n",currentTOrders.isConfirmed==true ? "Yes" : "No");
    printf("Is active: %s\n",currentTOrders.isActive==true ? "Yes" : "No");

}

// This method print the food                   | ********** MUHAMMET KILIN� **********
void displaySingleFood(food food)
{
    printf("Food id : %d\n",food.foodID);
    printf("Food name : %s\n",food.foodName);
    printf("Food fee : %.2f\n",food.foodPrice);
}


// This method print the all food               | ********** MUHAMMET KILIN� **********
void displayFoodMenu()
{
    food currentFood;
    FILE *file = fopen(foodsTxt,"rb+");
    for(int i = 0; i<numberOfFoods;i++)
    {
        fread(&currentFood, sizeof(currentFood),1,file);
        displaySingleFood(currentFood);
    }
    fclose(file);
}

