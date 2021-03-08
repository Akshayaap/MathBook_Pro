#pragma once

struct variable {

};
struct terminal {

};

struct production {
	struct variable* variable;
	void* derivationString;
	void* action;
};

struct grammar {
	int size;
};



void actionAdd(void* dest,void* src1,void* src2) {

}