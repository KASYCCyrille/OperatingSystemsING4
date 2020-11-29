#include "mmu.h"

t_byte	myRead(t_mem *mp, t_address p)
{
	return mp->mem[p];
}
