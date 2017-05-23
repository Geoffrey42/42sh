/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux_parents.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 11:19:39 by ggane             #+#    #+#             */
/*   Updated: 2017/04/17 20:16:25 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		g_signal;

void	signal_catcher(int catched_signal)
{
	if (catched_signal == SIGINT)
	{
		if (!isatty(STDIN_FILENO))
			exit(130);
		return ;
	}
	if (catched_signal == SIGTSTP)
	{
		miniprintf(STDOUT_FILENO, "\nJob controls are not done, killing cmd\n");
		return ;
	}
	if (catched_signal == SIGUSR1)
		exit(120);
	g_signal = catched_signal;
	return ;
}

int		ft_getsig(void)
{
	char	tmp;

	tmp = g_signal;
	g_signal = 0;
	return (tmp);
}

int		signal_handler(char mode, int sigint_behavior)
{
	if (mode == GETSIG)
		ft_getsig();
	if (sigint_behavior == SIGINT_IGNORE && signal(SIGINT, SIG_IGN) == SIG_ERR)
	{
		miniprintf(STDERR_FILENO, "ERROR: Can't initiate signal handler.\n");
		exit(EXIT_FAILURE);
	}
	else if (sigint_behavior == SIGINT_REGULAR && signal(SIGINT, signal_catcher)
			== SIG_ERR)
	{
		miniprintf(STDERR_FILENO, "ERROR: Can't initiate signal handler.\n");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGTERM, SIG_IGN) == SIG_ERR || signal(SIGQUIT, SIG_IGN) ==
			SIG_ERR || signal(SIGTSTP, SIG_IGN) == SIG_ERR ||
			signal(SIGTTIN, SIG_IGN) == SIG_ERR || signal(SIGTTOU, SIG_IGN)
			== SIG_ERR)
	{
		miniprintf(STDERR_FILENO, "ERROR: Can't initiate signal handler.\n");
		exit(EXIT_FAILURE);
	}
	signal(SIGQUIT, signal_catcher);
	signal(SIGTSTP, signal_catcher);
	return (-1);
}
