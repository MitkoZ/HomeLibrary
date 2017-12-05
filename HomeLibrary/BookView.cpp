#include "stdafx.h"
#include "BookView.h"
#include "BookManagementEnum.h"
#include <iostream>
#include <string>
#include "Book.h"
#include "BookRepository.h"
#include <vector>
#include <algorithm>
using namespace std;

BookView::BookView()
{
}

BookView::~BookView()
{
}

void BookView::Show()
{
	while (true)
	{
		BookManagementEnum choice = RenderMenu();
		switch (choice)
		{
		case Insert:
			Add();
			break;
		case Delete:
			Remove();
			break;
		case SearchBookById:
			SearchById();
			break;
		case SearchBookByName:
			SearchByName();
			break;
		case SortByAuthor:
			SortByAuthorName();
			break;
		case SortByYearOfRelease:
			SortByYear();
			break;
		case Exit:
		{
			return;
		}
		}
	}
}

BookManagementEnum BookView::RenderMenu()
{
	while (true)
	{
		system("cls");
		cout << "Book Management:" << endl;
		cout << "[1]. Search Book by id" << endl;
		cout << "[2]. Search Book by name" << endl;
		cout << "[3]. Add Book" << endl;
		cout << "[4]. Delete Book" << endl;
		cout << "[5]. Sort By Author" << endl;
		cout << "[6]. Sort By Year of Release" << endl;
		cout << "[7]. Exit" << endl;
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			return SearchBookById;
		}
		case 2:
		{
			return SearchBookByName;
		}
		case 3:
		{
			return Insert;
		}
		case 4:
		{
			return Delete;
		}
		case 5:
		{
			return SortByAuthor;
		}
		case 6:
		{
			return SortByYearOfRelease;
		}
		case 7:
		{
			return Exit;
		}
		default:
			cout << "Invalid choice! Please try again";
			system("pause");
			break;
		}
	}
}

void BookView::Add()
{
	system("cls");
	string bookName;
	cout << "Enter Book Name:" << endl;
	cin.ignore();
	getline(cin, bookName);
	if (bookName == "")
	{
		cout << "Invalid book name!" << endl;
		system("pause");
		return;
	}
	string author;
	cout << "Enter Book Author:" << endl;
	getline(cin, author);
	if (author == "")
	{
		cout << "Invalid author name!" << endl;
		system("pause");
		return;
	}
	string genre;
	cout << "Enter Book Genre" << endl;
	getline(cin, genre);
	if (genre == "")
	{
		cout << "Invalid genre!" << endl;
		system("pause");
		return;
	}
	string releaseDate;
	cout << "Enter Book Release Date" << endl;
	cin >> releaseDate;
	if (releaseDate == "")
	{
		cout << "Invalid release date!" << endl;
		system("pause");
		return;
	}
	Book* bookInput = new Book(bookName, author, genre, stoi(releaseDate));
	BookRepository* bookRepo = new BookRepository("books.txt");
	bookRepo->Insert(bookInput);
	delete bookInput;
	delete bookRepo;
	cout << "Book saved successfully!" << endl;
	system("pause");
}

void BookView::Remove()
{
	system("cls");
	cout << "Delete a book:" << endl;
	cout << "Book Id:";
	int idInput;
	cin >> idInput;
	BookRepository* bookRepo = new BookRepository("books.txt");
	Book* bookDb = bookRepo->GetById(idInput);
	if (bookDb == nullptr)
	{
		cout << "Book not found!";
		system("pause");
		return;
	}
	else
	{
		bookRepo->Remove(bookDb);
		cout << "Book deleted successfully!";
		system("pause");
		return;
	}
}

void BookView::SearchById()
{
	system("cls");
	cout << "Search book by id:" << endl;
	cout << "Enter Book Id:" << endl;
	int id;
	cin >> id;
	BookRepository* bookRepo = new BookRepository("books.txt");
	Book* book = bookRepo->GetById(id);
	if (book == nullptr)
	{
		cout << "Book with this id not found!" << endl;
		system("pause");
		delete bookRepo;
		delete book;
		return;
	}
	system("cls");
	delete bookRepo;
	PrintEntity(book);
	delete book;
	system("pause");
}

void BookView::PrintEntity(Book * book)
{
	cout << "Id:" << book->Id << endl;
	cout << "Name:" << book->Name << endl;
	cout << "Author Name:" << book->AuthorName << endl;
	cout << "Genre:" << book->Genre << endl;
	cout << "Release Date:" << book->ReleaseDate << endl;
}

void BookView::SearchByName()
{
	system("cls");
	cout << "Search book by name:" << endl;
	cout << "Enter book name:" << endl;
	string name;
	cin >> name;
	BookRepository* bookRepo = new BookRepository("books.txt");
	Book* book = bookRepo->GetByName(name);
	if (book == nullptr)
	{
		cout << "Book with this name not found!" << endl;
		system("pause");
		delete book;
		delete bookRepo;
		return;
	}
	system("cls");
	PrintEntity(book);
	system("pause");
	delete book;
	delete bookRepo;
}

void BookView::SortByAuthorName()
{
	system("cls");
	BookRepository* bookRepo = new BookRepository("books.txt");
	vector<Book> bookVectorDb = bookRepo->GetAll();
	if (bookVectorDb.empty())
	{
		cout << "You don't have any books!" << endl;
		system("pause");
		return;
	}
	sort(bookVectorDb.begin(), bookVectorDb.end(),
		[](const Book& book, const Book& book2) {
		return book.AuthorName < book2.AuthorName;
	});
	for (size_t i = 0; i < bookVectorDb.size(); i++)
	{
		PrintEntity(&bookVectorDb[i]);
		cout << "===============================================" << endl;
	}
	system("pause");
	delete bookRepo;
}

void BookView::SortByYear()
{
	system("cls");
	BookRepository* bookRepo = new BookRepository("books.txt");
	vector<Book> bookVectorDb = bookRepo->GetAll();
	if (bookVectorDb.empty())
	{
		cout << "You don't have any books!" << endl;
		system("pause");
		return;
	}
	sort(bookVectorDb.begin(), bookVectorDb.end(),
		[](const Book& book, const Book& book2) {
		return book.ReleaseDate < book2.ReleaseDate;
	});
	for (size_t i = 0; i < bookVectorDb.size(); i++)
	{
		PrintEntity(&bookVectorDb[i]);
		cout << "===============================================" << endl;
	}
	system("pause");
	delete bookRepo;
}