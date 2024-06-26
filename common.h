#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED
#include <stdbool.h>

typedef struct food
{
    int foodID;
    char foodName[50];
    float foodPrice;
}food;

typedef struct takenOrders
{
    food f;
    int quantity;
    char tableID[250];
    bool isConfirmed;
    bool isActive;
}takenOrders;

long getFileContentSize(FILE *fp);

void truncateFile(char fileName[]);

void writeToLogFile(char text[]);

void displaySingleFood(food food);
void displayFoodMenu();

void printTakenOrders(takenOrders currentTOrders);
void showOrderListTable(char tableID[]);

bool isExistTable(char tableID[]);
bool isExistFood(int foodId);

#endif // COMMON_H_INCLUDED
