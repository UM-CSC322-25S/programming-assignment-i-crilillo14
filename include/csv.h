/*                         -- csv.h --
 * HEADER FILE - Declares functions for reading from and writing to CSV files,
 * specifically for boat data persistence.
 *
 * don't really need to create a header file but I feel it's more
 * organized this way.
 *
 * csv.c : Functions that pertain to writing and reading to csv files.
 *
 */

#ifndef CSV_H
#define CSV_H

#include "boat.h" // to be able to use boat stuff
#include <stdio.h>

int loadBoatsFromFile(const char *filename);    // load from csv to boatInventory
int saveBoatsToFile(const char *filename);      // write boats to csv
Boat *CSVparseLine(const char *line);           // csv line to boat obj - less straightforward.

#endif
