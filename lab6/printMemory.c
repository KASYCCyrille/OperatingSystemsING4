#include "mmu.h"
#include <stdio.h>

void printFullMem(t_mem *mp)
{
	t_address	i;
	t_hole		*link;

	i = -1;
	while(++i < SIZE)
	{
		printf("%5d : %d\n", i, mp->mem[i]);
	}
	
}

void printMemory(t_mem *mp)
{
	t_address	i;

	i = -1;
	while(++i < SIZE)
	{
		printf("%5d : %d\n", i, mp->mem[i]);
	}
}

void printHole(t_mem *mp)
{
	t_hole		*link;
	int			i;
	
	link = mp->root;
	i = -1;
	while (link)
	{
		i++;
		printf("%5d, adr: %d - sz : %d\n", i, link->adr, link->sz);
		link = link->next;
	}

}
