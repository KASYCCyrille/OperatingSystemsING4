# ifndef __MMU__H__
# define __MMU__H__

# define V_SIZE			65536	//2^16
# define P_SIZE			32768	//2^15
# define SZ_PAGE_TAB	1024	//2^10
# define NB_PAGE		512		//2^9
# define PAGE_SIZE		128		//2^7

typedef short	t_byte;
typedef int		t_address;
typedef int		t_page;
typedef			struct s_hole {
	t_address	adr;
	int			sz;
	struct		s_hole *next;
	struct		s_hole *prev;
}				t_hole;

typedef			struct {
	t_byte	p_mem[P_SIZE];
	t_page	p_pageTable[SZ_PAGE_TAB];
	t_hole	*v_root;
}				t_mem;


// dynamically allocates a t_mem structure and initializes its content
t_mem*		initMem();
// allocates space in bytes (t_byte) using First-Fit, Best-Fit or Worst-Fit
t_address 	myAlloc(t_mem *mem, int sz);
// release memory that has already been allocated previously
void		myFree(t_mem *mem, t_address p, int sz);
// assign a value to a byte
void		myWrite(t_mem *mem, t_address p, t_byte val);
// read memory from a byte
t_byte		myRead(t_mem *mem, t_address p);

void		printFullMem(t_mem *mem);
void		printMemory(t_mem *mem);
void		printHole(t_mem *mem);
# endif
