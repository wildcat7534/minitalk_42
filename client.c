/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:26 by cmassol           #+#    #+#             */
/*   Updated: 2024/10/08 16:01:05 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minitalk.h"
#include <signal.h>

volatile sig_atomic_t g_ack_received = 0;

void    handler_ack(int signum)
{
    (void)signum;
    g_ack_received = 1;
}

void    send_char(int pid, char c)
{
    int bit;
    
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
        {
            usleep(142);
        }
        bit++;
    }
}
void    check_pid(char *pid)
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

int        main(int arc, char **arv)
{
    pid_t pid;
    struct sigaction sa;
    
    if (arc != 3)
    {
        ft_printf("Usage: %s [PID] [string]\n", arv[0]);
        return (1);
    }
    check_pid(arv[1]);
    pid = (pid_t)ft_atoi(arv[1]);
    sa.sa_handler = handler_ack;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    ft_printf("Sending message...\n");
    ft_printf("arv[2] : %s\n", arv[2]);
    while (*arv[2])
    {
        while (1)
        {
            if (*arv[2] == '\0')
                break;
            sigaction(SIGUSR1, &sa, NULL);
            send_char(pid, *arv[2]);
            arv[2]++;
        }
    }
    usleep(142);
    send_char(pid, '\0');
    return (0);
}