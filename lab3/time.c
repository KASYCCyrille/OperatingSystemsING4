#include <sys/times.h>
#include <sys/resource.h>
#include <stdio.h>
#include <unistd.h>


clock_t times(struct tms *buf); 

int main() 
{
  struct tms start, end;
  struct rusage rstart, rend;
  int i;


  times(&start);
  getrusage(RUSAGE_SELF, &rstart);

   for (i=0; i<10000; i++)
    printf("a\n\n");

  times(&end);
  getrusage(RUSAGE_SELF, &rend);

  printf("%.3f s\n",
		 (end.tms_utime
		  +
		  end.tms_stime
		  -
		  start.tms_utime
		  -
		  start.tms_stime
		) * 1.0 / sysconf(_SC_CLK_TCK)
	  );
  
  printf("%ld usec\n",
		 (
			 rend.ru_utime.tv_sec - rstart.ru_utime.tv_sec
		 ) +
		 (
			 rend.ru_utime.tv_usec - rstart.ru_utime.tv_usec
		 ) +
		 (
			 rend.ru_stime.tv_sec - rstart.ru_stime.tv_sec
		 ) +
		 (
			 rend.ru_stime.tv_usec - rstart.ru_stime.tv_usec
		 )
	  );
}
