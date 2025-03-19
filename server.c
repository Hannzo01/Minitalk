/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:18:30 by kemzouri          #+#    #+#             */
/*   Updated: 2025/03/06 23:17:15 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

pid_t old_pid = 0; //keep track of the client's PID.

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr (n / 10);
		ft_putnbr (n % 10);
	}
	else
		ft_putchar(n + 48);
}

void	ft_handler(int signum, siginfo_t *info, void *context)
{

	(void)context;
	static char	byte = 0;//keep track of bits across multiple signals
	static int	i = 8;// Start from the 8th bit (MSB)
	//Static i: This ensures that i persists between function calls and 
    //doesn't reset to 8 after each signal.
		//printf("Signal received: %d\n", signum);  // Afficher le signal reçu
	
	if (old_pid == 0)
		old_pid = info->si_pid;
    pid_t   current_pid;

    current_pid = info->si_pid;
    if (current_pid != old_pid)
    {
        byte = 0;
        i = 8;
        old_pid = 0;
    }
	byte = byte << 1;	// Shift left to make room for the next bit

	// Add the bit based on the signal received
    if (signum == SIGUSR1)
		byte = byte | 1; // Set the LSB to 1 for SIGUSR1
	i--; 	// Decrease the bit counter (i) after adding the bit

	// When 8 bits are received, print the byte and reset
	if (i == 0)
	{
		if (byte == '\0')
        {
			write(1, "\n", 1);
            old_pid = 0; // Reset old_pid after the message is fully received
        }
		else
			write(1, &byte, 1);
		byte = 0;
		i = 8;
		//kill(old_pid, SIGUSR1);
	}
        // Acknowledge the received bit
	kill(info->si_pid, SIGUSR1);
		//kill(old_pid, SIGUSR1);
}

int	main()
{
    pid_t   pid;
    struct sigaction sa;

    pid = getpid();
    write(1, "Server is running with PID: ", 28);
	ft_putnbr(pid);
    write(1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handler;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	//signal(SIGUSR1, handler);
	//signal(SIGUSR2, handler);
	while(1) //to listen for incoming signals. 
	{	
        pause(); // makes the program wait until it receives a signal,
		// making it more efficient while(1); keeps the CPU busy doing nothing.
	}
}
