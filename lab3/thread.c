#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/times.h>
#include <sys/resource.h>

#define A 10
#define B 5
#define C 10
#define D 5
#define E 10
#define F 5
#define G 5
#define H 5


typedef struct s_calcul
{
	int v1;
	int v2;
	int *ret;
}				t_calc;

void	*op_addition(void *param)
{
	t_calc *calc = (t_calc*)param;

	*(calc->ret) = calc->v1 + calc->v2; 
}


void	*op_substraction(void *param)
{
	t_calc *calc = (t_calc*)param;

	*(calc->ret) = calc->v1 - calc->v2; 
}

void	*op_multiplication(void *param)
{
	t_calc *calc = (t_calc*)param;

	*(calc->ret) = calc->v1 * calc->v2; 
}

void	*op_division(void *param)
{
	t_calc *calc = (t_calc*)param;

	if (calc->v2 == 0)
	{
		printf("Can't divide by 0\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		*(calc->ret) = calc->v1 / calc->v2;
	}
}


void	*op_modulo(void *param)
{
	t_calc *calc = (t_calc*)param;

	if (calc->v2 == 0)
	{
		printf("Can't modulo by 0\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		*(calc->ret) = calc->v1 % calc->v2;
	}
}


void	create_thread(int iterateur)
{
	int			tab[8], iret[8], current_thread;
	pthread_t	thread[8];
	t_calc		calc[8];
	
	current_thread = 0;
	calc[current_thread].v1 = A;
	calc[current_thread].v2 = B;
	calc[current_thread].ret = &tab[current_thread];
	if((iret[current_thread]) = pthread_create(thread + current_thread, NULL, &op_addition, (void*)(&calc[current_thread])))
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n", iret[current_thread]);
		exit(EXIT_FAILURE);
	}

	current_thread = 1;
	calc[current_thread].v1 = C;
	calc[current_thread].v2 = D;
	calc[current_thread].ret = &tab[current_thread];
	if((iret[current_thread]) = pthread_create(thread + current_thread, NULL, &op_multiplication, (void*)(&calc[current_thread])))
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n", iret[current_thread]);
		exit(EXIT_FAILURE);
	}

	current_thread = 2;
	calc[current_thread].v1 = E;
	calc[current_thread].v2 = F;
	calc[current_thread].ret = &tab[current_thread];
	if((iret[current_thread]) = pthread_create(thread + current_thread, NULL, &op_substraction, (void*)(&calc[current_thread])))
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n", iret[current_thread]);
		exit(EXIT_FAILURE);
	}

	current_thread = 3;
	calc[current_thread].v1 = G;
	calc[current_thread].v2 = H;
	calc[current_thread].ret = &tab[current_thread];
	if((iret[current_thread]) = pthread_create(thread + current_thread, NULL, &op_addition, (void*)(&calc[current_thread])))
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n", iret[current_thread]);
		exit(EXIT_FAILURE);
	}

	pthread_join(thread[0], NULL); 
	pthread_join(thread[1], NULL); 
	pthread_join(thread[2], NULL); 
	pthread_join(thread[3], NULL); 
//	printf("%d - [ %d / %d ] + %d\n", tab[0], tab[1], tab[2], tab[3]);


	current_thread = 4;
	calc[current_thread].v1 = tab[0];
	calc[current_thread].v2 = tab[3];
	calc[current_thread].ret = &tab[current_thread];
	if((iret[current_thread]) = pthread_create(thread + current_thread, NULL, &op_addition, (void*)(&calc[current_thread])))
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n", iret[current_thread]);
		exit(EXIT_FAILURE);
	}

	current_thread = 5;
	calc[current_thread].v1 = tab[1];
	calc[current_thread].v2 = tab[2];
	calc[current_thread].ret = &tab[current_thread];
	if((iret[current_thread]) = pthread_create(thread + current_thread, NULL, &op_division, (void*)(&calc[current_thread])))
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n", iret[current_thread]);
		exit(EXIT_FAILURE);
	}

	pthread_join(thread[4], NULL); 
	pthread_join(thread[5], NULL);

	
	printf("%d - %d\n", iterateur, tab[4] - tab[5]);
}

int		main(void)
{
	int				iterateur;
	struct rusage	rstart, rend;

	getrusage(RUSAGE_SELF, &rstart);
	for (iterateur = 0; iterateur < 100; iterateur++)
	{
		create_thread(iterateur);
	}
	getrusage(RUSAGE_SELF, &rend);
	
	printf("\n  Thread usage:\nTime: %ldusec\nNb swap: %ld\nNb block read: %ld\nNb block write: %ld\nNb message sent: %ld\nNb message get: %ld\nNb signal get: %ld",
		   ( 
			   (rend.ru_utime.tv_sec-rstart.ru_utime.tv_sec)*1000000 +(rend.ru_utime.tv_usec-rstart.ru_utime.tv_usec)+(rend.ru_stime.tv_sec-rstart.ru_stime.tv_sec)*1000000 +(rend.ru_stime.tv_usec-rstart.ru_stime.tv_usec)
		   ),
		   (rend.ru_nswap - rstart.ru_nswap),
		   (rend.ru_inblock - rstart.ru_inblock),
		   (rend.ru_oublock - rstart.ru_oublock),
		   (rend.ru_msgsnd - rstart.ru_msgsnd),
		   (rend.ru_msgrcv - rstart.ru_msgrcv),
		   (rend.ru_nsignals - rstart.ru_nsignals)
		);
}
