/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:29:23 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:13:44 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char	*ft_insert_end(char *line, char buf[BSIZE])
{
	char	*ret;

	ret = ft_strjoin(line, buf);
	free(line);
	return (ret);
}

static void	ft_increase_insert(char buf[BSIZE], int *j, int *i, char **ret)
{
	while (buf[++(*j)] != 0)
		(*ret)[(*i)++] = buf[(*j)];
	(*i)--;
}

char		*ft_insert_char(char *line, char buf[BSIZE], int *index)
{
	char	*ret;
	int		len;
	int		i;
	int		j;

	j = -1;
	len = ft_strlen(line);
	if (*index == len && ft_strlen(buf) >= 2)
		*index += (int)ft_strlen(buf) - 1;
	len = ft_strlen(line) + ft_strlen(buf) - 1;
	if (*index == len)
		return (ft_insert_end(line, buf));
	i = -1;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	while (++i < *index)
		ret[i] = line[i];
	(ft_strlen(buf) == 1) ? ret[i] = buf[0] : (0);
	(ft_strlen(buf) != 1) ? ft_increase_insert(buf, &j, &i, &ret) : (0);
	while (++i <= len)
		ret[i] = line[i - ft_strlen(buf)];
	ret[i] = '\0';
	if (ft_strlen(buf) >= 2)
		*index += (int)ft_strlen(buf) - 1;
	free(line);
	return (ret);
}
