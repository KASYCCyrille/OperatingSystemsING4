# ifndef __MMU__H__
# define __MMU__H__

# define SIZE 1000
//65536

typedef short	t_byte;
typedef int		t_address;
typedef			struct s_hole {
	t_address	adr;
	int			sz;
	struct		s_hole *next;
	struct		s_hole *prev;
}				t_hole;

typedef			struct {
	t_byte	mem[SIZE];
	t_hole	*root; // holes list
}				t_mem;

// dynamically allocates a t_mem structure and initializes its content
t_mem*		initMem();
// allocates space in bytes (t_byte) using First-Fit, Best-Fit or Worst-Fit
t_address 	myAlloc(t_mem *mp, int sz);
// release memory that has already been allocated previously
void		myFree(t_mem *mp, t_address p, int sz);
// assign a value to a byte
void		myWrite(t_mem *mp, t_address p, t_byte val);
// read memory from a byte
t_byte		myRead(t_mem *mp, t_address p);

void		printFullMem(t_mem *mp);
void		printMemory(t_mem *mp);
void		printHole(t_mem *mp);
# endif
