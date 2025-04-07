/*
 *
 * menu.c : UI stuff for command line interface. 
 *
 * Not too complicated, just contains the functionality for user interactivity.
 * Handles all functions from the user with csv and boat functions. 
 * Now that I think about it, this probably should've been in main...
 *
*/

#include "../include/menu.h"
#include "../include/boat.h"
#include "../include/csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INPUT_SIZE 256 // should def make sure this covers all cases.

// Prints the current boat inventory in a formatted table.
void printInventory(void) {
    if (getBoatCount() == 0) {
        printf("No boats in the inventory.\n");
        return;
    }
    for (int i = 0; i < getBoatCount(); i++) {
        Boat *boat = getBoatAt(i);
        // to be completely honest, 
        // got all the padding and alignment from outside sources.

        // name padded to 20 characters
        printf("%-20s", boat->name);
        // Boat length in feet (with apostrophe)
        printf("%3d' ", boat->length);
        // Place type (left-justified in an 8-character field)
        printf("%-8s", PlaceToString(boat->place));
        // Extra info based on the placeType:
        switch (boat->place) {
            case slip:
                printf("   #%4d   ", boat->extraInfo.slipNumber); 
                break;
            case land:
                printf(" %7c   ", boat->extraInfo.bayLetter);  
                break;
            case trailor:
                printf("   %8s", boat->extraInfo.licenseTag);    
                break;
            case storage:
                printf("   #%4d   ", boat->extraInfo.storageNumber);
                break;
            default:
                printf("           "); 
                break;
        }
        // Money owed formatted with 2 decimal places, right aligned in its field
        printf(" Owes $%g\n", boat->moneyOwed);
    }
}


// -----------------------------------------------------------------------------

// Runs the main menu loop, processing user commands.
void runMenu(void) {
    char input[INPUT_SIZE];
    char option;
    
    while (1) {
        printf("\n(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : ");
        if (!fgets(input, sizeof(input), stdin))
            break;
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) == 0)
            continue;
        
        option = tolower(input[0]);
        if (option == 'x') {
            break;
        }

        switch (option) {
            case 'i': {
                printInventory();
                break;
            }
            case 'a': {
                printf("Please enter the boat data in CSV format                 : ");
                if (!fgets(input, sizeof(input), stdin))
                    break;
                input[strcspn(input, "\n")] = '\0';
                Boat *boat = CSVparseLine(input);
                if (boat) {
                    addBoat(boat);
                } else {
                    printf("Error parsing boat data.\n");
                }
                break;
            }
            case 'r': {
                printf("Please enter the boat name                               : ");
                if (!fgets(input, sizeof(input), stdin))
                    break;
                input[strcspn(input, "\n")] = '\0';
                if (removeBoat(input) == -1) {
                    printf("No boat with that name\n");
                }
                break;
            }
            case 'p': {
                printf("Please enter the boat name                               : ");
                if (!fgets(input, sizeof(input), stdin))
                    break;
                input[strcspn(input, "\n")] = '\0';
                int index = findBoat(input);
                if (index == -1) {
                    printf("No boat with that name\n");
                    break;
                }
                Boat *boat = getBoatAt(index);
                printf("Please enter the amount to be paid                       : ");
                if (!fgets(input, sizeof(input), stdin))
                    break;
                double payment = atof(input);
                if (payment > boat->moneyOwed) {
                    printf("That is more than the amount owed, $%.2f\n", boat->moneyOwed);
                } else {
                    boat->moneyOwed -= payment;
                }
                break;
            }
            case 'm': {
                // Update monthly charges
                for (int i = 0; i < getBoatCount(); i++) {
                    updateMonthlyCharges(getBoatAt(i));
                }
                break;
            }
            default:
                printf("Invalid option %c\n", input[0]);
                break;
        }
    }
}
