#pragma once
#include "Slot.h"	//No cpp file because the requirements/instructions were contradictory
#define MAXHASH 10	//TODO - change to 1000

template <class T> class HashTable{
private:
	unsigned int pseudoRandomTable[MAXHASH];
	Slot<T>* theTable[MAXHASH];

public:
	HashTable(){
		GenerateRandomTable();
		GenerateIteratedTable();
	}
	~HashTable(){
		for(unsigned int i = 0; i < MAXHASH; i++){
			delete theTable[i];
		}
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
			theTable[i] = new Slot<T>();
		}
	}

	bool insert(int key, T value, int& collisions){
		collisions = 0;
		unsigned int spot = dumbHash(key);
		unsigned int originalHash = spot;

		while(!(theTable[spot])->isEmpty()){	//If collision
			if(key == theTable[spot]->getKey()){	//No duplicates
				return false;
			}
			spot = (originalHash + pseudoRandomTable[spot]) % MAXHASH;	//Calculate new spot (h(K) + ri) mod M
			collisions++;
			if(collisions >= MAXHASH){
				return false;
			}
		}

		theTable[spot] = new Slot<T>(key, value);
		return true;
	}

	bool remove(int key){

	}

	bool find(int key, T& value){
		unsigned int spot = dumbHash(key);
		if((theTable[spot])->getKey() == key){
			value = (theTable[spot])->getValue();
			return true;
		}

		for(unsigned int collisions = 0, originalHash = spot; (!(theTable[spot])->isEmpty() || !(theTable[spot])->isTombstone()) && !((theTable[spot])->getKey() == key); spot = (originalHash + pseudoRandomTable[spot]) % MAXHASH){
			//Since this for loop looks weird, allow me to explain...
			//It starts with zero collisions and setting the originalHash.
			//Every iteration, it increases the collision counter, and pseudo-random probes.
			//If currently or previously occupied and not a match, continue the search.
			collisions++;
			if(collisions >= MAXHASH){
				return false;
			}
		}

		value = (theTable[spot])->getValue();
		return true;
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