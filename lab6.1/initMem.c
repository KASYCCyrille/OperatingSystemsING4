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
	returnMem->v_root = hole;
	i = -1;
	while (++i < P_SIZE)
		returnMem->p_mem[i] = 0;
	i = -1;
	while (++i < SZ_PAGE_TAB)
		returnMem->p_pageTable[i] = -1;
	return(returnMem);
}
