// HomeLibrary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BookView.h"
using namespace std;

int main()
{
	BookView* bookView = new BookView();
	bookView->Show();
	delete bookView;
	return 0;
}

