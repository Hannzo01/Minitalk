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

void	send_char(unsigned char c, int pid)
{
	unsigned char bit;
	int	i;

	i = 7;
	while (i >= 0)
	{
		bit = c >> i & 1;
		if (bit == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		//pause();//attend un ACK après chaque bit,
		i--;
	}
//	kill(pid, SIGUSR1);
	//pause();
	usleep(500);
}

int main(int argc, char *argv[])
{
	int		pid;
	char	*msg;
	int		i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid == 0 || pid == -1)
			return (-1);
		msg = argv[2];
		while (msg[i] != '\0')
		{
			send_char((unsigned char)msg[i], pid);
			pause(); //attend un ACK après chaque caractère (8 bits envoyés d'un coup).
			i++;
		}
		send_char('\0', pid);
	}
	else
		printf("Error\n");
}