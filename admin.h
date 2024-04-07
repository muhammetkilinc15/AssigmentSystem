#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED
#include "common.h"

void createTable(char tableID[]);
void deleteTable(char tableID[]);
void checkNewOrder();
void showAllInvocies();
void updateFood(int foodID,float fee);
#endif // ADMIN_H_INCLUDED
