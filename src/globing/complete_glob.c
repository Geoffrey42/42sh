/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_glob.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:19:02 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:23:50 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static void	ft_loop_glob(char **glob, char **new_str)
{
	int		j;
	char	*tmp;

	j = 0;
	while (glob && glob[j])
	{
		tmp = ft_strjoin(*new_str, " ");
		free(*new_str);
		*new_str = ft_strjoin(tmp, glob[j]);
		free(tmp);
		j++;
	}
}

char		*complete_glob(char *str)
{
	char	**ret;
	char	*new_str;
	char	**glob;
	int		i;

	i = 0;
	glob = NULL;
	new_str = ft_strdup("\0");
	ret = ft_strsplit(str, ' ');
	while (ret[i] != NULL)
		i++;
	(i > 0) ? i-- : (0);
	if (ret[i])
	{
		glob = globing(ret[i]);
		ft_loop_glob(glob, &new_str);
		while (--i >= 0)
			free(ret[i]);
	}
	i = -1;
	while (glob && glob[++i])
		free(glob[i]);
	free(glob);
	free(ret);
	return (new_str);
}
