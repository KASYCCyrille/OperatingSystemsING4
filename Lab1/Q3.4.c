/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Q3.4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suvitiel <ckasyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:50:31 by suvitiel          #+#    #+#             */
/*   Updated: 2020/09/15 11:53:24 by suvitiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main (void)
{
	int i = 5;
	if(!fork())
	{
		execl("/usr/bin/firefox", "firefox", (char*)NULL);

		i++;
		printf("%d\n", i);
	}
	else
	{
		printf("Process id: %i\n", getpid());
	}
}
