/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:15:58 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 18:05:08 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_print_str_endl(int nb, ...)
{
	va_list	ap;
	int		i;

	va_start(ap, nb);
	if (nb != 1)
	{
		i = 0;
		while (i++ < nb)
			ft_putstr_fd(va_arg(ap, char*), 2);
	}
	else
		ft_putstr_fd(va_arg(ap, char*), 2);
	va_end(ap);
}

char	*ft_free(char *str)
{
	free(str);
	str = NULL;
	return (NULL);
}

void	ft_init_redir(t_var *var, char *s)
{
	if (var->command)
		free(var->command);
	var->redir = NULL;
	var->command = NULL;
	var->pipe = (char **)malloc(sizeof(char *) * 2);
	var->pipe[0] = ft_strdup(s);
	var->pipe[1] = NULL;
	var->i = 0;
	var->out = 0;
	var->in = 0;
	var->err = 0;
	var->fd_out = 0;
	var->fd_in = 0;
	var->fd_err = 0;
	var->red = 0;
	var->ctl_c = 0;
}

int		ft_search_redir(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			i++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
		if (s[i] == '<')
			return (2);
		if (s[i] == '>' && s[i + 1] == '&')
			return (3);
		if ((s[i] == '>' || s[i] == '<' || s[i] == '|') && s[i - 1] != '\\')
			return (1);
		if (s[i] == '>')
			return (4);
		i++;
	}
	return (0);
}

int		ft_if_pipe(char *s)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i] != '\0')
		if ((s[i] == '\'' || s[i] == '\"') && s[i - 1] != '\\')
		{
			j = i + 1;
			while (s[j] && s[j] != s[i])
				j++;
			i = j;
		}
		else if (s[i] == '|')
			return (1);
	return (0);
}
