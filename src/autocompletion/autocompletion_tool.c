/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion_tool.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:00:21 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:46:38 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_strlen_tab(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] < 0)
			j++;
		i++;
	}
	i -= j;
	return (i);
}

int		max_len(char **array)
{
	int	len;
	int	i;

	i = 0;
	(array && array[0]) ? len = ft_strlen_tab(array[0]) : (0);
	while (array[++i])
	{
		ft_tab_to_space(array[i]);
		if (len < ft_strlen_tab(array[i]))
			len = ft_strlen_tab(array[i]);
		ft_space_to_tab(array[i]);
	}
	i = ft_strlen_tab(array[0]) - 1;
	if (array[0][i] == '/')
		i--;
	while (i > 0 && array[0][i] != '/')
		i--;
	len -= i;
	return (len);
}

char	*clean_addr(char *s)
{
	char	*clean;
	int		i;

	i = ft_strlen(s);
	while (i > 0 && s[i] != '/')
		i--;
	if (i == 0)
		clean = ft_strdup(s);
	else
		clean = ft_strdup(&(s[i + 1]));
	return (clean);
}

char	*begin_clean(char *begin)
{
	char	*clean;
	int		i;
	int		j;

	i = ft_strlen(begin);
	while (i >= 0)
	{
		if (ft_iswspace(begin[i]) && begin[i - 1] != '\\')
			break ;
		i--;
	}
	clean = (char *)malloc(sizeof(char) * (i + 1));
	j = 0;
	while (j <= i)
	{
		clean[j] = begin[j];
		j++;
	}
	clean[j] = '\0';
	return (clean);
}
