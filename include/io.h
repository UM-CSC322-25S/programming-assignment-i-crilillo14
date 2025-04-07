/*                         -- io.h --
 *
 * HEADER FILE - 
 * don't really need to create a header file but I feel it's more
 * organized this way.
 *
 * io.c : Functions that pertain to writing and reading to csv files.
 *
 */



#ifndef IO_H
#define IO_H

int loadBoatsFromFile(const char *filename);
int saveBoatsToFile(const char *filename);

#endif // IO_H
