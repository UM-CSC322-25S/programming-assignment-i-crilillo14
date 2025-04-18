/*                       -- boat.c --
 * Implements the core functionality for managing boat data structures,
 * including adding, removing, finding, sorting, and updating monthly charges.
 *

 ALL FUNCTIONALITY FOR BOATS IN THIS FILE

Definition of a boat (as relevant to this program):

 - The name of the boat (up to 127 characters long, not containing a comma)
 - The length in feet - up to 100' (hint: choose a suitable data type)
 - Which type of place (slip/land/trailor/storage) (hint: use an enum like this)

typedef enum {
    slip,
    land,
    trailor,
    storage,
    no_place
} PlaceType;

Depending on the type, extra relevant information (use a union):
  Slip - the slip number 1-85
  Land - the bay letter, A-Z
  Trailor - the trailor license tag
  Storage - the storage space number 1-50

 - The amount of money owed to the marina
 */

#include "../include/boat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define global variables for boat inventory
Boat *boatInventory[MARINA_MAX_BOAT_CAPACITY];
int boatCount = 0;

// Monthly rates per foot
const double SLIP_RATE = 12.50;
const double LAND_RATE = 14.00;
const double TRAILOR_RATE = 25.00;
const double STORAGE_RATE = 11.20;

// STRING UTILITY
// --------------------------------------------------------------------------------

// { given by professor }
//----Convert a string to a place
PlaceType StringToPlaceType(char *PlaceString) {

  if (!strcasecmp(PlaceString, "slip")) {
    return (slip);
  }
  if (!strcasecmp(PlaceString, "land")) {
    return (land);
  }
  if (!strcasecmp(PlaceString, "trailor")) {
    return (trailor);
  }
  if (!strcasecmp(PlaceString, "storage")) {
    return (storage);
  }
  return (no_place);
}
//----------------------------------------------------------------------------------

// { given by professor }
//----Convert a place to a string
char *PlaceToString(PlaceType Place) {

  switch (Place) {
  case slip:
    return ("slip");
  case land:
    return ("land");
  case trailor:
    return ("trailor");
  case storage:
    return ("storage");
  case no_place:
    return ("no_place");
  default:
    printf("How the faaark did I get here?\n");
    exit(EXIT_FAILURE);
    break;
  }
}

// CORE CLASS FUNCTIONALITY
// ------------------------------------------------------------------------

// Initialize the boat inventory array and count.
// Resetting boatCount here is redundant but dont wanna risk it
// also setting to null cus I dont wanna risk it
void initializeBoatInventory(void) {
    // boatCount = 0; // Already initialized globally
    for (int i = 0; i < MARINA_MAX_BOAT_CAPACITY; i++) {
        boatInventory[i] = NULL;
    }
}

// custom comparison used by qsort { alphabetical, case-insensitive }
static int compareBoats(const void *a, const void *b) {
    Boat *boatA = *(Boat **)a;
    Boat *boatB = *(Boat **)b;
    return strcasecmp(boatA->name, boatB->name);
}

// thank god I didn't have to implement sorting.
// wouldn't have been that bad but still good. 
void sortInventory(void) {
    if (boatCount > 1) {
        qsort(boatInventory, boatCount, sizeof(Boat *), compareBoats);
    }
}

// Adds a boat to the inventory, 
// checking for duplicates,
// re-sorts the list
void addBoat(Boat *boat) {
  // IMPORTANT, if addign doesn't work, the boat memory has to be freed,

    if (boatCount >= MARINA_MAX_BOAT_CAPACITY) {
        printf("Inventory full, cannot add more boats.\n");
        free(boat); // Free the boat that couldn't be added
        return;
    }

    // check if it's already there
    // it might make more sense to use the license but it's not like 
    // this is required functionality either.
    if (findBoat(boat->name) != -1) {
        printf("Error: A boat named '%s' already exists in the inventory.\n", boat->name);
        free(boat);
        return;
    }

    // add the boat and sort
    boatInventory[boatCount++] = boat;
    sortInventory();
}

// finds boat by name
// Returns the index if found or -1 if not
int findBoat(const char *name) {
    for (int i = 0; i < boatCount; i++) {
        if (strcasecmp(boatInventory[i]->name, name) == 0) {
            return i;
        }
    }
    return -1;
}


// remove by name, not by index. 
// free mem of boat and shift whole array (like in csc220)
int removeBoat(const char *name) {
    int index = findBoat(name);
    if (index == -1) {
        return -1;
    }

    free(boatInventory[index]);

    // shift
    for (int i = index; i < boatCount - 1; i++) {
        boatInventory[i] = boatInventory[i + 1];
    }
    boatInventory[boatCount - 1] = NULL;
    boatCount--;
    return 0;
}

// was going to implement a more complicated solution
// keeping track of boatcount is so much easier. 
// this is more like a wrapper
int getBoatCount(void) {
    return boatCount;
}

// Returns a pointer to the boat at index or null
Boat *getBoatAt(int index) {
    if (index < 0 || index >= boatCount) {
        return NULL;
    }
    return boatInventory[index];
}

// Update the monthly charge for a single boat by adding length * rate
// where the rate depends on the boat's place [CONSTANTS UP TOP]
void updateMonthlyCharges(Boat *boat) {
    double rate = 0.0;
    switch (boat->place) {
        case slip:
            rate = SLIP_RATE;
            break;
        case land:
            rate = LAND_RATE;
            break;
        case trailor:
            rate = TRAILOR_RATE;
            break;
        case storage:
            rate = STORAGE_RATE;
            break;
        default:
            rate = 0.0;
            break;
    }
    boat->moneyOwed += boat->length * rate;
}


// Free all allocated boats. AFTER WRITING TO CSV!!!!
void freeAllBoats(void) {
    for (int i = 0; i < boatCount; i++) {
        free(boatInventory[i]);
        boatInventory[i] = NULL;
    }
    boatCount = 0;
}
