// Project4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "HashTable.h"
#include "Slot.h"
using namespace std;


int main()
{

	HashTable<int>* hi = new HashTable<int>();

	int col;
	hi->insert(1, 1, col);
	hi->insert(1, 2, col);
	hi->insert(1, 3, col);
	hi->insert(1, 4, col);
	hi->insert(1, 5, col);
	hi->insert(1, 6, col);
	hi->insert(1, 7, col);
	hi->insert(1, 8, col);
	hi->insert(1, 9, col);
	hi->insert(1, 10, col);
	hi->insert(1, 11, col);
	hi->insert(1, 12, col);

	system("PAUSE");
    return 0;
}
