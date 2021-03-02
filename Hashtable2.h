#ifndef HASHTABLE2_H
#define HASHTABLE2_H

#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class HashTable2
{
	public:
		HashTable2( unsigned & size );

		void add( string & key );
		bool search( string & key );
		unsigned getComparisons();

	private:
		bool isPrime(int n);
		unsigned hash( const string & key , unsigned tableSize );

		string* dictionary;
		unsigned sz;
		unsigned comparions;
};

/***************
**CONSTRUCTORS**
***************/

HashTable2::HashTable2( unsigned & size ) {
	unsigned newsz = size * 2;

	if( newsz%2 == 0 )
        newsz++;

    while( !isPrime(newsz) )
		newsz+=2;

	dictionary = new string[ newsz ];
	sz = newsz;
}

/*******************
**MEMBER FUNCTIONS**
*******************/

unsigned HashTable2::hash( const string & key, unsigned tableSize ) {
	unsigned hashVal = 0;

	for( unsigned i = 0; i <= key.length(); i++ )
		hashVal = 37 * hashVal + key[i];

	return hashVal % tableSize;
}

void HashTable2::add( string & key ) {
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

	if( dictionary[ index ] == "") {
		dictionary[ index ] = word;
	}
	else {
		for ( unsigned i = 1; dictionary[ index ] != ""; i++ ) {
			index += i * i;
			index = index % sz;
		}

		dictionary[ index ] = word;
	}
}

bool HashTable2::isPrime(int n) {
    for(int i = 2; i <= n/2; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
} 


bool HashTable2::search( string & key ) {
	unsigned i = 1;
	string word;
	char ch;

	for( unsigned i; i < key.length(); i++) {
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

	while( dictionary[ index ] != word && dictionary[ index ] != "" ) {
		index += i * i;
		index = index % sz;
		i++;
		comparions++;
	}

	return( dictionary[ index ] == word );
}

unsigned HashTable2::getComparisons() {
	return comparions;
}

#endif // HASHTABLE2_H
