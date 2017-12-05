#pragma once
#include <string>
class Book
{
public:
	~Book();
	Book();
	Book(std::string name, std::string authorName, std::string genre, int releaseDate);
public:
	int Id;
	std::string Name;
	std::string AuthorName;
	std::string Genre;
	int ReleaseDate;
};

