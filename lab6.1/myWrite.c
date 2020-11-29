#include "mmu.h"

void	myWrite(t_mem *mp, t_address p, t_byte val)
{
	mp->mem[p] = val;
}
