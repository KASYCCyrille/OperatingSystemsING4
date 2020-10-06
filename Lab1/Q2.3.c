/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Q3.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suvitiel <ckasyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 14:52:36 by suvitiel          #+#    #+#             */
/*   Updated: 2020/09/08 15:14:00 by suvitiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main(void)
{
	pid_t	process_id;
	int		i = 5;

	if (!(process_id = fork()))
	{
		printf("I'm the parent - %i\n", process_id);
		i++;
	}
	else
	{
		printf("I'm the child - %i\n", process_id);
		sleep(3);
		printf("i = %d\n", i);
	}
	return (0);
}
