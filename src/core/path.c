/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:14:45 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:09:34 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_write_path(char *tmp, char **path, int i)
{
	tmp = ft_strjoin(path[i], "/");
	free(path[i]);
	path[i] = ft_strdup(tmp);
	free(tmp);
}

int		ft_path_finded(char **s, char *tmp)
{
	free(*s);
	*s = ft_strdup(tmp);
	free(tmp);
	return (1);
}

int		ft_path_inacess(char *tmp, char **s)
{
	free(tmp);
	miniprintf(STDERR_FILENO, "42sh: %s: permission denied.\n", *s);
	return (0);
}
