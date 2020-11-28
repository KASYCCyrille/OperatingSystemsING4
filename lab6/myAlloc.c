#include "mmu.h"
#include <stdlib.h>
#include <stdio.h>

t_hole *bestFit(t_mem *mp, int sz)
{
	t_hole *link, *ret;

	link = mp->root;
	ret = NULL;
	while (link)
	{
		if (link->sz > sz && (!ret || link->sz < ret->sz))
			ret = link;
		link = link->next;
	}
	return (ret);
}

t_hole *firstFit(t_mem *mp, int sz)
{
	t_hole	*link;

	link = mp->root;
	while (link->sz < sz && link->next != NULL )
		link = link->next;
	if (link->adr + sz > SIZE)
		return (NULL);
	return (link);
}

t_hole *worseFit(t_mem *mp, int sz)
{
	t_hole *link, *ret;

	link = mp->root;
	ret = mp->root;
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

t_address myAlloc(t_mem *mp, int sz)
{
	t_hole		*link;
	t_address	ret;

	//Change here the algorithm that you prefer
	if (!(link = firstFit(mp, sz)))
		return (-1);
	ret = link->adr;
	printf("%d\n", ret);
	if(link->sz - sz == 0)
	{
		if(link->prev)
			link->prev->next = link->next;
		else
			mp->root->next = link->next;
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
