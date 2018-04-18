#pragma once
#include "Slot.h"	//No cpp file because the requirements/instructions were contradictory
#define MAXHASH 10;	//TODO - change to 1000

template <class T> class HashTable{
public:
	HashTable(){

	}
	~HashTable(){

	}

	bool keyExists(int key){
		return false;
	}

	bool HashTable<T>::insert(int key, T value, int& collisions){

	}

	bool HashTable<T>::remove(int key){

	}

	bool HashTable<T>::find(int key, T& value){

	}

	float HashTable<T>::alpha(){

	}
};

unsigned int ELFHash(const char* str, unsigned int length){	//http://www.partow.net/programming/hashfunctions/#ELFHashFunction
	unsigned int hash = 0;
	unsigned int x = 0;
	unsigned int i = 0;

	for(i = 0; i < length; ++str, ++i){
		hash = (hash << 4) + (*str);

		if((x = hash & 0xF0000000L) != 0){
			hash ^= (x >> 24);
		}

		hash &= ~x;
	}

	return hash;
}