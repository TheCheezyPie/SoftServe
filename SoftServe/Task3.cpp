#include "Task3.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <future>

using std::cout, std::endl;

static std::mutex mtx;

FReaderResult Reader::ReadItem(std::string ItemName, bool bFullFileName)
{
	if (!bFullFileName)
	{
		ItemName = PathToFolder + ItemName;
	}

	//cout << "------Reading file: " << fileName << endl;

	switch (CheckExtension(ItemName))
	{
	case EExtensionCheckResult::Avaliable:
		ReadFile(ItemName, true);
		break;
	case EExtensionCheckResult::NotAvaliable:
	{
		//cout << "Wrong file extension!" << endl;
		WriteAvailableExtensions();
		return FReaderResult();
		break;
	}
	case EExtensionCheckResult::Folder:
	{
		return ParseDirectory(ItemName);
		break;
	}
	default:
		break;
	}

	return FReaderResult();
}

FReaderResult Reader::ReadFile(std::string fileName, bool bFullFileName)
{
	std::lock_guard<std::mutex> lock(mtx);

	using namespace std::chrono;
	auto start = high_resolution_clock::now();

	if (!bFullFileName)
	{
		fileName = PathToFolder + fileName;
	}		

	cout << "------Reading file: " << fileName << endl;

	std::ifstream file(fileName);
	if (!file.is_open())
	{
		//cout << "Error: file" << fileName << " not found" << endl;
		return FReaderResult();
	}

	//cout << "File opened successfully" << std::endl;

	FReaderResult Result = ParseLines(file);

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	Result.ExecutionTime = duration.count();

	file.close();

	return Result;
}

void Reader::WriteAvailableExtensions()
{
	cout << "Available extensions:";
	for (auto AvailableExtension : AvailableExtensions)
	{
		cout << " ." << AvailableExtension;
	}
	cout << endl;
}

FReaderResult Reader::ParseDirectory(const std::string& fileName)
{
	using namespace std::filesystem;
	FReaderResult Result;

	std::vector<std::future<FReaderResult>> futures;
	if (exists(fileName) && is_directory(fileName))
	{
		for (const auto& entry : recursive_directory_iterator(fileName))
		{
			if (is_regular_file(entry.status()))
			{
				futures.emplace_back
				(
					std::async(std::launch::async, &Reader::ReadFile, this, entry.path().string(), true)
				);
			}
		}
		for (auto& future : futures)
		{
			Result += future.get();
		}
		return Result;
	}
	else
	{
		cout << "Error: directory " << fileName << " not found" << endl;
		return FReaderResult();
	}
}

EExtensionCheckResult Reader::CheckExtension(std::string fileName)
{	
	std::string ReversedFileExtension;
	ReversedFileExtension.resize(MaxExtensionLength);
	const int FileNameLength = fileName.length() - 1;

	bool bLongerThanMax = false;

	for (int i = FileNameLength; i >= 0; i--)
	{
		// if the extension is longer than the available ones
		if (FileNameLength - i >= MaxExtensionLength)
		{
			bLongerThanMax = true;
		}

		char c = fileName[i];
		if (c != '.')
		{
			if (!bLongerThanMax)
			{
				ReversedFileExtension[FileNameLength - i] = c;
			}
		}
		else
		{
			if (!bLongerThanMax)
			{
				ReversedFileExtension[FileNameLength - i] = '\0';
			}
			else
			{
				return EExtensionCheckResult::NotAvaliable;
			}
			break;
		}

		// If there is no extension (only folder)
		if (i == 0)
		{
			return EExtensionCheckResult::Folder;
		}
	}

	std::string NormalFileExtension;
	NormalFileExtension.resize(MaxExtensionLength);
	int ExtensionLength = ReversedFileExtension.length();
	NormalFileExtension[ExtensionLength] = '\0';

	for (int i = 0; i < ExtensionLength; i++)
	{
		char c = ReversedFileExtension[(ExtensionLength - 1) - i];
		NormalFileExtension[i] = c;
	}

	for (auto AvailableExtension : AvailableExtensions)
	{
		if (NormalFileExtension.compare(AvailableExtension) != 0)
		{
			return EExtensionCheckResult::Avaliable;
		}
	}

	return EExtensionCheckResult::NotAvaliable;
}

FReaderResult Reader::ParseLines(std::ifstream& file)
{
	FReaderResult Result;

	// Used to account for multiline comments ( /**/ )
	int MultilineStartIndex = -1;

	std::string Line;
	while (std::getline(file, Line))
	{
		Result.TotalLines++;

		if (Line.empty())
		{
			Result.BlankLines++;
		}
		else
		{
			bool bAccountedForLine = false;

			for (int i = 0; i < Line.length(); i++)
			{
				if (Line[i] == ' ' || Line[i] == '\t')
				{
					continue;
				}
				else if (Line[i] == '/')
				{
					if (i + 1 < Line.length())
					{
						if (Line[i + 1] == '/')
						{
							Result.CommentLines++;
							break;
						}
						else if (Line[i + 1] == '*')
						{
							Result.CommentLines++;
							MultilineStartIndex = Result.TotalLines;
							i++;
							continue;
						}
					}
					Result.CodeLines++;
				}
				else if (Line[i] == '*')
				{
					if (i + 1 < Line.length())
					{
						if (Line[i + 1] == '/')
						{
							if (MultilineStartIndex != Result.TotalLines)
							{
								Result.CommentLines++;
							}
							MultilineStartIndex = -1;
							i++;
							continue;
						}
					}
					if (!bAccountedForLine)
					{
						Result.CodeLines++;
					}
				}
				else
				{
					if (MultilineStartIndex == -1 && !bAccountedForLine)
					{
						Result.CodeLines++;
						bAccountedForLine = true;
					}
				}
			}
		}
	}

	return Result;
}

bool Reader::WriteToFile(const FReaderResult& ToWrite, std::string Path, bool bFullFileName)
{
	if (!bFullFileName)
	{
		Path = PathToFolder + Path;
	}

	std::ofstream file(Path);

	if (file.is_open())
	{
		file << ToWrite;
		file.close();
		return true;
	}

	return false;
}
