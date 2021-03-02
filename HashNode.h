#ifndef HASHNODE_H
#define HASHNODE_H

#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class HashNode
{
	public:
		HashNode( string key );
		string getKey();
		HashNode* getNext();
		void setKey( string & key);
		void setNext( HashNode* next );
	private:
		string key;
		HashNode* next;
};

/***************
**CONSTRUCTORS**
***************/

HashNode::HashNode( string key ) {
	this->key = key;
	this->next = NULL;
}

/*******************
**MEMBER FUNCTIONS**
*******************/

string HashNode::getKey() {
	return key;
}

HashNode* HashNode::getNext() {
	return next;
}

void HashNode::setKey( string & key) {
	this->key = key;
}

void HashNode::setNext( HashNode* next ) {
	this->next = next;
}


#endif // HASHNODE_H
