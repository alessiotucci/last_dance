/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:02:56 by atucci            #+#    #+#             */
/*   Updated: 2024/03/29 21:54:45 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function is the signal handler for the SIGINT signal,
 which is sent when the user presses Ctrl+C.
 It clears the current line in the readline buffer,
 moves the cursor to a new line, and redraws the prompt.
 This gives you a new prompt on a new line when you press Ctrl+C */
void	handle_ctrl_c(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	printf("\n");
	rl_redisplay();
}

// Signal handler for SIGQUIT (Ctrl+\)
// WE CANNOT USE EXIT!!!
void	handle_ctrl_backlash(int sig)
{
	(void)sig;
	printf("\nHandling signal with Ctrl+\\ \n");
	exit(0);
}

// Signal handler for SIGTERM (default termination signal)
void	handle_ctrl_d(int sig)
{
	(void)sig;
	printf("\nHandling termination signal \n");
	exit(0);
}

/*
		TO DO 
		* include the global variable for exit code
		* use the rl_replace_line, and rl_on_new_line
		* use the rl_redisplay function.
*/
