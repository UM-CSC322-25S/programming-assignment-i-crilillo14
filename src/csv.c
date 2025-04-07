/*
 *  csv.c -- csv file functionality - boils down to read and write ops. 
 */

#include "../include/csv.h"
#include "../include/boat.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Helper function to remove a trailing newline character from a string.
static void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Parses a CSV-formatted line and returns a pointer to a newly allocated Boat struct.
// Expected CSV format: 
//   name,length,place,,mextraInfo,moneyOwed
//   OK SO I MIXED UP THE ORDER BETWEEN MEMORY ORDER AND CSV, BUT IT STILL WORKS
//   DON'T TOUCH
// For extra:
//   slip      -> slip number (integer)
//   land      -> bay letter (character)
//   trailor   -> license tag (string)
//   storage   -> storage number (integer)
//
//   MOST IMPORTANT FN IN THE PROGRAM
Boat *CSVparseLine(const char *line) {
    // Duplicate the line (since strtok modifies the string)
    char *lineCopy = strdup(line);
    if (!lineCopy) return NULL;
    
    Boat *boat = malloc(sizeof(Boat));
    if (!boat) {
        free(lineCopy);
        return NULL;
    }
    
    char *token = NULL;
    // Token 1: Boat name
    token = strtok(lineCopy, ",");
    if (!token) { free(boat); free(lineCopy); return NULL; }
    strncpy(boat->name, token, MAX_BOAT_NAME_LENGTH - 1);
    boat->name[MAX_BOAT_NAME_LENGTH - 1] = '\0';
    
    // Token 2: Boat length
    token = strtok(NULL, ",");
    if (!token) { free(boat); free(lineCopy); return NULL; }
    boat->length = (uint8_t)atoi(token);
    
    // Token 3: Place type string
    token = strtok(NULL, ",");
    if (!token) { free(boat); free(lineCopy); return NULL; }
    boat->place = StringToPlaceType(token);
    
    // Token 4: Extra info (depends on placeType)
    token = strtok(NULL, ",");
    if (!token) { 
      free(boat); 
      free(lineCopy); 
      return NULL;
    }

    // according to the placetype, set extraInfo
    switch (boat->place) {
        case slip:
            boat->extraInfo.slipNumber = (uint8_t)atoi(token);
            break;
        case land:
            boat->extraInfo.bayLetter = token[0];
            break;
        case trailor:
            strncpy(boat->extraInfo.licenseTag, token, MAX_LICENSE_TAG_LENGTH - 1);
            boat->extraInfo.licenseTag[MAX_LICENSE_TAG_LENGTH - 1] = '\0';
            break;
        case storage:
            boat->extraInfo.storageNumber = (uint8_t)atoi(token);
            break;
        default:
            break;
    }
    
    // Token 5: Money owed
    token = strtok(NULL, ",");
    if (!token) { free(boat); free(lineCopy); return NULL; }
    boat->moneyOwed = atof(token);
    
    free(lineCopy);
    return boat;
}

// Loads boats from a CSV file.
// For each nonempty line in the file, a Boat is created and added to the inventory.
// Returns 0 on success, or -1 if there was an error opening the file.
int loadBoatsFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file for reading");
        return -1;
    }
    
    char line[512];   // TODO: figure out exactly how much space I should give the buffer
    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);
        if (strlen(line) == 0)
            continue;  // Skip empty lines
        Boat *boat = CSVparseLine(line);
        if (boat) {
            addBoat(boat);
        }
    }
    fclose(fp);
    return 0;
}

// Saves the current boat inventory to a CSV file.
// Each boat is written in the format: name,length,place,extra,moneyOwed
// Returns 0 on success, or -1 if there was an error opening the file.
int saveBoatsToFile(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error opening file for writing");
        return -1;
    }
    
    for (int i = 0; i < getBoatCount(); i++) {
        Boat *boat = getBoatAt(i);
        switch (boat->place) {
            case slip:
                fprintf(fp, "%s,%d,%s,%d,%.2f\n",
                        boat->name,
                        boat->length,
                        PlaceToString(boat->place),
                        boat->extraInfo.slipNumber,
                        boat->moneyOwed);
                break;
            case land:
                fprintf(fp, "%s,%d,%s,%c,%.2f\n",
                        boat->name,
                        boat->length,
                        PlaceToString(boat->place),
                        boat->extraInfo.bayLetter,
                        boat->moneyOwed);
                break;
            case trailor:
                fprintf(fp, "%s,%d,%s,%s,%.2f\n",
                        boat->name,
                        boat->length,
                        PlaceToString(boat->place),
                        boat->extraInfo.licenseTag,
                        boat->moneyOwed);
                break;
            case storage:
                fprintf(fp, "%s,%d,%s,%d,%.2f\n",
                        boat->name,
                        boat->length,
                        PlaceToString(boat->place),
                        boat->extraInfo.storageNumber,
                        boat->moneyOwed);
                break;
            default:
                break;
        }
    }
    
    fclose(fp);
    return 0;
}

