/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:34:55 by kemzouri          #+#    #+#             */
/*   Updated: 2025/03/05 23:30:33 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int g_flag = 0;

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	sign = 1;
	res = 0;

	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	res = res * sign;
	return (res);
}

void    handler(int signum)
{
    if (signum == SIGUSR1)
        g_flag = 1;
}

void	send_char(unsigned char c, int pid)
{
	unsigned char bit;
	int	i;
	int	retries;

	i = 7;
	retries = 1000;
	while (i >= 0)
	{
		bit = c >> i & 1;
		if (bit == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
        while (g_flag == 0 && retries > 0)
	{
        	usleep(50);
		retries--;
	}
	if (g_flag == 0)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	g_flag = 0;
        usleep(20);
        i--;
	}
}

int main(int argc, char *argv[])
{
	int		pid;
	int		i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid <= 0)
			return (-1);
        signal(SIGUSR1, handler);
		while (argv[2][i] != '\0')
		{
			send_char((unsigned char)argv[2][i], pid);
			i++;
		}
		send_char('\0', pid);
	}
	else
		write(2, "Error\n", 6);
}
