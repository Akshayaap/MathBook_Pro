#include<stdlib.h>


//c++ play freaking hide and sik with intellisense

char** parseCmd(char* cmd,int *numtoken,int *tokensize) {
	int numTokens = 10;
	int i = 0;
	int itr = 0;
	char** tokens =(char**) new char** [10] {0};
	char* buff = new char[10]{0};
	int buffSize = 10;
	char ch;
	int j = 0;
	while (cmd[itr]==' ') {
		itr++;
	}
	while (true) {
		ch = cmd[itr++];
		if (ch==' '||ch==0) {
			tokensize[i] = j;
			j = 0;
			
			if (i<numTokens) {
				tokens[i++] = buff;
				buff = new char[10]{0};
				buffSize = 10;

			}
			else {
				
				numTokens += 10;
				tokens =(char**) realloc(tokens,numTokens*sizeof(char*));

			}
			while (cmd[itr] == ' ') {
				itr++;
			}
			
		}
		else {
			if (j < buffSize) {
				buff[j++] = ch;
			}
			else {
				buffSize += 10;
				buff = (char*)realloc(buff, buffSize);
				buff[j++] = ch;
				for (int a = j; a < buffSize; a++) {
					buff[a] = 0;
				}
			}
		}
		if (ch == 0)
			break;
	}
	
	tokens =(char**) realloc(tokens,i*sizeof(char*));
	*numtoken = i;
	return tokens;
}

void freeCmdBuff(char** cmd,int numtoken) {
	for (int i = 0; i < numtoken;i++) {
		free(cmd[i]);
	}
	free(cmd);
}