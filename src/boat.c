/*

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


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../include/boat.h"

// CONSTANTS --------------------------------------------------------------------------------------

#define MAX_BOAT_NAME_LENGTH 128 // +1 for null terminator: s[127] + \0
#define MACRO
#define MARINA_MAX_BOAT_CAPACITY 120

// TYPEDEFS ---------------------------------------------------------------------------------------

typedef enum {
    slip,
    land,
    trailor,
    storage,
    no_place
} PlaceType;


typedef struct {
  char name[MAX_BOAT_NAME_LENGTH]; 
  uint8_t length;
  PlaceType place; 
  double moneyOwed; // double cus it can get expensive to own a boat 
} Boat;

// to be used in main.c
extern Boat *boatInventory[MARINA_MAX_BOAT_CAPACITY];
extern int boatCount;

// STRING UTILITY -----------------------------------------------------

//-------------------------------------------------------------------------------------------------
//----Convert a string to a place
PlaceType StringToPlaceType(char * PlaceString) {

    if (!strcasecmp(PlaceString,"slip")) {
        return(slip);
    }
    if (!strcasecmp(PlaceString,"land")) {
        return(land);
    }
    if (!strcasecmp(PlaceString,"trailor")) {
        return(trailor);
    }
    if (!strcasecmp(PlaceString,"storage")) {
        return(storage);
    }
    return(no_place);
}
//-------------------------------------------------------------------------------------------------
//----Convert a place to a string
char * PlaceToString(PlaceType Place) {

    switch (Place) {
        case slip:
            return("slip");
        case land:
            return("land");
        case trailor:
            return("trailor");
        case storage:
            return("storage");
        case no_place:
            return("no_place");
        default:
            printf("How the faaark did I get here?\n");
            exit(EXIT_FAILURE);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
