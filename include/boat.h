/*                      -- boat.h -- 
 * HEADER FILE - 
 * declares 
 * 
 */


#include <stdint.h>

// CONSTANTS --------------------------------------------------------------------------------------

#define MAX_BOAT_NAME_LENGTH 128 // +1 for null terminator: s[127] + \0
#define MARINA_MAX_BOAT_CAPACITY 120

// TYPEDEFS ---------------------------------------------------------------------------------------

typedef enum {
    slip,
    land,
    trailor,
    storage,
    no_place
} PlaceType;

typedef union {
    int slipNumber;         // 1-85
    char bayLetter;         // A-Z
    char licenseTag[MAX_LICENSE_TAG_LENGTH];
    int storageNumber;      // 1-50
} PlaceInfo;


typedef struct {
  char name[MAX_BOAT_NAME_LENGTH]; 
  uint8_t length;           // uint8_t spans the range of valid boat lengths, saves memory space.
  PlaceType place; 
  double moneyOwed;         // double cus it can get expensive to own a boat, also a real number.
  PlaceInfo extraInfo;      // depending on the PlaceType.
} Boat;

// to be used in main.c
extern Boat *boatInventory[MARINA_MAX_BOAT_CAPACITY];
extern int boatCount;


