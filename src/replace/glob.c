/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:50:13 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:34:54 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		estula(char *s)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			j = i + 1;
			while (s[i] != s[j])
				j++;
			i = j;
		}
		if (s[i] == '$' && s[i + 1] == '*')
			i++;
		if ((s[i] == '*' && s[i - 1] != '$') || (s[i] == '?' &&
		(s[i - 1] != '$' || i == 0)) || (i > 1 && s[i] == '?' &&
		s[i - 1] == '$' && s[i - 2] == '$'))
			return (1);
	}
	return (0);
}

void	ft_glob_rep(char **tmp, char **array, int i)
{
	free(*tmp);
	*tmp = ft_strdup(array[i]);
	free(array[i]);
	array[i] = complete_glob(*tmp);
	free(*tmp);
}

char	*replace_glob(char *line, t_var *var)
{
	int		i;
	char	**array;
	char	*tmp;
	char	*ret;

	i = -1;
	if (estula(line) == 0)
		return (line);
	array = ft_strsplit_sp(line);
	while (array[++i])
	{
		tmp = complete_glob(array[i]);
		(ft_strcmp(tmp, "\0")) ? ft_glob_rep(&tmp, array, i) : free(tmp);
		if (estula(array[i]) == 1)
		{
			miniprintf(STDERR_FILENO, "%s: No match.\n", array[0]);
			var->nodol = 1;
			break ;
		}
	}
	ret = tab_to_str(array, line);
	ft_freetab(&array);
	return (ret);
}
