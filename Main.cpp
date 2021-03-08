#include"BasicMath.h"
#include<string.h>
#include<iostream>
#include"LexicalAnalyser.h"



int main(int argc,char** argv) {
	char cmdLine[256] = {0};
	struct lexiconItems *lexItems;

	
	while (true) {
		if (cmdLine[0])
			std::cout << "\n";
		std::cout << ">>>";
		std::cin.getline(cmdLine,256);
		if (cmdLine[0]) {
			lexItems = lexicalAnalysis(cmdLine);
			if (lexItems) {
				printLexicons(lexItems);
				freeResources(lexItems);
			}
		}
		
	}
	
	return 0;
	
} 
