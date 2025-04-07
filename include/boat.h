/*                      -- boat.h --
 * HEADER FILE -
 * declares
 *
 */

#ifndef BOAT_H
#define BOAT_H

#include <stdint.h>

// CONSTANTS
// --------------------------------------------------------------------------------------

#define MAX_BOAT_NAME_LENGTH 128 // +1 for null terminator: s[127] + \0
#define MARINA_MAX_BOAT_CAPACITY 120

// ok, so there's no constraint for the licence tag length, but mallocing for
// *char instead of some char[] with fixed lenght is goign to be SO MUCH easier.
// from the given sample output, it seems that it's at most 6 chars, +1 for null
// terminator.
#define MAX_LICENSE_TAG_LENGTH 7

// TYPEDEFS
// ---------------------------------------------------------------------------------------

typedef enum { slip, land, trailor, storage, no_place } PlaceType;

/* For PlaceInfo:

Slip - the slip number 1-85 -> 7 bits, make it uint8 too
Land - the bay letter, A-Z -> char
Trailor - the trailor license tag -> no restriction imposed on length or format,
*char Storage - the storage space number 1-50 -> 6 bits, use uint8_t too.

*/

typedef union {
  uint8_t slipNumber; // 1-85
  char bayLetter;     // A-Z
  char licenseTag[MAX_LICENSE_TAG_LENGTH];
  uint8_t storageNumber; // 1-50
} PlaceInfo;

typedef struct {
  char name[MAX_BOAT_NAME_LENGTH];
  uint8_t length; // uint8_t spans the range of valid boat lengths, saves memory
                  // space.
  PlaceType place;
  double moneyOwed;    // double cus it can get expensive to own a boat, also a
                       // real number.
  PlaceInfo extraInfo; // depending on the PlaceType.
} Boat;

// to be used in main.c
extern Boat *boatInventory[MARINA_MAX_BOAT_CAPACITY];
extern int boatCount;

// FUNCTIONS ------------------------------------------------------------------------------
void initializeBoatInventory(void);
PlaceType StringToPlaceType(char *PlaceString);
char *PlaceToString(PlaceType Place);
void addBoat(Boat *boat);
int removeBoat(const char *name);
int findBoat(const char *name);
int getBoatCount(void);
Boat *getBoatAt(int index);
void updateMonthlyCharges(Boat *boat);
void freeAllBoats(void);


#endif // BOAT_H
