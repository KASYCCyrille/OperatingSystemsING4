#include "mmu.h"
#include <stdio.h>

void printFullMem(t_mem *mp)
{
	t_address	i;
	t_hole		*link;
	int			mem, alloc;

	link = mp->root;
	mem = 1;
	alloc = 0;
	i = -1;
	while(++i < SIZE)
	{
		if (i > link->adr + link->sz)
		{
			link = link->next;
			mem++;
		}
		if (link && i >= link->adr && i < (link->adr + link->sz))
			alloc = mem;
		else
			alloc = 0;
		printf("%5d : %2d -  %d\n", i, alloc, mp->mem[i]);
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
	i = 0;
	while (link)
	{
		i++;
		printf("%5d, adr: %d - sz : %d\n", i, link->adr, link->sz);
		link = link->next;
	}

}
