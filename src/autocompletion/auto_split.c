/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 12:48:12 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:45:53 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_loop_split(t_var *var)
{
	char	*tmp;

	tmp = ft_strjoin(var->comp->array[var->comp->len], "/");
	free(var->comp->array[var->comp->len]);
	var->comp->array[var->comp->len] = ft_strdup(tmp);
	free(tmp);
}

void	split_to_line(char *line, t_var *var)
{
	struct stat	s;
	char		*string;

	var->comp->len = 0;
	(var->comp->split) ? var->comp->new = ft_strjoin(var->comp->begin, "*") :
	(0);
	(!var->comp->split) ? var->comp->new = ft_strjoin(line, "*") : (0);
	ft_space_to_tab(var->comp->new);
	(find_dollar(line)) ? string = lst_to_str(line, var) : (0);
	(!find_dollar(line)) ? string = complete_glob(var->comp->new) : (0);
	(string != NULL) ? var->comp->array = ft_strsplit(string, ' ') : (0);
	while (var->comp->array[var->comp->len])
	{
		var->comp->array[var->comp->len] =
		ft_tab_space(var->comp->array[var->comp->len]);
		lstat(var->comp->array[var->comp->len], &s);
		var->comp->array[var->comp->len] =
		ft_strdup_spaces(var->comp->array[var->comp->len]);
		(S_ISDIR(s.st_mode)) ? ft_loop_split(var) : (0);
		var->comp->len++;
	}
	while (var->comp->array[var->comp->res])
		var->comp->res++;
	free(string);
}

void	split_line(char *line, t_var *var)
{
	if (var->index < (int)ft_strlen(line))
	{
		var->comp->i = var->index;
		while (var->comp->j < var->index)
		{
			var->comp->begin[var->comp->j] = line[var->comp->j];
			var->comp->j++;
		}
		var->comp->begin[var->comp->j] = '\0';
		var->comp->j = 0;
		while (var->comp->i < (int)ft_strlen(line))
		{
			var->comp->end[var->comp->j] = line[var->comp->i];
			var->comp->i++;
			var->comp->j++;
		}
		var->comp->end[var->comp->j] = '\0';
		var->comp->split = 1;
	}
	split_to_line(line, var);
}
