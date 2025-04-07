/*                         -- menu.h --
 * HEADER FILE - Declares functions related to the command-line user interface,
 * such as the main menu loop and inventory display.
 */

#ifndef MENU_H
#define MENU_H

#include "boat.h" // Include boat.h for access to boat functions/data

// runs main loop
void runMenu(void);
// shows current inventory when i/I are entered
void printInventory(void);


#endif // MENU_H
