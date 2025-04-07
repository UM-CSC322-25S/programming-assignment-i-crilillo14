/*
 *        -- Main for fleet management program -- 
 *
 * Breakdown of the structure of the project :
 *
 * boat.c
 *
 *
 *
 */


#include "../include/boat.h"
#include "../include/csv.h"
#include "../include/menu.h"
#include <stdio.h>
#include <stdlib.h>

// Declaration of the menu function from menu.c
// void runMenu(); // Declaration should be in menu.h

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <BoatData.csv>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    // Initialize the boat inventory.
    initializeBoatInventory();
    
    // Load boats from the CSV file provided as a command-line argument.
    if (loadBoatsFromFile(argv[1]) != 0) {
        printf("Failed to load boat data from file: %s\n", argv[1]);
    }
    
    printf("Welcome to the Boat Management System\n");
    printf("-------------------------------------\n");
    
    // menu.c func for main loop
    runMenu();
    
    // after exiting, save boatInventory back to csv
    if (saveBoatsToFile(argv[1]) != 0) {
        printf("Failed to save boat data to file: %s\n", argv[1]);
    }
    
    // Free all allocated boat memory.
    freeAllBoats();
    
    printf("\nExiting the Boat Management System\n");
    return EXIT_SUCCESS;
}

