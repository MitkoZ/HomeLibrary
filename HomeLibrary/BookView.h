#pragma once
#include"Book.h"
class BookView
{
public:
	BookView();
	~BookView();
	void Show();
private:
	enum BookManagementEnum RenderMenu();
	void Add();
	void Remove();
	void SearchById();
	void PrintEntity(Book* book);//prints the entity to the console
	void SearchByName();
	void SortByAuthorName();
	void SortByYear();
};
