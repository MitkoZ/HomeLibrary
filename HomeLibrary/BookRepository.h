#pragma once
#include "Book.h"
#include <fstream>
#include <vector>
class BookRepository
{
public:
	BookRepository(std::string filePath);
	~BookRepository();
	void Insert(Book* book);
	void Remove(Book* book);
	Book* GetById(int id);
	Book* GetByName(std::string name);
	std::vector<Book> GetAll();
private:
	std::string filePath;
	void WriteEntity(Book* book, std::ofstream* outputFileStream);
	int PopulateEntity(Book* book, std::ifstream* inputfileStream);
	int GetNextId();
};

