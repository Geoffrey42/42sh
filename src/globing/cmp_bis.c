/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:24:11 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:27:36 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		glob_strlen(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '[')
		{
			while (str[i] != ']' && str[i] != '\0')
				i++;
		}
		if (str[i] == '\0')
			break ;
		i++;
		count++;
	}
	return (count);
}

int		init_strncmp(size_t *i, size_t *y, char *s1, char *s2)
{
	*i = -1;
	*y = 0;
	if (glob_strlen(s2) > glob_strlen(s1))
	{
		return (0);
	}
	return (-1);
}

char	*glob_strstr(char *s1, char *s2)
{
	int	i;

	if (*s2 == '\0')
		return ((char*)s1);
	i = 0;
	while (s1[i] != '\0')
	{
		if (glob_strncmp(s1 + i, s2, glob_strlen(s2)) == 0)
			return (&(s1[i]));
		i++;
	}
	return (NULL);
}

int		glob_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;
	size_t	y;
	char	*bracket;

	if (n == 0 || init_strncmp(&i, &y, s1, s2) != -1)
		return (n);
	while (s1[++i] != '\0' && i < n)
	{
		if (s2[y] == '[')
		{
			y++;
			bracket = make_bracket(s2, y);
			if (bracket == NULL)
				return (1);
			if ((ft_strchr(bracket, s1[i])) == NULL)
				return (free_bracket(bracket));
			free(bracket);
			while (s2[y] != ']')
				y++;
		}
		else if (s1[i] != s2[y] && s2[y] != '?')
			return ((unsigned char)s1[i] - (unsigned char)s2[y]);
		y++;
	}
	return (0);
}
