#pragma once

#include <stdint.h>
#include <string>

static constexpr const char* const AvailableExtensions[] = { "cpp", "c", "h", "hpp"};

enum class EExtensionCheckResult : uint8_t
{
	NotAvaliable,
	Avaliable,
	Folder
};

struct FReaderResult
{
	int TotalLines = 0;
	int BlankLines = 0;
	int CommentLines = 0;
	int CodeLines = 0;
	int ExecutionTime = 0;

	operator std::string() const
	{
		return "Total lines: " + std::to_string(TotalLines) + "\n" +
			"Blank lines: " + std::to_string(BlankLines) + "\n" +
			"Comment lines: " + std::to_string(CommentLines) + "\n" +
			"Code lines: " + std::to_string(CodeLines) + "\n" +
			"Execution time: " + std::to_string(ExecutionTime) + "ms";
	}
	
	friend std::ostream& operator<<(std::ostream& os, const FReaderResult& rr)
	{
		os << (std::string)rr;
		return os;
	}

	FReaderResult& operator+(const FReaderResult& other)
	{
		TotalLines += other.TotalLines;
		BlankLines += other.BlankLines;
		CommentLines += other.CommentLines;
		CodeLines += other.CodeLines;
		ExecutionTime += other.ExecutionTime;

		return *this;
	}

	FReaderResult& operator+=(const FReaderResult& other)
	{
		return *this + other;
	}
};

class Reader
{
public:
	Reader() {};

	Reader(std::string path) : PathToFolder(path) {};	
	
	void WriteAvailableExtensions();

	FReaderResult ReadItem(std::string ItemName, bool bFullFileName = false);
	//@param
	//	bFullFileName - if false, fileName will be added to the PathToFolder
	FReaderResult ReadFile(std::string fileName, bool bFullFileName = false);
	FReaderResult ParseDirectory(const std::string& fileName);

	bool WriteToFile(const FReaderResult& ToWrite, std::string Path, bool bFullFileName = false);

private:
	EExtensionCheckResult CheckExtension(std::string fileName);
	std::string ReverseString(const std::string& ToReverse);
	// Doesn't directly modify the file,
	// the std::getline does
	FReaderResult ParseLines(std::ifstream& file);

	const std::string PathToFolder = R"*(D:\SoftServe\Task3\)*";
};
