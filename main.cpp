#include "Hashtable1.h"
#include "Hashtable2.h"

#include <fstream>
#include <chrono>

typedef chrono::high_resolution_clock Clock;

using namespace std;

int main(int argc, char *argv[]) {
	unsigned size = 0;
	unsigned QMisspelled = 0, LMisspelled = 0;
	string word = "";

	string dicName = argv[1];
	string fileName = argv[2];

	ifstream dictionary;
	dictionary.open(dicName.c_str());

	if (dictionary) {
		while(dictionary >> word) {
			size++;
		}
	}

	HashTable1 LHash( size );
	HashTable2 QHash( size );

	dictionary.close();
	dictionary.open(dicName.c_str());

	if (dictionary) {
		while(dictionary >> word) {
			LHash.add( word );
			QHash.add( word );
		}
	}

	dictionary.close();

	ifstream file;
	file.open(fileName.c_str());

	chrono::time_point<std::chrono::system_clock> start1, end1;
	start1 = chrono::system_clock::now();

	if (file) {
		while(file >> word) {
			if( LHash.search( word ) == false ) {
				LMisspelled++;
			}
		}
	}

	end1 = chrono::system_clock::now();
	chrono::duration<double> timePassed1 = end1 - start1;

	file.close();

	file.open(fileName.c_str());

	chrono::time_point<std::chrono::system_clock> start2, end2;
	start2 = chrono::system_clock::now();

	if (file) {
		while(file >> word) {
			if( QHash.search( word ) == false ) {
				QMisspelled++;
			}
		}
	}

	end2 = chrono::system_clock::now();
	chrono::duration<double> timePassed2 = end2 - start2;

	file.close();


	cout << "Linked Hash:" << endl;
	cout << "	Misspelled: " << LMisspelled << endl;
	cout << "	Comparions: " << LHash.getComparisons() << endl;
	cout << "	Time Passed: " << timePassed1.count() << endl;
	cout << "Quadratic Hash:" << endl;
	cout << "	Misspelled: " << QMisspelled << endl;
	cout << "	Comparisons: " << QHash.getComparisons() << endl;
	cout << "	Time Passed: " << timePassed2.count() << endl;

	return 0;
}

