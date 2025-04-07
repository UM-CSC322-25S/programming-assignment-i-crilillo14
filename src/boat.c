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

#include "../include/boat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
//-------------------------------------------------------------------------------------------------

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
