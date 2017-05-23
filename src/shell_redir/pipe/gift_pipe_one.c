/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gift_pipe_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piranucc <piranucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 06:26:21 by ggane             #+#    #+#             */
/*   Updated: 2017/04/24 22:18:25 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		is_file(char **s, char **cmd)
{
	int i;
	int	ret;

	i = 0;
	ret = 0;
	*s = NULL;
	while (cmd[i] && ft_strcmp(cmd[i], "<<"))
		i++;
	if (!cmd[i])
		return (0);
	i += 2;
	if (!cmd[i])
		return (0);
	while (cmd[i] && (!ft_strcmp(cmd[i], ">") || !ft_strcmp(cmd[i], ">>")))
		i += 2;
	i -= 2;
	if (!ft_strcmp(cmd[i], ">"))
		ret = 1;
	if (!ft_strcmp(cmd[i], ">>"))
		ret = 2;
	i++;
	*s = ft_strdup(cmd[i]);
	return (ret);
}

void	ft_free_next_cmd(char ***cmd, int i)
{
	int	j;

	free((*cmd)[i]);
	(*cmd)[i] = NULL;
	while ((*cmd)[++i])
		free((*cmd)[i]);
	i = 1;
	while (*(cmd + i))
	{
		j = -1;
		while ((*(cmd + i))[++j])
			free((*(cmd + i))[j]);
		free(*(cmd + i));
		*(cmd + i) = NULL;
		i++;
	}
}

void	ft_init_loop_red(t_var *var)
{
	var->from = 0;
	var->to = 0;
	var->numredir = 0;
	var->repeat = 0;
}

void	ft_aggreg_close(t_var *var, int *fd)
{
	var->old_stderr = dup(STDERR_FILENO);
	close(STDERR_FILENO);
	*fd = open("/dev/null", O_WRONLY);
	dup2(*fd, STDERR_FILENO);
	var->oui = 1;
	var->from = 0;
	var->to = 0;
}

void	ft_loop_redir_spe(t_var *var, char ***cmd, int *i)
{
	var->numredir = is_file(&var->filename, *cmd);
	while ((*cmd)[*i])
	{
		free((*cmd)[*i]);
		(*cmd)[*i] = NULL;
		(*i)++;
	}
}
