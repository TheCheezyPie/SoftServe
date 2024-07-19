
#include <iostream>
#include "SoftServe.h"
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"

void Task1()
{
	char*** List = (char***)malloc(8);
	if (List)
	{
		StringListInit(List);
		StringListAdd(*List, "Hello");
		StringListAdd(*List, "World1");
		StringListAdd(*List, "World2");
		StringListAdd(*List, "World3");
		StringListAdd(*List, "World4");
		StringListAdd(*List, "World5");
		StringListAdd(*List, "World6");
		StringListRemove(*List, "World3");

		StringListReplaceInStrings(*List, "World", "Hell");

		StringListSize(*List);

		free(List);
	}
}

void Task2()
{
	AnyType Any = 5.f;
	std::cout << Any.ToInt() << std::endl;
}

void Task3()
{
	Reader Reader;
	FReaderResult Result = Reader.ReadItem("input.cpp");
	std::cout << Result;
}

int main()
{
	//Task1();
	//Task2();
	Task3();

	std::cin.get();
	return 0;
}

