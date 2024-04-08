#include <stdio.h>
#include <stdlib.h>
#include "customer.h"
int main()
{
    int selection, amount, foodId;
    char tableId[250];
    do{
        printf("Display food menu (1)\n");
        printf("Place a new order(2)\n");
        printf("Show order list of table (3)\n");
        printf("Update amount (4)\n");
        printf("Pay the bill (5)\n");
        printf("Cancel order (6)\n");
        printf("Exit (7)\n");
        printf("Enter your selection : ");
        scanf("%d",&selection);
        switch(selection){

        case 1:
            displayFoodMenu();
            break;
        case 2:
            printf("Enter table ID: ");
            scanf("%s",&tableId);
            printf("Enter food ID: ");
            scanf("%d",&foodId);
            printf("Enter amount: ");
            scanf("%d",&amount);

            if(!isExistTable(tableId))
            {
                printf("There is no table with the given id!!!");
            }
            else if(!isExistFood(foodId))
            {
                printf("There is no food with the given id!!!");
            }
            else{
                newOrder(tableId,foodId,amount);
            }
            break;
        case 3:
            printf("Enter table ID: ");
            scanf("%s",&tableId);

            showOrderListTable(tableId);
            break;
        case 4:

            printf("Enter table ID: ");
            scanf("%s",&tableId);
            printf("Enter food ID to update: ");
            scanf("%d",&foodId);
            printf("Enter new amount: ");
            scanf("%d",&amount);

            if(!isExistTable(tableId))
            {
                printf("There is no table with the given id!!!");
            }
            else{
                updateAmount(tableId,foodId,amount);
            }
            break;

        case 5:
            printf("Enter table ID to pay the bill:");
            scanf("%s",&tableId);
             if(!isExistTable(tableId))
            {
                printf("There is no table with the given id!!!");
            }
            else{
                payBill(tableId);
            }
            break;

        case 6:
            printf("Enter table ID: ");
            scanf("%s",&tableId);
            printf("Enter food ID to update: ");
            scanf("%d",&foodId);
             if(!isExistTable(tableId))
            {
                printf("There is no table with the given id!!!");
            }
            else{
                cancelOrder(tableId,foodId);
            }
            break;

        }
    }while(selection !=7);
    return 0;
}
