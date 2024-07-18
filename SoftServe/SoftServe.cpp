
#include <iostream>
#include "SoftServe.h"
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"

void Task1()
{
	char*** list = (char***)malloc(8);
	if (list)
	{
		StringListInit(list);
		StringListAdd(*list, "Hello");
		StringListAdd(*list, "World1");
		StringListAdd(*list, "World2");
		StringListAdd(*list, "World3");
		StringListAdd(*list, "World4");
		StringListAdd(*list, "World5");
		StringListAdd(*list, "World6");
		StringListRemove(*list, "World3");

		StringListReplaceInStrings(*list, "World", "Hell");

		StringListSize(*list);

		free(list);
	}
}

void Task2()
{
	AnyType any = 5.f;
	std::cout << any.ToInt() << std::endl;
}

int main()
{
	//Task1();
	//Task2();

	Reader reader;
	FReaderResult result = reader.ReadFile("");
	std::cout << result;
	std::cout << std::endl << reader.WriteToFile(result, "result.txt");

	std::cin.get();
	return 0;
}

