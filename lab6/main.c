#include "mmu.h"
#include "stdio.h"

int main(void) {
	t_mem 		*mem = initMem();
	t_address	adr1 = myAlloc(mem, 5);
	t_address	adr2 = myAlloc(mem, 10);
	t_address	adr3 = myAlloc(mem, 100);

	printf("%d - %d - %d\n", adr1, adr2, adr3);
	printf("Prev before: %p\n", mem->root->prev);
	myFree(mem, adr2, 10);
	myFree(mem, adr1, 5);	
//	printMemory(mem);

//	myWrite(mem, adr3, 543); // write on the 1st byte
//	myWrite(mem, adr3+9, 34); // write on the 10th byte
//	t_byte val1 = myRead(mem, adr3);
//	t_byte val2 = myRead(mem, adr3+9);
//	printf("%d - %d - %d\n", adr1, adr2, adr3);
//	printf("%d\n", val1);
//	printf("%d\n", val2);
//	printMemory(mem);
}
