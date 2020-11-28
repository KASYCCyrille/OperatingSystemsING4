#include "mmu.h"
#include <stdlib.h>
#include <stdio.h>

void	defragmentHoles(t_mem *mp)
{
	t_hole *link, *to_free;
	int full_sz;

	link = mp->root;
	while (link->next)
	{
		if (link->adr + link->sz >= link->next->adr)
		{
			to_free = link->next;
			link->sz = (to_free->adr - link->adr) + to_free->sz;
			link->next = to_free->next;
			link->next->prev = link;
			free(to_free);
		}
		else
			link = link->next;
	}
}

void	myFree(t_mem *mp, t_address p, int sz)
{
	t_hole	*link, *new_hole;

	link = mp->root;
	while (link->adr < p && link->next != NULL)
		link = link->next;
	if (!(new_hole = malloc(sizeof(t_hole))))
	{
		printf("ERROR MALLOC");
		return;
	}
	new_hole->sz = sz;
	new_hole->adr = p;
	new_hole->next = link;
	new_hole->prev = link->prev;
	if (link->prev)
		link->prev->next = new_hole;
	else
		mp->root = new_hole;
	link->prev = new_hole;

	printf("-------\n");
	printHole(mp);
	defragmentHoles(mp);
	printf("---\n");
	printHole(mp);
}
