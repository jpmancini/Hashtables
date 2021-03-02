#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "HashNode.h"

using namespace std;

class HashTable1 {
	public:
		HashTable1( unsigned & size );

		void add( string & key );
		bool search( string & key );
		unsigned getComparisons();

	private:
		bool isPrime(int n);
		unsigned hash( const string & key , int tableSize );

		HashNode** dictionary;
		unsigned sz;
		unsigned comparions;
};

/***************
**CONSTRUCTORS**
***************/

HashTable1::HashTable1( unsigned & size ) {
	unsigned newsz = size * 2;

	if( newsz%2 == 0 )
        newsz++;

    while( !isPrime(newsz) )
		newsz+=2;

	dictionary = new HashNode*[ newsz ];
	sz = newsz;

	for (unsigned i; i < newsz; i++)
		dictionary[i] = NULL;
}


/*******************
**MEMBER FUNCTIONS**
*******************/

unsigned HashTable1::hash( const string & key, int tableSize ) {
	unsigned hashVal = 0;

	for( unsigned i = 0; i <= key.length(); i++ )
		hashVal = 37 * hashVal + key[i];

	return hashVal % tableSize;
}

void HashTable1::add( string & key ) {
	string word = "";
	char ch;
	
	for( unsigned i = 0; i < key.length(); i++) {
		ch = key[i];
		if( ch >= 65 && ch <= 90)
			word += tolower(ch);
		if( ch >= 97 && ch <= 122)
			word += ch;
	}

	unsigned index = hash( word , sz );

	if( dictionary[ index ] == NULL ) {
		dictionary[ index ] = new HashNode( word );
	}
	else {
		HashNode* temp = dictionary[ index ];

		while ( temp->getNext() != NULL ) {
			temp = temp->getNext();
		}
		
		if ( temp->getKey() != word )
			temp->setNext( new HashNode( word ) );
	}
}

bool HashTable1::isPrime(int n) {
    for(int i = 2; i <= n/2; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
} 

bool HashTable1::search( string & key ) {
	string word = "";
	char ch;
	
	for( unsigned i = 0; i < key.length(); i++) {
		ch = key[i];
		if( ch >= 65 && ch <= 90)
			word += tolower(ch);
		if( ch >= 97 && ch <= 122)
			word += ch;
	}

	if( word == "" ){
		return true;
	}

	unsigned index = hash( word, sz );

	if( dictionary[index] != NULL ) {
		HashNode* temp = dictionary[ index ];

		if( temp->getKey() == word ) {
			return true;
		}

		while( temp->getKey() != word && temp->getNext() != NULL ) {
			temp = temp->getNext();
			comparions++;
		}

		if( temp->getKey() == word ) {
			return true;
		}
	}
	else {
		return false;
	}

	return false;
}

unsigned HashTable1::getComparisons() {
	return comparions;
}

#endif // HASHTABLE_H
