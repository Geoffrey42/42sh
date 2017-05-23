/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:45:55 by ggane             #+#    #+#             */
/*   Updated: 2017/04/13 16:56:43 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*tab_to_str(char **array, char *line)
{
	char	*new_line;
	int		i;
	char	*tmp;
	char	*tmp1;

	i = -1;
	new_line = ft_strdup("\0");
	while (array[++i] != NULL)
	{
		tmp = ft_strjoin(" ", array[i]);
		tmp1 = ft_strjoin(new_line, tmp);
		free(tmp);
		free(new_line);
		new_line = ft_strdup(tmp1);
		free(tmp1);
	}
	free(line);
	return (new_line);
}
