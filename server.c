/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:30:20 by cmassol           #+#    #+#             */
/*   Updated: 2024/10/08 16:18:06 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minitalk.h"
#include "include/libft.h"

void  receive_signal_btoa(int sig, siginfo_t *info, void *context) {
  static unsigned char  c = 0;
  static int bit = 0;
  (void)info;
  (void)context;
  
  c += (sig == SIGUSR1) << bit;
  bit++;
  if (bit == 8) {
    write(STDOUT_FILENO, &c, 1);
/*     write(STDOUT_FILENO, "\n", 1);
    write(STDOUT_FILENO, "Received: ", 10);
    write(STDOUT_FILENO, "\n", 1); */
    c = 0;
    bit = 0;
  }

  if (info->si_pid != 0)
    kill(info->si_pid, SIGUSR1);
    
  //char *info_pid = ft_itoa(info->si_pid);
  //write(1, "\nSignal received from PID: ", 27);
  //write(1, info_pid, ft_strlen(info_pid));
  return ;
}
void  handle_sigterm(int sig) {
  (void)sig;
  write(1, "\n", 1);
  write(1, "Received signal SIGTERM\n", 24);
  write(1, "Exiting...\n", 11);
  write(1, "Goodbye!\n", 9);
  write(1, ".....🐱", 9);
  write(1, "\n", 1);
  exit(0);
}

int main(void) {
  pid_t pid;

  struct sigaction sa;

  sa.sa_sigaction = receive_signal_btoa;
  sa.sa_flags = SA_SIGINFO;
  sigaction(SIGUSR1, &sa, NULL);
  sigaction(SIGUSR2, &sa, NULL);
  sigaction(SIGTERM, &sa, NULL);
  pid = getpid();
  ft_printf("The process ID is %d\n", pid);
  write(1, "Waiting for signals...\n", 23);
  write(1, "Press Ctrl+C to stop the server\n\n", 32);

  while(1) {
    //ft_printf("signal SIGUSR1 : %d\n", SIGUSR1);
    //ft_printf("signal SIGUSR2 : %d\n", SIGUSR2);
    signal(SIGINT, handle_sigterm);
    sigaction(SIGUSR1, &sa, NULL);
    pause();
    sigaction(SIGUSR2, &sa, NULL);
    pause();
  }
  return (0);
}