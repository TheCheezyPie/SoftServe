#pragma once

#include <stdlib.h>
#include <string.h>
#define MY_DEBUG

typedef const char* String;

/* Initializes list */
void StringListInit(char*** list);
/* Destroy list and set pointer to NULL. */
void StringListDestroy(char*** list);

/* Inserts value at the end of the list. */
/* IS A COPY FUNCTION */
void StringListAdd(char**& list, String str);
/* Removes all occurrences of str in the list. */
void StringListRemove(char** list, String str);

/* Returns the number of items in the list. */
int StringListSize(char** list);
/*	Returns the index position of the first occurrence of str in the list.
	Returns -1 if str is not found.*/ 
int StringListIndexOf(char** list, String str);

/* Removes duplicate entries from the list. */
void StringListRemoveDuplicates(char** list);
/* Replaces every occurrence of the before, in each of the string lists's strings, with after. */
void StringListReplaceInStrings(char** list, String before, String after);
/* Sorts the list of strings in ascending order
	Selection sort*/
void StringListSort(char** list);

#ifdef MY_DEBUG
void PrintList(char** list);
#endif // MY_DEBUG