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


// This function appends the given text to a file named "log.txt".
void writeToLogFile(char text[])
{
    FILE *file = fopen(logTtxt,"a+");
    fprintf(file,"%s",text);
    fclose(file);
}


// dosya var ise true , yok ise false
bool isExistTable(char tableID[])
{
    return opendir(tableID)!=NULL;
}

bool isExistFood(int foodID)
{
    FILE *file = fopen(foodsTxt,"rb+");
    food current;
    fread(&current,sizeof(current),1,file);
    while(!feof(file))
    {
        if(foodID == current.foodID)
        {
            return true;
        }
        fread(&current,sizeof(current),1,file);
    }
<<<<<<< HEAD
=======
    fclose(file);
>>>>>>> mami
    return false;

}


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
            fread(&currentTOrders,sizeof(currentTOrders),1,file);
        }
        fclose(file);
    }
    else
    {
        printf("There is no table with the given id!!!\n");

    }
}

void showOrderTable(takenOrders currentTOrders)
{
    printf("Table Id : %d\n",currentTOrders.tableID);
    displaySingleFood(currentTOrders.f);
    printf("Amount: %d\n",currentTOrders.quantity);
    printf("Is confirmed: %s\n",currentTOrders.isConfirmed==true ? "Yes" : "No");
    printf("Is active: %s\n",currentTOrders.isActive==true ? "Yes" : "No");

}


// This method print the food
void displaySingleFood(food food)
{
    printf("Food id : %d\n",food.foodID);
    printf("Food name : %s\n",food.foodName);
    printf("Food fee : %.2f\n",food.foodPrice);
}


// This function print the menu
void displayFoodMenu()
{
    DIR *dir;
    char cwd[50];
    getcwd(cwd,50);
    dir = opendir(cwd);
    strcat(cwd,"//");
    strcat(cwd,foodsTxt);
    food currentFood;
    FILE *file = fopen(cwd,"rb+");
    for(int i = 0; i<numberOfFoods;i++)
    {
        fread(&currentFood, sizeof(currentFood),1,file);
        displaySingleFood(currentFood);
    }
    fclose(file);
    closedir(dir);
}

