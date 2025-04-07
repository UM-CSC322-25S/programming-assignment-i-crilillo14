#ifndef MENU_H
#define MENU_H

#include "boat.h" // Include boat.h for access to boat functions/data

// Runs the main interactive menu loop.
void runMenu(void);

// Prints the current boat inventory.
// Note: If only used within menu.c, this declaration isn't strictly necessary here.
// void printInventory();

#endif // MENU_H
