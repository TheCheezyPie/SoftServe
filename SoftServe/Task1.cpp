#include "Task1.h"

// DELETE THIS
#include <iostream>
using namespace std;
//

void StringListInit(char*** list)
{
	char** NewList = (char**)malloc(2 * sizeof(char*));
	if (NewList)
	{
		*list = NewList;
		NewList[0] = nullptr;
		auto LastElem = (char*)malloc(1 * sizeof(char));
		if (LastElem)
		{
			LastElem[0] = '\0';
			NewList[1] = LastElem;
		}
	}
}

void StringListDestroy(char*** list)
{
	if (*list)
	{
		for (int i = 0;; i++)
		{
			if ((*list)[i])
			{
				if ((*list)[i][0] == '\0')
				{
					free((*list)[i]);
					break;
				}
				free((*list)[i]);
			}
		}
		free(*list);
		*list = nullptr;
	}
}

void StringListAdd(char**& list, String str)
{
	if (strlen(str) == 0)
	{
		return;
	}

	if (list)
	{
		cout << "--------Adding " << str << endl;
		for (int i = 0;; i++)
		{
			if (list[i])
			{
				if (list[i][0] == '\0')
				{
					cout << "end of the list at " << i << endl;
					break;
				}
				continue;
			}
			else
			{
				size_t s_size = strlen(str) + 1;
				char* NewElem = (char*)malloc(s_size * sizeof(char));
				if (NewElem)
				{
					strcpy_s(NewElem, s_size, str);
					list[i] = NewElem;
					return;
				}
				//else
				//{
				//	// WRITE ERROR SOMEHOW
				//	//exit(EXIT_FAILURE);
				//}
			}
		}

		// Reallocating memory like a vector
		cout << "--------Reallocating\n";

		int OldSize = StringListSize(list);
		int NewSize = OldSize * 2;

		cout << "OldSize: " << OldSize << " NewSize: " << NewSize << endl;

		char** NewList = (char**)realloc(list, (NewSize) * sizeof(char*));

		if (NewList)
		{
			list = NewList;

			for (int i = OldSize; i < NewSize; i++)
			{
				NewList[i] = nullptr;
			}

			NewList[NewSize] = (char*)malloc(1 * sizeof(char));
			if (NewList[NewSize])
			{
				*NewList[NewSize] = '\0';
			}

			StringListAdd(NewList, str);
		}
		//else
		//{
		//	// WRITE ERROR SOMEHOW
		//	//exit(EXIT_FAILURE);
		//}
	}
}

void StringListRemove(char** list, String str)
{
	if (list)
	{
		int index = StringListIndexOf(list, str);
		if (index != -1 && list[index])
		{
			free(list[index]);
			list[index] = nullptr;

			for (int i = index + 1;; i++)
			{
				if (list[i])
				{
					if (list[i][0] == '\0')
					{
						return;
					}
					list[i - 1] = list[i];
					list[i] = nullptr;
				}
				else
				{
					return;
				}
			}
		}
	}
}

int StringListSize(char** list)
{
	if (list)
	{
		for (int i = 0;; i++)
		{
			if (list[i])
			{
				if (list[i][0] == '\0')
				{
					cout << "end of the list when counting size " << i << endl;
					return i;
				}
			}
			else
			{
				cout << "empty element; size " << i << endl;
				return i;
			}
		}
	}

	return 0;
}

int StringListIndexOf(char** list, String str)
{
	if (list)
	{
		for (int i = 0;; i++)
		{
			if (list[i])
			{
				if (list[i][0] == '\0')
				{
					cout << "end of the list when searching " << i << endl;
					return -1;
				}
				else if (strcmp(list[i], str) == 0)
				{
					cout << "found " << str << " at " << i << endl;
					return i;
				}
			}
			else
			{
				cout << "empty element; not found " << str << endl;
				return -1;
			}
		}
	}
	return 0;
}

void StringListRemoveDuplicates(char** list)
{
	if (list)
	{
		for (int i = 0;; i++)
		{
			if (list[i])
			{
				if (list[i][0] == '\0')
				{
					return;
				}
				for (int j = i + 1;; j++)
				{
					if (list[j])
					{
						if (list[j][0] == '\0')
						{
							break;
						}
						if (strcmp(list[i], list[j]) == 0)
						{
							free(list[j]);
							list[j] = nullptr;
						}
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				return;
			}
		}
	}
}

void StringListReplaceInStrings(char** list, String before, String after)
{
	if (list)
	{
		for (int i = 0;; i++)
		{
			if (list[i])
			{
				if (list[i][0] == '\0')
				{
					// end of the list
					return;
				}
				char* found = strstr(list[i], before);
				if (found)
				{
					size_t before_len = strlen(before);
					size_t after_len = strlen(after);
					size_t new_len = strlen(list[i]) - before_len + after_len + 1;
					char* NewElem = (char*)malloc(new_len * sizeof(char));
					if (NewElem)
					{
						strncpy_s(NewElem, new_len, list[i], found - list[i]);
						strcat_s(NewElem, new_len, after);
						strcat_s(NewElem, new_len, found + before_len);
						free(list[i]);
						list[i] = NewElem;
					}
				}
			}
			else
			{
				// empty element -> end of the elements
				return;
			}
		}
	}
}

void StringListSort(char** list)
{
	if (list)
	{
		int size = StringListSize(list);
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (strcmp(list[i], list[j]) > 0)
				{
					char* temp = list[i];
					list[i] = list[j];
					list[j] = temp;
				}
			}
		}
	}
}

#ifdef MY_DEBUG
void PrintList(char** list)
{
	if (list)
	{
		cout << "--------Printing list\n";
		for (int i = 0;; i++)
		{
			if (list[i])
			{
				if (list[i][0] == '\0')
				{
					cout << "end of the list at " << i << endl;
					cout << "--------End of the list\n";
					return;
				}
				cout << list[i] << " at " << i << endl;
			}
			else
			{
				cout << "empty element at " << i << endl;
			}
		}
	}
}
#endif // MY_DEBUG