
#include"LexicalAnalyser.h"
struct lexiconItems* lexicalAnalysis(char* CmdLine) {

	struct lexiconItems* lexItems = createLexStream();

	int state = 0;		//finite state machine state to recognize lexicon type
	char ch = 0;		//reads character from CmdLine
	int iter = 0;		//iterator for CmdLine

	int front = 0;
	int rear = 0;

	char stringLiteral[256];
	char* identifier;
	long double decimalLiteral = 0;
	int idLen = 0;
	long double base = .1;
	long double pow = 0;
	int expSign = 1;

	while (true)
	{
		ch = CmdLine[iter];
		if (ch) {
			if (lexItems->iter >= lexItems->streamSize) {
				lexItems->streamSize *= 2;
				((int**)lexItems->stream)[0] = (int*)realloc(((int**)lexItems->stream)[0], sizeof(int) * lexItems->streamSize);
				((char**)lexItems->stream)[1] = (char*)realloc(((char**)lexItems->stream)[1], sizeof(char*) * lexItems->streamSize);
				((int**)lexItems->stream)[2] = (int*)realloc(((int**)lexItems->stream)[2], lexItems->streamSize * sizeof(int));

			}
		}

		switch (state)
		{
		case 0:
			if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
				front = iter;
				state = 13;
				idLen=1;
				iter++;
			}
			else if (ch >= 48 && ch <= 57) {
				decimalLiteral =(long double) ch - 48;
				state = 7;
				front = iter;
				iter++;
			}
			else {
				switch (ch)
				{
				case '+':
					((int*)((int**)lexItems->stream)[0])[lexItems->iter] = ADD_OP;
					((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter;
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
					iter++;
					break;
				case '-':
					((int*)((int**)lexItems->stream)[0])[lexItems->iter] = SUB_OP;
					((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter;
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
					iter++;
					break;
				case '/':
					((int*)((int**)lexItems->stream)[0])[lexItems->iter] = DIV_OP;
					((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter;
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
					iter++;
					break;
				case '%':
					((int*)((int**)lexItems->stream)[0])[lexItems->iter] = MOD_OP;
					((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter;
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
					iter++;
					break;
				
				case '^':
					((int*)((int**)lexItems->stream)[0])[lexItems->iter] = B_XOR_OP;
					((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter;
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
					iter++;
					break;
				case '~':
					((int*)((int**)lexItems->stream)[0])[lexItems->iter] = B_NOT_OP;
					((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter;
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
					iter++;
					break;
				case ',':
					((int*)((int**)lexItems->stream)[0])[lexItems->iter] = COMA;
					((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter;
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
					iter++;
					break;
				case ';':
					((int*)((int**)lexItems->stream)[0])[lexItems->iter] = SEMICLN;
					((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter;
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
					iter++;
					break;
				case ':':
					((int*)((int**)lexItems->stream)[0])[lexItems->iter] = COLON;
					((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter;
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
					iter++;
					break;
				case '(':
					((int*)((int**)lexItems->stream)[0])[lexItems->iter] = L_PARAN;
					((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter;
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
					iter++;
					break;
				case ')':
					((int*)((int**)lexItems->stream)[0])[lexItems->iter] = R_PARAN;
					((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter;
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
					iter++;
					break;
				case '{':
					((int*)((int**)lexItems->stream)[0])[lexItems->iter] = L_CURLY_BRAC;
					((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter;
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
					iter++;
					break;
				case '}':
					((int*)((int**)lexItems->stream)[0])[lexItems->iter] = R_CURLY_BRAC;
					((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter;
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
					iter++;
					break;
				case '[':
					((int*)((int**)lexItems->stream)[0])[lexItems->iter] = L_S_BRAC;
					((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter;
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
					iter++;
					break;
				case ']':
					((int*)((int**)lexItems->stream)[0])[lexItems->iter] = R_S_BRAC;
					((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter;
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
					iter++;
					break;
				case '*':
					state = 1;
					iter++;
					break;
				case '|':
					state = 5;
					iter++;
					break;
				case '&':
					state = 6;
					iter++;
					break;
				case '<':
					state = 4;
					iter++;
					break;
				case '>':
					state = 3;
					iter++;
					break;
				case '!':
					state = 2;
					iter++;
					break;
				case '\'':
					state = 14;
					iter++;
					front = iter;
					idLen = 1;
					break;
				case '\"':
					state = 15;
					iter++;
					front = iter;
					idLen = 1;
					break;
				case '.':
					state = 8;
					iter++;
					
					break;
				case 0:
					goto A;
					break;
				case ' ':
					iter++;
					break;
				case '=':
					state = 20;
					iter++;
					break;

				default:

					freeResources(lexItems);
					errorPointer(iter);
					std::cout << "Error : Unrecognize input character " << ch << " At " << iter << std::endl;
					return NULL;
					break;
				}
			}
			break;
		case 1:
			if (ch == '*') {
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = POW_OP;
				((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter-1;
				iter++;
			}
			else {
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = MULT_OP;
				((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter-1;
			}
			state = 0;
			((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
			break;
		case 2:
			if (ch == '=') {
				((int*)((int***)lexItems->stream)[0])[lexItems->iter] = NOT_EQTO_OP;
				
				iter++;
			}
			else {
				((int*)((int***)lexItems->stream)[0])[lexItems->iter] = NOT_OP;
				
			}
			((int*)((int**)lexItems->stream)[3])[lexItems->iter] = iter - 1;
			((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
			state = 0;
			break;
		case 3:
			if (ch == '=') {
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = G_OR_EQTO_OP;
				
				iter++;
			}
			else {
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = GREATER_THAN_OP;
				
			}
			((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter - 1;
			((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
			state = 0;
			break;
		case 4:
			if (ch == '=') {
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = L_OR_EQTO_OP;
				iter++;
			}
			else {
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = LESS_THAN_OP;
			}
			((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter - 1;
			((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
			state = 0;
			break;
		case 5:
			if (ch == '|') {
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = OR_OP;
				iter++;
			}
			else {
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = B_OR_OP;
			}
			((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter - 1;
			((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
			state = 0;
			break;
		case 6:
			if (ch == '&') {
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = AND_OP;
				iter++;
			}
			else {
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = B_AND_OP;
			}
			((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter - 1;
			((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
			state = 0;
			break;
		case 7:
			if (ch == '.') {
				state = 8;
				iter++;  
			}
			else if ((ch >= 48) && (ch <= 57)) {
				decimalLiteral *= 10;
				decimalLiteral += (long double)ch - 48;
				iter++;
			}
			else if (ch == 'e' || ch == 'E') {
				state = 10;
				iter++;
			}
			else {    //I just Hate Documentation
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = DEC_LTRL;
				((long double**)((long double***)lexItems->stream)[1])[lexItems->iter] = new long double;
				*((long double**)((long double***)lexItems->stream)[1])[lexItems->iter++] = decimalLiteral;
				decimalLiteral = 0;
				((int*)((int**)lexItems->stream)[2])[lexItems->iter] = front;
				state = 0;
			}
			break;
		case 8:
			if (ch >= 48 && ch <= 57) {
				decimalLiteral += base * ((long double)ch - 48);
				base /= 10;
				state = 9;
				iter++;
			}
			else {
				freeResources(lexItems);
				errorPointer(iter);
				std::cout << "Error : Digit Expected At " << iter << std::endl;
				return NULL;
			}
			break;
		case 9:
			if (ch == 'e' || ch == 'E') {
				state = 10;
				iter++;
				base = .1;
			}
			else if (ch >= 48 && ch <= 57) {
				decimalLiteral += base * ((long double)ch - 48);
				base /= 10;
				iter++;
			}
			else {
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = DEC_LTRL;
				((long double**)((long double***)lexItems->stream)[1])[lexItems->iter] = new long double;
				*((long double**)((long double***)lexItems->stream)[1])[lexItems->iter++] = decimalLiteral;
				decimalLiteral = 0;
				((int*)((int**)lexItems->stream)[2])[lexItems->iter] =front;
				state = 0;
				base = .1;
			}
			break;
		case 10:
			if (ch == '-') {
				expSign = -1;
				state = 11;
				iter++;
			}
			else if (ch == '+') {
				state = 11;
				iter++;
			}
			else if (ch >= 48 && ch <= 57) {
				pow = (long double)ch - 48;
				state = 12;
				iter++;
			}
			else {
				freeResources(lexItems);
				errorPointer(iter);
				std::cout << "Error : Digit or +/- Sign Expected At " << iter << std::endl;
				return NULL;
			}
			break;
		case 11:
			if (ch >= 48 && ch <= 57) {
				pow = (long double)ch - 48;
				state = 12;
				iter++;
			}
			else {
				freeResources(lexItems);
				errorPointer(iter);
				std::cout << "Error : Digit Expected At " << iter << std::endl;
				return NULL;
			}
			break;
		case 12:
			if (ch >= 48 && ch <= 57) {
				pow *= 10;
				pow += (long double)ch - 48;
				iter++;
			}
			else {
				decimalLiteral = decimalLiteral * powl(10, expSign * pow);
				state = 0;
				pow = 0;
				//decimalLiteral = 0;
				expSign = 1;
				/*((int*)((int**)lexItems->stream)[0])[lexItems->iter] = DEC_LTRL;
				((long double**)((long double***)lexItems->stream)[1])[lexItems->iter++] = (long double*)malloc(sizeof(long double));
				*((long double**)((long double***)lexItems->stream)[1])[lexItems->iter++] = decimalLiteral;
				*/
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = DEC_LTRL;
				((int*)((int**)lexItems->stream)[2])[lexItems->iter] = front;
				((long double**)((long double***)lexItems->stream)[1])[lexItems->iter] = new long double;
				*((long double**)((long double***)lexItems->stream)[1])[lexItems->iter++] = decimalLiteral;
				
				decimalLiteral = 0;

			}
			break;
		case 13:
			if ((ch >= 65 && ch <= 90) || (ch >= 48 && ch <= 57) || (ch >= 97 && ch <= 122)) {
				idLen++;
				iter++;
			}
			else {
				if (idLen > 16) {
					freeResources(lexItems);
					errorPointer(iter);
					std::cout << "Error : To big identifier At " << front << std::endl;
					return NULL;
				}
				else {
					state = 0;
					identifier = new char[idLen + 1];
					stringCopy(identifier, CmdLine + front, idLen);
					identifier[idLen] = 0;
					((int*)((int**)lexItems->stream)[0])[lexItems->iter] = IDENTIFIER;
					((int*)((int**)lexItems->stream)[2])[lexItems->iter] = front;
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = identifier;
					idLen = 0;

				}
			}
			break;
		case 14:
			if (ch=='\'') {
				if (idLen == 0) {
					((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
				}
				((char**)((char***)lexItems->stream)[1])[lexItems->iter] = (char*)malloc(idLen * sizeof(char));
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = STR_LTRL;
				((int*)((int**)lexItems->stream)[2])[lexItems->iter] = front-1;
				stringCopy(((char**)((char***)lexItems->stream)[1])[lexItems->iter],CmdLine+front,idLen-1);
				*(((char**)((char***)lexItems->stream)[1])[lexItems->iter++]+idLen-1) = 0;
				
				idLen = 0;
				state = 0;
			}
			else {

				idLen++;
			}
			iter++;
			break;
		case 15:
			if (ch == '\"') {
				if (idLen==0) {
					((char**)((char***)lexItems->stream)[1])[lexItems->iter] = NULL;
				}
				((char**)((char***)lexItems->stream)[1])[lexItems->iter] =(char*) malloc(idLen*sizeof(char));
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = STR_LTRL;
				((int*)((int**)lexItems->stream)[2])[lexItems->iter] = front-1;
				stringCopy(((char**)((char***)lexItems->stream)[1])[lexItems->iter],CmdLine+front,idLen);
				*(((char**)((char***)lexItems->stream)[1])[lexItems->iter++] + idLen - 1) = 0;
				idLen = 0;
				state = 0;
				
			}
			else {
				idLen++;
			}
			iter++;
			break;

		case 20:
			if (ch=='=') {
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = EQUALTO_OP;
				((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter-1;
				((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
				iter++;
				state = 0;
				break;
			}
			else {
				((int*)((int**)lexItems->stream)[0])[lexItems->iter] = ASSIGNMENT_OP;
				((int*)((int**)lexItems->stream)[2])[lexItems->iter] = iter - 1;
				((char**)((char***)lexItems->stream)[1])[lexItems->iter++] = NULL;
				state = 0;
				break;
			}
			break;

		default:
			freeResources(lexItems);
			errorPointer(iter);
			std::cout << "Error : Unrecognize input character " << ch << " At " << iter << std::endl;
			return NULL;
			break;
		}
		if (ch == 0) {
			break;
		}

	}
A:	if(lexItems->iter<lexItems->streamSize){
		lexItems->streamSize = lexItems->iter;
		((int**)lexItems->stream)[0] = (int*)realloc(((int**)lexItems->stream)[0], sizeof(int) * lexItems->streamSize);
		((char***)lexItems->stream)[1] = (char**)realloc(((char***)lexItems->stream)[1], sizeof(char*) * lexItems->streamSize);
		((int**)lexItems->stream)[2] = (int*)realloc(((int**)lexItems->stream)[2], lexItems->streamSize * sizeof(int));
	}
	return lexItems;
}


struct lexiconItems* createLexStream() {
	struct lexiconItems* ptr = (struct lexiconItems*)malloc(sizeof(struct lexiconItems));
	ptr->stream = (int**)malloc(3 * sizeof(void*));
	ptr->streamSize = 8;
	ptr->iter = 0;
	((int**)ptr->stream)[0] = (int*)malloc(ptr->streamSize * sizeof(int));	//stream[0] array of pointer to lexicon types	
	/*((int*)(stream))[1] = 90;*/
	((char***)ptr->stream)[1] = (char**)malloc(ptr->streamSize * sizeof(char*)); //stream[1] array of pointer to pointer to lexicon value
	((int**)ptr->stream)[2] = (int*)malloc(sizeof(int)*ptr->streamSize);
	return ptr;
}
void freeResources(struct lexiconItems* LexItems) {
	free((int*)(((int**)LexItems->stream)[0]));
	for (int i = 0; i < LexItems->iter; i++) {
		if ((char*)((char**)((char***)LexItems->stream)[1])[i]) {
			free(((char**)((char***)LexItems->stream)[1])[i]);
		}
	}
	free(LexItems->stream);
	free(LexItems);
}

void stringCopy(char* dest, char* src, int cnt) {
	for (int i = 0; i < cnt; i++) {
		dest[i] = src[i];
	}
}


void printLexicons(struct lexiconItems* lexItems) {
	void* ptr;
	int lexType;
	for (int i = 0; i < lexItems->streamSize; i++) {
		lexType = (int)(((int*)((int**)lexItems->stream)[0])[i]);
		ptr = ((char*)((char**)((char***)lexItems->stream)[1])[i]);
		//std::cout << "\t" << ((char*)((char**)((char***)lexItems->stream)[1])[i]);
		switch (lexType) {
		case ADD_OP:
			std::cout << "#" << lexType << "\t#OP\t+";
			break;
		case SUB_OP:
			std::cout << "#" << lexType << "\t#OP\t-";
			break;
		case MULT_OP:
			std::cout << "#" << lexType << "\t#OP\t*";
			break;
		case DIV_OP:
			std::cout << "#" << lexType << "\t#OP\t/";
			break;
		case MOD_OP:
			std::cout << "#" << lexType << "\t#OP\t%";
			break;
		case POW_OP:
			std::cout << "#" << lexType << "\t#OP\t**";
			break;
		case B_AND_OP:
			std::cout << "#" << lexType << "\t#OP\t&";
			break;
		case B_OR_OP:
			std::cout << "#" << lexType << "\t#OP\t|";
			break;
		case B_NOT_OP:
			std::cout << "#" << lexType << "\t#OP\t~";
			break;
		case B_XOR_OP:
			std::cout << "#" << lexType << "\t#OP\t^";
			break;
		case AND_OP:
			std::cout << "#" << lexType << "\t#OP\t&&";
			break;
		case OR_OP:
			std::cout << "#" << lexType << "\t#OP\t||";
			break;
		case NOT_OP:
			std::cout << "#" << lexType << "\t#OP\t!";
			break;
		case EQUALTO_OP:
			std::cout << "#" << lexType << "\t#OP\t==";
			break;
		case NOT_EQTO_OP:
			std::cout << "#" << lexType << "\t#OP\t!=";
			break;
		case LESS_THAN_OP:
			std::cout << "#" << lexType << "\t#OP\t<";
			break;
		case GREATER_THAN_OP:
			std::cout << "#" << lexType << "\t#OP\t>";
			break;
		case G_OR_EQTO_OP:
			std::cout << "#" << lexType << "\t#OP\t>=";
			break;
		case L_OR_EQTO_OP:
			std::cout << "#" << lexType << "\t#OP\t<=";
			break;
		case IDENTIFIER:
			std::cout << "#" << lexType << "\t#ID\t" << (char*)ptr;;
			break;
		case DEC_LTRL:
			std::cout << "#" << lexType << "\t#DEC_LTRL\t" << *(long double*)ptr;
			break;
		case STR_LTRL:
			std::cout << "#" << lexType << "\t#STR_LTRL\t" << (char*)ptr;
			break;
		case ASSIGNMENT_OP:
			std::cout << "#" << lexType << "\t#OP\t=";
			break;
		case COMA:
			std::cout << "#" << lexType << "\t#SEP\t,";
			break;
		case COLON:
			std::cout << "#" << lexType << "\t#SEP\t:";
			break;
		case SEMICLN:
			std::cout << "#" << lexType << "\t#SEP\t;";
			break;
		case L_PARAN:
			std::cout << "#" << lexType << "\t#PARAN\t(";
			break;
		case R_PARAN:
			std::cout << "#" << lexType << "\t#PARAN\t)";
			break;
		case L_CURLY_BRAC:
			std::cout << "#" << lexType << "\t#PARAN\t{";
			break;
		case R_CURLY_BRAC:
			std::cout << "#" << lexType << "\t#PARAN\t}";
			break;
		case L_S_BRAC:
			std::cout << "#" << lexType << "\t#PARAN\t[";
			break;
		case R_S_BRAC:
			std::cout << "#" << lexType << "\t#PARAN\t]";
			break;
		default:
			break;
		}

		std::cout <<"\t"<<((int**)lexItems->stream)[2][i]<< std::endl;
	}
}

void errorPointer(int possition) {
	std::cout << "   ";
	for (int i = 0; i < possition;i++){
		std::cout << ' ';
	}
	std::cout << '^' << std::endl;
}
