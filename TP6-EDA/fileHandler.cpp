#include "stdafx.h"
#include "fileHandler.h"
#include <string>
#include <iostream>

using namespace std;

fileHandler::fileHandler(char * fileName, char mode)
{
	switch (mode)
	{
	case 'r':
		file.open(fileName, ios::in);
	}

}

int fileHandler::countLines(void)
{
	int lineCounter = 0;
	string lineAux;
	while (getline(file, lineAux))
	{
		lineCounter++;
	}
	file.clear();
	file.seekg(0, ios::beg); //vuelvo al principio para un nuevo uso

	return lineCounter;
}

int fileHandler::identifyWordLine(string & word)
{
	int i = 0;
	int lineNumber = -1;
	string wordAux;
	bool wordFounded = false;

	while (!wordFounded && getline(file, wordAux))
	{
		lineNumber++;
		cout << wordAux << endl;
		if (word == wordAux)
		{
			wordFounded = true;
		}
	}
	if (!wordFounded)
	{
		lineNumber = -1; //caso que no se halla encontrado la palabra
	}
	file.clear();
	file.seekg(0, ios::beg); //vuelvo al principio para un nuevo uso

	return lineNumber;
}

bool fileHandler::extractLines(string * wordsArray, int numberOfWords)
{
	bool exitOperation = false;
	int i = 0;
	for (i = 0; (i < numberOfWords) && getline(file, wordsArray[i]); i++)
	{
		//solo geteo la línea.
	}
	if (i == numberOfWords)
	{
		exitOperation = true;
	}
	file.clear();
	file.seekg(0, ios::beg); //vuelvo al principio para un nuevo uso

	return exitOperation;
}

bool fileHandler::extractLines(vector <string> & vector_)
{
	bool exitOperation = false;
	string linea;
	int initialCapacity = vector_.size();
	while (getline(file, linea))
	{
		vector_.push_back(linea);
	}
	int finalCapacity = vector_.size();
	if (finalCapacity > initialCapacity)
	{
		exitOperation = true;
	}

	return exitOperation;
}


fileHandler::~fileHandler()
{
	file.close();
}
