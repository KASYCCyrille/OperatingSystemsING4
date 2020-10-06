/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Q3.2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suvitiel <ckasyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:19:15 by suvitiel          #+#    #+#             */
/*   Updated: 2020/09/15 11:42:24 by suvitiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main(void)
{
	printf("Process id: %i\n", getpid());
	execl("/usr/bin/firefox", "firefox", (char*)NULL);
}
