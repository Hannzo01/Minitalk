# ifndef MINITALK_H
# define MINITALK_H

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

//  server  //
void    ft_putchar(char c);
void	ft_putnbr(int n);
void	ft_handler(int signum, siginfo_t *info, void *context);

//  client  //
int	    ft_atoi(char *str);
void    handler(int signum);
void	send_char(unsigned char c, int pid);



# endif
