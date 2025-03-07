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
//Static i: This ensures that i persists between function calls and 
//doesn't reset to 8 after each signal.
void	handler(int signum)
{
	static char	byte = 0; //keep track of bits across multiple signals
	static int	i = 8; // Start from the 8th bit (MSB)
	// Shift left to make room for the next bit
	byte = byte << 1;

	// Add the bit based on the signal received
	if (signum == SIGUSR1)
		byte = byte | 1;  // Set the LSB to 1 for SIGUSR1
	else if (signum == SIGUSR2)
		// Leave LSB as 0 for SIGUSR2
		byte = byte | 0; //the default bit value is already 0.

	// Decrease the bit counter (i) after adding the bit
	i--;

	// When 8 bits are received, print the byte and reset
	if (i == 0)
	{
		if (byte == '\0')
			write(1, "\n", 1);
		else
			write(1, &byte, 1); // Print the byte as a character
		byte = 0;			// Reset byte for the next character
		i = 8; // Reset bit counter for the next byte
		// need to reset i = 8 so that the next message can be received properly.	
		//need to reset even if we received '\0' bcz the client can send multiple messages one after another
	}
}

int	main()
{
	printf("%d\n", getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while(1) //to listen for incoming signals.
	{	pause(); // makes the program wait until it receives a signal,
		// making it more efficient while(1); keeps the CPU busy doing nothing.
	}
}