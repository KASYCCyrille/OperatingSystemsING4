#include "mmu.h"
#include <stdlib.h>

t_hole *bestFit(t_mem *mem, int sz)
{
	t_hole *link, *ret;

	link = mem->v_root;
	ret = NULL;
	while (link)
	{
		if (link->sz > sz && (!ret || link->sz < ret->sz))
			ret = link;
		link = link->next;
	}
	return (ret);
}

t_hole *firstFit(t_mem *mem, int sz)
{
	t_hole	*link;

	link = mem->v_root;
	while (link->sz < sz && link->next != NULL )
		link = link->next;
	if (link->adr + sz > SIZE)
		return (NULL);
	return (link);
}

t_hole *worseFit(t_mem *mem, int sz)
{
	t_hole *link, *ret;

	link = mem->v_root;
	ret = mem->v_root;
	while (link)
	{
		if (link->sz > ret->sz)
			ret = link;
		link = link->next;
	}
	if (ret->sz < sz)
		return (NULL);
	return (ret);
}

t_address myVAlloc(t_mem *mem, int sz)
{
	t_hole		*link;
	t_address	ret;

	//Change here the algorithm that you prefer
	if (!(link = firstFit(mem, sz)))
		return (-1);
	ret = link->adr;
	if(link->sz - sz == 0)
	{
		if(link->prev)
			link->prev->next = link->next;
		else
			mem->v_root->next = link->next;
		link->next->prev = link->prev;
		free(link);
	}
	else
	{
		link->sz = link->sz - sz;
		link->adr = link->adr + sz;
	}
	return (ret);
}

int			firstFreePage(t_mem *mem)
{
	int i, j;

	i = -1;
	while (++i < NB_PAGE)
	{
		j = -1;
		while(++j < SZ_PAGE_TAB && mem->p_pageTable[j] != i);
		if(j == SZ_PAGE_TAB)
			return (i);
	}
	return (-1);
}

t_address	myPAlloc(t_mem *mem, int size)
{
	t_address	virtual;
	int			pageNum, sz, sizeCount;

	if ((virtual = myVAlloc(mem, sz)) < 0)
		return (-1);
	sizeCount = size;
	while (sizeCount / PAGE_SIZE > 0)
	{
		if (sizeCount > PAGE_SIZE)
		{
			sizeCount -= PAGE_SIZE;
			sz = PAGE_SIZE;
		}
		else
		{
			sz = SizeCount
			sizeCount = 0;
		}		
		pageNum = virtual / PAGE_SIZE;
		if (mem->p_pageTable[pageNum] == -1)
			if((mem->p_pageTable[pageNum] = firstFreePage(mem)) == -1)
				return (-1);
		//ret = mem->p_pageTable[virtual / PAGE_SIZE] * PAGE_SIZE + (virtual % PAGE_SIZE);
	}
	return (virtual);
}
