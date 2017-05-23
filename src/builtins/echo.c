/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 08:15:44 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:54:44 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_tab_to_str(char **arg)
{
	char	*s;
	char	*tmp;
	int		i;

	i = -1;
	s = ft_strdup("\0");
	while (arg[++i])
	{
		tmp = ft_strjoin(s, arg[i]);
		free(s);
		if (arg[i + 1])
			s = ft_strjoin(tmp, " ");
		else
			s = ft_strdup(tmp);
		free(tmp);
	}
	return (s);
}

void	ft_replace_part_three(t_built *built, int i, int *j)
{
	if (built->arg[i][*j + 1] == 'r')
	{
		built->arg[i][*j] = '	';
		built->arg[i][++(*j)] = '\r';
	}
	else if (built->arg[i][*j + 1] == 'v')
	{
		built->arg[i][*j] = '	';
		built->arg[i][++(*j)] = '\v';
	}
	else if (built->arg[i][*j + 1] == 'f')
	{
		built->arg[i][*j] = '	';
		built->arg[i][++(*j)] = '\f';
	}
}

void	ft_replace_part_two(t_built *built, int i, int *j)
{
	if (built->arg[i][*j + 1] == '\\')
	{
		built->arg[i][*j] = '	';
		built->arg[i][++(*j)] = '\\';
	}
	else if (built->arg[i][*j + 1] == 'a')
	{
		built->arg[i][*j] = '	';
		built->arg[i][++(*j)] = '\a';
	}
	else if (built->arg[i][*j + 1] == 'b')
	{
		built->arg[i][*j] = '	';
		built->arg[i][++(*j)] = '\b';
	}
	else if (built->arg[i][*j + 1] == 'n')
	{
		built->arg[i][*j] = '	';
		built->arg[i][++(*j)] = '\n';
	}
	else
		ft_replace_part_three(built, i, j);
}

void	ft_replace_space_echo(t_built *built, int i, int j)
{
	j = 0;
	while (built->arg[i][j])
	{
		if (built->arg[i][j] == '\\')
		{
			if (built->arg[i][j + 1] == '0')
			{
				built->arg[i][j] = '	';
				built->arg[i][++j] = '	';
			}
			else if (built->arg[i][j + 1] == '\'')
			{
				built->arg[i][j] = '	';
				built->arg[i][++j] = '\'';
			}
			else if (built->arg[i][j + 1] == '\"')
			{
				built->arg[i][j] = '	';
				built->arg[i][++j] = '\"';
			}
			else
				ft_replace_part_two(built, i, &j);
		}
		j++;
	}
}

int		ft_echo(t_built *built, t_var *var)
{
	int	i;
	int	j;

	i = 0;
	while (!built->noarg && built->arg[i] && built->arg[i][0] != '\0')
	{
		if (i > 0)
			miniprintf(STDOUT_FILENO, " ");
		ft_replace_space_echo(built, i, j);
		j = -1;
		while (built->first != 'n' && built->arg[i][++j])
			if (built->arg[i][j] == '\\' && built->arg[i][j + 1] == 't' && ++j)
				miniprintf(STDOUT_FILENO, "	");
			else if (built->arg[i][j] != '	')
				miniprintf(STDOUT_FILENO, "%c", built->arg[i][j]);
		i++;
	}
	if (built->first == 0 && !built->noarg)
		miniprintf(STDOUT_FILENO, "\n");
	else if (!built->noarg)
		var->echo = ft_tab_to_str(built->arg);
	else if (built->noarg)
		miniprintf(STDOUT_FILENO, "\n");
	ft_built_free(built);
	return (V);
}
