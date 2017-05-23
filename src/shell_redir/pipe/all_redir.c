/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 01:41:01 by lprunier          #+#    #+#             */
/*   Updated: 2017/04/25 01:41:16 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_redir_in_pipe(t_var *var, int *i, int p[2], char ***cmd)
{
	int		fd_bis;
	char	*tmp;

	while (var->pipe_in[++(*i)])
	{
		fd_bis = open(var->pipe_in[*i], O_RDONLY);
		if (var->hdc == 1)
			while (get_next_line(fd_bis, &tmp) != -1)
			{
				write(p[0], tmp, ft_strlen(tmp));
				free(tmp);
			}
		else
			while (get_next_line(fd_bis, &tmp))
			{
				write(p[0], tmp, ft_strlen(tmp));
				free(tmp);
			}
		free(var->pipe_in[*i]);
		free(tmp);
		close(fd_bis);
	}
	free(var->pipe_in);
	ft_exec(*cmd, var);
}

void	ft_rediroutpipe(t_var *var, char ***cmd)
{
	int	file;

	if (var->pipe_out)
		file = open(var->pipe_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		file = open(var->pipe_end, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (var->hdc && var->hdc_result != NULL)
	{
		write(file, var->hdc_result, ft_strlen(var->hdc_result));
		miniprintf(file, "%s", EOF);
	}
	else
		dup2(file, STDOUT_FILENO);
	ft_exec(*cmd, var);
	close(file);
}

void	ft_pipehdc(t_var *var, char ***cmd)
{
	int		file;
	char	*tmp;

	file = open("/sgoinfre/goinfre/Perso/piranucc/.log", O_WRONLY | O_CREAT |
			O_TRUNC, 0644);
	tmp = ft_strdup((*cmd)[0]);
	write(file, var->hdc_result, ft_strlen(var->hdc_result));
	free(var->hdc_result);
	ft_freetab(&(*cmd));
	*cmd = (char **)malloc(sizeof(char *) * (3));
	(*cmd)[0] = ft_strdup(tmp);
	free(tmp);
	(*cmd)[1] = ft_strdup("/sgoinfre/goinfre/Perso/piranucc/.log");
	(*cmd)[2] = NULL;
	ft_exec(*cmd, var);
}

void	ft_choose_redir_pipe(t_var *var, char ***cmd, int p[2])
{
	int		i;
	char	*tmp;

	var->test = 0;
	i = -1;
	tmp = NULL;
	if (var->pipe_in && (var->pipe_end || var->pipe_out))
		ft_redir_in_out(var, cmd, &i, tmp);
	else if (var->pipe_in || (var->hdc && var->pipe_in))
		ft_redir_in_pipe(var, &i, p, cmd);
	else if ((var->pipe_out || var->pipe_end) || ((var->pipe_out ||
					var->pipe_end) && var->hdc))
		ft_rediroutpipe(var, cmd);
	else if (var->hdc && !var->pipe_out && !var->pipe_end && !var->pipe_in &&
			var->hdc_result != NULL)
		ft_pipehdc(var, cmd);
	else
	{
		ft_exec(*cmd, var);
		exit(EXIT_FAILURE);
	}
}
