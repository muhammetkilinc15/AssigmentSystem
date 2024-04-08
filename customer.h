#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED
#include "common.h"

void newOrder(char tableId[],int foodID,int amount);
void updateAmount(char tableID[],int foodID,int amount);
void payBill(char tableId[]);
void cancelOrder(char tableId[],int foodId);

#endif // CUSTOMER_H_INCLUDED

