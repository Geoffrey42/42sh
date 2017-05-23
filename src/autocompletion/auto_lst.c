/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 13:03:21 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:40:59 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*lst_to_str(char *line, t_var *var)
{
	t_lenv	*begin;
	char	*nline;
	char	*clef;
	int		i;
	int		j;

	begin = var->lenv;
	nline = NULL;
	if (!var->lenv)
		return (NULL);
	i = ft_strlen(line);
	while (line[i] != '$')
		i--;
	j = ++i;
	while (line[j] != ' ' && line[j] != '\0')
		j++;
	clef = ft_strsub(line, i, j - i);
	nline = ft_strdup("\0");
	ft_line_in_lst(var, &nline, clef);
	var->lenv = begin;
	free(clef);
	return (nline);
}

void	ft_line_in_lst(t_var *var, char **new_line, char *clef)
{
	char	*tmp;
	char	*tmp1;

	while (var->lenv)
	{
		if (!ft_strncmp(clef, var->lenv->bef, ft_strlen(clef)))
		{
			tmp = ft_strjoin(" $", var->lenv->bef);
			tmp1 = ft_strjoin(*new_line, tmp);
			free(*new_line);
			*new_line = ft_strdup(tmp1);
			free(tmp1);
			free(tmp);
		}
		var->lenv = var->lenv->next;
	}
}
