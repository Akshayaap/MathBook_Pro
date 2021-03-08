#pragma once
#include"tokens.h"


namespace DS {
	struct stack {
		void* stack;
		int top;
		int size;
	};

	struct variable {
		int varCode;
		int typeCode;
		void* value;
	};

	struct terminal {
		int termCode;
		int typeCode;
		void* value;
	};

	struct production {
		int varCode;
		int* prodStr;
		void* action;
	};



	//stack operations
	struct stack* creatStack(int);
	void reSize(struct stack*);
	void fitSize(struct stack*);
	void* pop(struct stack*);
	void push(struct stack*, void*);
	void* top(struct stack*);

}

//grammar operations


namespace mathbook {
	struct production grammar[35]={};
};






