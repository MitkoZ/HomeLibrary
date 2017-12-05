#include "stdafx.h"
#include "Book.h"
using namespace std;

Book::~Book()
{
}

Book::Book()
{
}

Book::Book(string name, string authorName, string genre, int releaseDate)
	:Name(name), AuthorName(authorName), Genre(genre), ReleaseDate(releaseDate)
{

}