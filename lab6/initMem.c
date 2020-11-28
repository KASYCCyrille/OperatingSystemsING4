#include "mmu.h"
#include <stdlib.h>

t_mem *initMem()
{
	t_mem		*returnMem;
	t_hole		*hole;
	t_address	i;

	if (!(returnMem = malloc(sizeof(t_mem))))
		return NULL;
	if (!(hole = malloc(sizeof(t_hole))))
		return NULL;
	hole->adr = 0;
	hole->sz = SIZE;
	hole->next = NULL;
	hole->prev = NULL;	
	returnMem->root = hole;
	i = -1;
	while (++i < SIZE)
		returnMem->mem[i] = 0;
	return(returnMem);
}
