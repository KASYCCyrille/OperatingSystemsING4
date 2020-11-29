#include "mmu.h"
#include "stdio.h"

int main(void) {
	t_mem 		*mem = initMem();
	t_address	adr1 = myAlloc(mem, 5);
	t_address	adr2 = myAlloc(mem, 10);
	t_address	adr3 = myAlloc(mem, 100);

	myFree(mem, adr2, 10);
	myFree(mem, adr1, 5);
	myWrite(mem, adr3, 543); // write on the 1st byte
	myWrite(mem, adr3+9, 34); // write on the 10th byte
	t_byte val1 = myRead(mem, adr3);
	t_byte val2 = myRead(mem, adr3+9);
	printf("Full memory:\n");
	printFullMem(mem);
	printf("Values read from memory:\n");
	printf("Val1: %d\n", val1);
	printf("Val2: %d\n", val2);
	printf("Registered holes:\n");
	printHole(mem);
}
