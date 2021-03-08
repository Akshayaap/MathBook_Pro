#pragma once
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<string.h>
#include"tokens.h"
//#include"FSM.h"
void printLexicons(struct lexiconItems* lexItems);
struct lexiconItems* lexicalAnalysis(char*);

void freeResources(struct lexiconItems* LexItems);
struct lexiconItems* createLexStream();
void stringCopy(char*,char*,int);
void errorPointer(int);



struct lexiconItems {
	void* stream;
	/* stream is used to store lexicon
				stream is 1D array of pointer pointing to token type and
				token value respetively*/
	int streamSize ;
	//initial lex stream size which can later be updated
	int iter=0;
};

