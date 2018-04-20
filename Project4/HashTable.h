#pragma once
#include "Slot.h"	//No cpp file because the requirements/instructions were contradictory
#include <cmath>
#define MAXHASH 1000
using namespace std;

unsigned int doHash(int key);

template <class T> class HashTable{
private:
	unsigned int pseudoRandomTable[MAXHASH];
	Slot<T>* theTable[MAXHASH];
	unsigned int filledSlots = 0;

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

	unsigned int getSize(){
		return this->filledSlots;
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
		unsigned int spot = doHash(key);
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
		this->filledSlots++;
		return true;
	}

	bool remove(int key){
		unsigned int spot = doHash(key);
		if((theTable[spot])->getKey() == key){
			(theTable[spot])->kill();
			return true;
		}

		for(unsigned int collisions = 0, originalHash = spot; (theTable[spot])->isTombstone() || (!((theTable[spot])->isEmpty()) && !((theTable[spot])->getKey() == key)); spot = (originalHash + pseudoRandomTable[spot]) % MAXHASH){
			//Since this for loop looks weird, allow me to explain...
			//It starts with zero collisions and setting the originalHash.
			//Every iteration, it increases the collision counter, and pseudo-random probes.
			//If currently and not a match, or previously occupied, continue
			collisions++;
			if(collisions >= MAXHASH){
				return false;
			}
		}

		(theTable[spot])->kill();
		return true;
	}

	bool find(int key, T& value){
		unsigned int spot = doHash(key);
		if((theTable[spot])->getKey() == key){
			value = (theTable[spot])->getValue();
			return true;
		}

		for(unsigned int collisions = 0, originalHash = spot; (theTable[spot])->isTombstone() || (!((theTable[spot])->isEmpty()) && !((theTable[spot])->getKey() == key)); spot = (originalHash + pseudoRandomTable[spot]) % MAXHASH){
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
		return this->filledSlots / MAXHASH;
	}

	template<class T> friend ostream& operator<<(ostream& out, const HashTable<T>& c){
		unsigned short slotWidth = static_cast<unsigned short>(log10(MAXHASH));
		unsigned short keyWidth = static_cast<unsigned short>(log10(INT_MAX));
		out << setfill('0') << std::setiosflags(ios::right) << "\nHere is the tree" << endl;
		for(unsigned int i = 0; i < MAXHASH; i++){
			//char t[32];
			//sprintf_s(t, "%05d", i);
			if(c.theTable[i]->isNormal()){
				out << "Slot: " << setw(slotWidth) << i << setw(0) << "\tKey: " << setw(keyWidth) << c.theTable[i]->getKey() << setw(0) << "\tValue: " << c.theTable[i]->getValue() << endl;
			}
		}
		return out;
	}
};

void swapTwoValues(unsigned int& value1, unsigned int& value2){
	unsigned int temp = value1;
	value1 = value2;
	value2 = temp;
}

unsigned int doHash(int key){
	return key % MAXHASH;
}
