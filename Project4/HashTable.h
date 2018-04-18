#pragma once
#include "Slot.h"	//No cpp file because the requirements/instructions were contradictory
#define MAXHASH 10	//TODO - change to 1000

template <class T> class HashTable{
private:
	unsigned int pseudoRandomTable[MAXHASH];
	Slot<T> theTable[MAXHASH];

public:
	HashTable(){
		GenerateRandomTable();
		GenerateIteratedTable();
	}
	~HashTable(){

	}

	void GenerateRandomTable(){
		for(unsigned int i = 0; i < MAXHASH; i++){
			pseudoRandomTable[i] = i;
		}
		for(unsigned int i = 0; i < MAXHASH; i++){
			swapTwoValues(pseudoRandomTable[i], pseudoRandomTable[rand() % MAXHASH]);
		}
	}
	void GenerateIteratedTable(){
		for(unsigned int i = 0; i < MAXHASH; i++){
			theTable[i] = Slot<T>();
		}
	}

	bool keyExists(int key){
		return false;
	}

	bool insert(int key, T value, int& collisions){
		unsigned int spot;
		do{
			spot = dumbHash(key + spot);
		}
		while((theTable[spot]).isEmpty());
	}

	bool remove(int key){

	}

	bool find(int key, T& value){

	}

	float alpha(){
		return 0;
	}
};

void swapTwoValues(unsigned int& value1, unsigned int& value2){
	unsigned int temp = value1;
	value1 = value2;
	value2 = temp;
}

unsigned int dumbHash(int key){
	return key % MAXHASH;
}

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