#pragma once


struct Colour{
	Colour(unsigned int c) { me = c; }

	operator unsigned int() { return me; }

	unsigned int me;
};


void setColour(unsigned int newColour) {

}

void foo() {

	Colour c = 0xFF0000FF;

	setColour(Colour(0xff0000ff));

}


unsigned int memory = 0x00000004;

void thing() {
	for (unsigned int* iter = memory; iter != 0xff000000; iter++) {

	}
}

for (auto iter = LinkedList.begin(); iter != LinkedList.end(); iter++) {

}