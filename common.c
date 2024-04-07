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

// This method print menu 
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
    fread(&currentFood, sizeof(currentFood),1,file);
    while(!feof(file))
    {
        printf("Food id : %d\n",currentFood.foodID);
        printf("Food name : %s\n",currentFood.foodName);
        printf("Food fee : %.2f\n",currentFood.foodPrice);
        fread(&currentFood, sizeof(currentFood),1,file);
    }
    fclose(file);
    closedir(dir);
}

void writeToLogFile(char text[])
{
    FILE *file = fopen(logTtxt,"a+");
	fprintf(file,"%s",text);
	fclose(file);
}

