/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:10:21 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:07:39 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int	ft_execution(t_var *var, char **arg, int ret)
{
	pid_t	pid;

	init_std(var);
	if ((pid = fork()) == 0)
	{
		(var->env != NULL) ? ft_freetab(&var->env) : (0);
		var->env = ft_lst_to_tab(&var->lenv);
		ft_kill_quotes(&arg);
		execve(arg[0], arg, var->env);
		exit(0);
	}
	else if (parent_exec(pid, &ret, var) == 0)
		return (ret);
	signal_handler(SETSIG, SIGINT_REGULAR);
	init_termios(var);
	wait(&ret);
	return (ret);
}

int	ft_exec(char **cmd, t_var *var)
{
	if (ft_is_builtin(cmd[0]) == V)
		return (builtins(cmd, var));
	else if (ft_find_exec(&cmd[0], var))
	{
		ft_freetab(&var->env);
		var->env = ft_lst_to_tab(&var->lenv);
		ft_kill_quotes(&cmd);
		execve(cmd[0], cmd, var->env);
		exit(0);
	}
	return (F);
}
