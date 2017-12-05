#include "stdafx.h"
#include "BookRepository.h"
using namespace std;

BookRepository::BookRepository(std::string filePath) :filePath(filePath)
{
}

BookRepository::~BookRepository()
{
}

void BookRepository::WriteEntity(Book* book, std::ofstream* outputFileStream)
{
	string idToString = to_string(book->Id);
	outputFileStream->write(idToString.c_str(), idToString.size());
	outputFileStream->put('\n');
	outputFileStream->write(book->Name.c_str(), book->Name.size());
	outputFileStream->put('\n');
	outputFileStream->write(book->AuthorName.c_str(), book->AuthorName.size());
	outputFileStream->put('\n');
	outputFileStream->write(book->Genre.c_str(), book->Genre.size());
	outputFileStream->put('\n');
	string releaseDateToString = to_string(book->ReleaseDate);
	outputFileStream->write(releaseDateToString.c_str(), releaseDateToString.size());
	outputFileStream->put('\n');
}

int BookRepository::PopulateEntity(Book * book, std::ifstream * inputfileStream)
{
	string idString;
	std::getline(*inputfileStream, idString);
	if (idString == "")
	{
		return 1;
	}
	book->Id = stoi(idString);
	std::getline(*inputfileStream, book->Name);
	std::getline(*inputfileStream, book->AuthorName);
	std::getline(*inputfileStream, book->Genre);
	string releaseDateString;
	std::getline(*inputfileStream, releaseDateString);
	book->ReleaseDate = stoi(releaseDateString);
	return 0;
}

void BookRepository::Insert(Book* book)
{
	ofstream outputFileStream;
	outputFileStream.open(filePath, ios::app);
	book->Id = GetNextId();
	WriteEntity(book, &outputFileStream);
	outputFileStream.close();
}

void BookRepository::Remove(Book* book)
{
	ifstream inputFileStream;
	ofstream tempOutputFileStream;
	tempOutputFileStream.open("temp." + filePath, ios::out);
	inputFileStream.open(filePath, ios::in);
	while (!inputFileStream.eof())
	{
		Book* bookDb = new Book();
		bool endOfStream = PopulateEntity(bookDb, &inputFileStream) == 1;
		if (endOfStream)
		{
			inputFileStream.close();
			tempOutputFileStream.close();
			remove(filePath.c_str());
			rename(("temp." + filePath).c_str(), filePath.c_str());
			break;
		}
		if (bookDb->Id != book->Id)
		{
			WriteEntity(bookDb, &tempOutputFileStream);
			delete bookDb;
		}
	}
}

Book * BookRepository::GetById(int id)
{
	ifstream inputFileStream;
	inputFileStream.open(filePath, ios::in);
	while (!inputFileStream.eof() && inputFileStream.good())
	{
		Book* book = new Book();
		PopulateEntity(book, &inputFileStream);
		if (book->Id == id)
		{
			inputFileStream.close();
			return book;
		}
	}
	inputFileStream.close();
	return nullptr;
}

Book * BookRepository::GetByName(string name)
{
	ifstream inputFileStream;
	inputFileStream.open(filePath, ios::in);
	while (!inputFileStream.eof() && inputFileStream.good())
	{
		Book* book = new Book();
		PopulateEntity(book, &inputFileStream);
		if (book->Name == name)
		{
			inputFileStream.close();
			return book;
		}
	}
	inputFileStream.close();
	return nullptr;
}

int BookRepository::GetNextId()
{
	ifstream inputFileStream;
	inputFileStream.open(filePath, ios::in);
	int id = 1;
	while (!inputFileStream.eof())
	{
		Book* book = new Book();
		PopulateEntity(book, &inputFileStream);

		if (id <= book->Id)
		{
			id = book->Id + 1;
		}
		delete book;
	}
	inputFileStream.close();
	return id;
}

vector<Book> BookRepository::GetAll()
{
	vector<Book> booksResult;
	ifstream inputFileStream;
	inputFileStream.open(filePath, ios::in);

	while (!inputFileStream.eof())
	{
		Book* bookDb = new Book();
		bool endOfStream = PopulateEntity(bookDb, &inputFileStream) == 1;
		if (endOfStream)
		{
			inputFileStream.close();
			return booksResult;
		}
		booksResult.push_back(*bookDb);
		delete bookDb;
	}
}
