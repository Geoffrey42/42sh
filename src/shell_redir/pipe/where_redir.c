/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   where_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 01:36:56 by lprunier          #+#    #+#             */
/*   Updated: 2017/04/25 01:37:40 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_free_where(t_var *var, int *i, int *to, int *in)
{
	*i = -1;
	*in = 0;
	*to = -1;
	var->hdc = 0;
	if (var->pipe_in != NULL)
		ft_free_tab(var->pipe_in);
	var->pipe_in = NULL;
	if (var->pipe_out)
		free(var->pipe_out);
	var->pipe_out = NULL;
	if (var->pipe_end)
		free(var->pipe_end);
	var->pipe_end = NULL;
}

void	ft_alloc_in(t_var *var, int in, int to, char *s)
{
	int	i;
	int	j;

	i = 0;
	var->pipe_in = (char **)malloc(sizeof(char *) * (in + 1));
	while (++to < in)
	{
		while (s[i] != '<')
			i++;
		while (s[i] == '<')
			i++;
		while (s[i] == ' ')
			i++;
		j = i;
		while (s[j] != '\0' && s[j] != ' ')
			j++;
		var->pipe_in[to] = ft_strsub(s, i, j - i);
	}
	var->pipe_in[to] = NULL;
}

void	ft_alloc_out(t_var *var, int *i, int *j, char *s)
{
	*j = ++(*i);
	while (s[*j] == ' ')
		(*j)++;
	while (s[*j] != '\0' && s[*j] != ' ')
		(*j)++;
	if (s[*j] == ' ')
		(*j)--;
	(s[*i - 2] == '>') ? var->pipe_end = ft_strsub(s, *i + 1, *j - *i) : (0);
	(s[*i - 2] != '>') ? var->pipe_out = ft_strsub(s, *i + 1, *j - *i) : (0);
}

void	ft_where_redir(t_var *var, char *s)
{
	int	i;
	int	j;
	int	in;
	int	to;

	ft_free_where(var, &i, &to, &in);
	if (s == NULL)
		return ;
	while (s[++i])
		if (s[i] == '<' && s[i + 1] == '<')
		{
			var->hdc = 1;
			i++;
		}
		else if (s[i] == '<')
			in++;
	if (in > 0)
		ft_alloc_in(var, in, to, s);
	i = ft_strlen(s) - 1;
	while (i > 0 && s[i] != '>')
		i--;
	if (s[i] == '>' && s[i + 1] != '&' && s[i + 2] != '&')
		ft_alloc_out(var, &i, &j, s);
	free(s);
}

void	ft_redir_in_out(t_var *var, char ***cmd, int *i, char *tmp)
{
	int	file;

	var->test = 1;
	if (var->pipe_out)
	{
		file = open(var->pipe_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		free(var->pipe_out);
	}
	else if (var->pipe_end)
	{
		file = open(var->pipe_end, O_WRONLY | O_CREAT | O_APPEND, 0644);
		free(var->pipe_end);
	}
	tmp = ft_strdup((*cmd)[0]);
	ft_freetab(&(*cmd));
	*cmd = (char **)malloc(sizeof(char *) * (count_tab(var->pipe_in) + 2));
	(*cmd)[0] = ft_strdup(tmp);
	free(tmp);
	while (var->pipe_in[++(*i)])
		(*cmd)[*i + 1] = ft_strdup(var->pipe_in[*i]);
	(*cmd)[*i + 1] = NULL;
	dup2(file, STDOUT_FILENO);
	ft_freetab(&(var->pipe_in));
	ft_exec(*cmd, var);
	close(file);
}
