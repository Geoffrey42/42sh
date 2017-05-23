/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux_parents_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:57:55 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 18:14:12 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int	g_pid;
int	g_signal_bis;

void		signal_catcher_bis(int catched_signal)
{
	if (catched_signal == SIGINT)
	{
		if (!isatty(STDIN_FILENO))
			exit(130);
		return ;
	}
	if (catched_signal == SIGTSTP)
	{
		kill(g_pid, 9);
		g_signal_bis = 9;
		miniprintf(STDOUT_FILENO, "Job controls are not done, killing cmd\n");
		return ;
	}
	if (catched_signal == SIGCHLD)
	{
		return ;
	}
	if (catched_signal == SIGALRM)
	{
		miniprintf(STDOUT_FILENO, "SIGTERM->%d\n", g_pid);
		return ;
	}
	g_signal_bis = catched_signal;
	return ;
}

static void	error_malloc(char *s)
{
	miniprintf(STDERR_FILENO, s);
	exit(EXIT_FAILURE);
}

int			signal_handler_bis(char mode, int sigint_behavior, int pid)
{
	int		tmp;

	g_pid = pid;
	if (mode == GETSIG)
	{
		tmp = g_signal_bis;
		g_signal_bis = 0;
		return (tmp);
	}
	if (sigint_behavior == SIGINT_IGNORE && signal(SIGINT, SIG_IGN) == SIG_ERR)
		error_malloc("ERROR: Can't initiate signal handler.\n");
	else if (sigint_behavior == SIGINT_REGULAR &&
		signal(SIGINT, signal_catcher_bis) == SIG_ERR)
		error_malloc("ERROR: Can't initiate signal handler.\n");
	if (signal(SIGTERM, SIG_IGN) == SIG_ERR ||
			signal(SIGQUIT, SIG_IGN) == SIG_ERR ||
			signal(SIGTSTP, SIG_IGN) == SIG_ERR ||
			signal(SIGTTIN, SIG_IGN) == SIG_ERR ||
			signal(SIGTTOU, SIG_IGN) == SIG_ERR)
		error_malloc("ERROR: Can't initiate signal handler.\n");
	signal(SIGQUIT, signal_catcher_bis);
	signal(SIGTSTP, signal_catcher_bis);
	signal(SIGCHLD, signal_catcher_bis);
	signal(SIGALRM, signal_catcher_bis);
	return (-1);
}

void		print_sig(int *status, t_var *var, int pid,
t_signal_ptr **sig_handler)
{
	if (WTERMSIG(*status) < SIGNALS_CHILD &&
		sig_handler[WTERMSIG(*status)] != NULL)
	{
		if (g_signal_bis != 9 && (WTERMSIG(*status) != 11))
			miniprintf(STDERR_FILENO, sig_handler[WTERMSIG(*status)]->err);
		else if (WTERMSIG(*status) == 11)
			miniprintf(STDERR_FILENO, "[PID]:%d\t%s\t%s\n", pid,
				sig_handler[WTERMSIG(*status)]->err, var->logic[0]);
		else
			miniprintf(STDERR_FILENO, sig_handler[WTERMSIG(*status)]->err);
		var->var_ret = WTERMSIG(*status) + 128;
	}
}

int			parent_exec(pid_t pid, int *status, t_var *var)
{
	t_signal_ptr	**sig_handler;
	int				stop;

	stop = 0;
	signal_handler_bis(SETSIG, SIGINT_IGNORE, pid);
	waitpid(pid, status, WUNTRACED);
	if (WIFSIGNALED(*status))
	{
		if (!(sig_handler = malloc(sizeof(t_signal_ptr *) * SIGNALS_CHILD)))
			error_malloc("ERROR: Out of memory! malloc() failed\n");
		alloc_sig_handler(sig_handler);
		init_sig_handler(sig_handler);
		print_sig(status, var, pid, sig_handler);
		(WTERMSIG(*status) == SIGINT) ? stop = 1 : (0);
		(WTERMSIG(*status) == SIGQUIT) ? stop = 1 : (0);
		(WTERMSIG(*status) == SIGQUIT) ? kill(pid, WTERMSIG(*status)) : (0);
		(WTERMSIG(*status) == SIGTERM) ? stop = 1 : (0);
		free_sig_handler(sig_handler);
	}
	g_signal_bis = 0;
	init_termios(var);
	return (stop);
}
