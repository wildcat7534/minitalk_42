/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:26 by cmassol           #+#    #+#             */
/*   Updated: 2024/10/13 16:11:44 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minitalk.h"

volatile sig_atomic_t	g_ack_received;

void	handler_ack(int signum)
{
	(void)signum;
	g_ack_received = 1;
}

void	send_char(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		g_ack_received = 0;
		if (c & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c >>= 1;
		while (!g_ack_received)
			usleep(4200);
		bit++;
	}
}

void	check_pid(char *pid)
{
	while (*pid)
	{
		if (!ft_isdigit(*pid))
		{
			ft_printf("Invalid PID\n");
			exit(1);
		}
		pid++;
	}
}

int	main(int arc, char **arv)
{
	pid_t				pid;
	struct sigaction	sa;

	if (arc != 3)
	{
		ft_printf("Usage: %s [PID] [string]\n", arv[0]);
		return (1);
	}
	check_pid(arv[1]);
	pid = (pid_t)ft_atoi(arv[1]);
	sa.sa_handler = handler_ack;
	sa.sa_flags = 0;
	ft_printf("Sending message...\n");
	while (*arv[2])
	{
		while (1)
		{
			sigaction(SIGUSR1, &sa, NULL);
			send_char(pid, *arv[2]);
			if (*arv[2] == '\0')
				break ;
			arv[2]++;
		}
	}
	return (0);
}
