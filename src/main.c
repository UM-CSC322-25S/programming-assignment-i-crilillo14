/*
 *        -- Main for fleet management program -- 
 * 
 * Contains core logic of the program.
 * 
 * Breakdown of the structure of the project :
 * + boat.c - for boat functionality
 * + csv.c - for reading, writing, loading, saving, and parsing csv data.
 * + menu.c - for UI stuff and main logic. {could simply be contained within main too}
 *
 * main by itself does not do too much, just orchestrates everything and is the entrypoint
 * of the program.
 */


#include "../include/boat.h"
#include "../include/csv.h"
#include "../include/menu.h"
#include <stdio.h>
#include <stdlib.h>

// btw, boatInventory declared in boat.c


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <BoatData.csv>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    // Initialize the boat inventory.
    initializeBoatInventory();
    
    // Load boats from the CSV file specified in command line
    if (loadBoatsFromFile(argv[1]) != 0) {
        printf("Failed to load boat data from file: %s\n", argv[1]);
    }
    
    printf("Welcome to the Boat Management System\n");
    printf("-------------------------------------\n");
    
    // -- menu.c func for main loop --
    runMenu();
    
    // after exiting, save boatInventory back to csv
    if (saveBoatsToFile(argv[1]) != 0) {
        printf("Failed to save boat data to file: %s\n", argv[1]);
    }
    
    // Free all the boats, no mem leaks around here
    freeAllBoats();
    
    printf("\nExiting the Boat Management System\n");
    return EXIT_SUCCESS;
}

