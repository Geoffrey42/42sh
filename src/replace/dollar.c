/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:43:00 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:34:15 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*replace_dol_find(char *value, t_var *var)
{
	t_lenv *begin;

	begin = var->lenv;
	var->nodol = 0;
	while (var->lenv)
	{
		if (!ft_strcmp(&(value[1]), var->lenv->bef))
		{
			free(value);
			value = ft_strdup(var->lenv->aft);
			var->nodol = 0;
			break ;
		}
		else
			var->nodol = 1;
		var->lenv = var->lenv->next;
	}
	if (var->nodol == 1)
		miniprintf(STDERR_FILENO,
		"42sh: %s Undefined variable.\n", value);
	var->lenv = begin;
	return (value);
}

void	ft_double_dol(char **array, int i)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strsub(array[i], 2, ft_strlen(array[i]));
	tmp1 = ft_itoa(getpid());
	free(array[i]);
	array[i] = ft_strjoin(tmp1, tmp);
	free(tmp);
	free(tmp1);
}

void	ft_dollars(char **array, int i, t_var *var)
{
	if (array[i][0] == '$' && array[i][1] == '$')
		ft_double_dol(array, i);
	else if (array[i][0] == '$' && array[i][1] == '*')
	{
		array[i][0] = ' ';
		array[i][1] = ' ';
	}
	else if (array[i][0] == '$' && array[i][1] != '\0' &&
		array[i][1] != ' ')
		array[i] = replace_dol_find(array[i], var);
}

char	*replace_dol(char *line, t_var *var)
{
	int		i;
	char	**array;
	char	*ret;

	i = 0;
	while (line[i] != '$' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (line);
	i = -1;
	array = ft_strsplit_sp(line);
	while (array[++i])
	{
		if (array[i][0] == '$' && array[i][1] == '?')
		{
			free(array[i]);
			array[i] = ft_itoa(var->var_ret);
		}
		ft_dollars(array, i, var);
	}
	ret = tab_to_str(array, line);
	ft_freetab(&array);
	return (ret);
}
