/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:30:20 by cmassol           #+#    #+#             */
/*   Updated: 2024/10/13 17:16:08 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minitalk.h"

void	add_char(t_lst_char **lst, char c)
{
	t_lst_char	*new;
	t_lst_char	*tmp;

	new = (t_lst_char *)malloc(sizeof(t_lst_char));
	if (!new)
		return ;
	new->c = c;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
	}
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	print_lst(t_lst_char *lst)
{
	t_lst_char	*tmp;

	tmp = lst;
	while (tmp)
	{
		write(1, &tmp->c, 1);
		tmp = tmp->next;
	}
}

void	receive_signal_btoa(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				bit;
	static t_lst_char		*lst_str = NULL;

	(void)info;
	(void)context;
	c += (sig == SIGUSR1) << bit;
	bit++;
	if (bit == 8)
	{
		add_char(&lst_str, c);
		if (c == '\0')
		{
			print_lst(lst_str);
			ft_free(lst_str);
			lst_str = NULL;
			write(STDOUT_FILENO, "\n", 1);
		}
		c = 0;
		bit = 0;
	}
	if (info->si_pid != 0)
		kill(info->si_pid, SIGUSR1);
	return ;
}

void	handle_sigterm(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	write(1, "Received signal SIGTERM\n", 24);
	write(1, "Exiting...\n", 11);
	write(1, "Goodbye!\n", 9);
	write(1, ".....🐱", 9);
	write(1, "\n", 1);
	exit(0);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_sigaction = receive_signal_btoa;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	pid = getpid();
	ft_printf("The process ID is ==%d==\n", pid);
	write(1, "Waiting for signals...\n", 23);
	write(1, "Press Ctrl+C to stop the server\n\n", 32);
	while (1)
	{
		signal(SIGINT, handle_sigterm);
		sigaction(SIGUSR1, &sa, NULL);
		pause();
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}
